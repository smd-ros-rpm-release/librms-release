#include <rms/slot.hpp>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace librms;

slot::slot(rms *client, unsigned int id, unsigned int condition_id, string start, string end, string created, string modified)
    :
    start_(start), end_(end), created_(created), modified_(modified)
{
  id_ = id;
  condition_id_ = condition_id;
  client_ = client;
  appointment_checked_ = false;
  appointment_fetched_ = false;
}

slot::~slot()
{
  if (appointment_fetched_)
  {
    delete appointment_;
  }
}

unsigned int slot::get_id() const
{
  return id_;
}

unsigned int slot::get_condition_id() const
{
  return condition_id_;
}

string slot::get_start() const
{
  return start_;
}

string slot::get_end() const
{
  return end_;
}

string slot::get_created() const
{
  return created_;
}

string slot::get_modified() const
{
  return modified_;
}

bool slot::has_appointment()
{
  if (!appointment_checked_)
  {
    stringstream ss;
    ss << "SELECT COUNT(`id`) FROM `appointments` WHERE `slot_id`=" << id_ << ";";
    MYSQL_RES *res = client_->query(ss.str());
    if (res)
    {
      // parse and get it
      MYSQL_ROW row = mysql_fetch_row(res);
      has_appointment_ = (atoi(row[0]) == 1);
      mysql_free_result(res);
    }
  }
  return has_appointment_;
}

appointment &slot::get_appointment()
{
  if (!appointment_fetched_)
  {
    stringstream ss;
    ss << "SELECT * FROM `appointments` WHERE `slot_id`=" << id_ << ";";
    MYSQL_RES *res = client_->query(ss.str());
    if (res)
    {
      // parse and get it
      MYSQL_ROW row = mysql_fetch_row(res);
      // check for a null user
      uint user_id = 0;
      if (row[1] != NULL)
      {
        user_id = atoi(row[1]);
      }
      appointment_ = new appointment(client_, atoi(row[0]), user_id, atoi(row[2]), string(row[3]), string(row[4]));
      mysql_free_result(res);
      appointment_fetched_ = true;
    }
  }
  return *appointment_;
}
