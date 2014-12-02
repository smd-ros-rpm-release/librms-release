#include <rms/rms.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace librms;

rms::rms(string host, unsigned int port, string user, string password, string database) :
    host_(host), user_(user), password_(password), database_(database)
{
  port_ = port;
  connected_ = false;
  // setup the client
  conn_ = mysql_init(NULL);
}

rms::~rms()
{
  if (connected_)
  {
    mysql_close(conn_);
  }
}

unsigned int rms::get_port() const
{
  return port_;
}

string rms::get_host() const
{
  return host_;
}

string rms::get_user() const
{
  return user_;
}

string rms::get_password() const
{
  return password_;
}

string rms::get_database() const
{
  return database_;
}

bool rms::connected()
{
  return connected_;
}

bool rms::connect()
{
  if (!mysql_real_connect(conn_, host_.c_str(), user_.c_str(), password_.c_str(), database_.c_str(), port_, NULL, 0))
  {
    cerr << "MySQL Error: '" << mysql_error(conn_) << "'" << endl;
  } else
  {
    connected_ = true;
  }
  return connected_;
}

study rms::get_study(unsigned int id)
{
  stringstream ss;
  ss << "SELECT * FROM `studies` WHERE `id`=" << id << ";";
  MYSQL_RES *res = this->query(ss.str());
  if (res)
  {
    MYSQL_ROW row = mysql_fetch_row(res);
    study s(this, atoi(row[0]), string(row[1]), string(row[2]), string(row[3]), atoi(row[4]), atoi(row[5]) != 0, atoi(row[6]) != 0, atoi(row[7]) != 0, string(row[8]), string(row[9]));
    mysql_free_result(res);
    return s;
  }

  // something went wrong
  study s(this, 1, "", "", "", 1, false, false, false, "", "");
  return s;
}

MYSQL_RES *rms::query(string query)
{
  if (connected_)
  {
    if (mysql_query(conn_, query.c_str()) == 0)
    {
      // parse and get it
      return mysql_use_result(conn_);
    } else
    {
      cerr << "MySQL Error: '" << mysql_error(conn_) << "'" << endl;
    }
  } else
  {
    cerr << "Error: no connection to RMS." << endl;
  }

  // something went wrong
  return NULL;
}
