#include <rms/condition.hpp>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace librms;

condition::condition(rms *client, unsigned int id, string name, unsigned int study_id, unsigned int iface_id, unsigned int environment_id, string created, string modified)
    :
    name_(name), created_(created), modified_(modified)
{
  id_ = id;
  study_id_ = study_id;
  iface_id_ = iface_id;
  environment_id_ = environment_id;
  client_ = client;
  slots_fetched_ = false;
}

unsigned int condition::get_id() const
{
  return id_;
}

string condition::get_name() const
{
  return name_;
}


unsigned int condition::get_study_id() const
{
  return study_id_;
}


unsigned int condition::get_iface_id() const
{
  return iface_id_;
}


unsigned int condition::get_environment_id() const
{
  return environment_id_;
}

string condition::get_created() const
{
  return created_;
}

string condition::get_modified() const
{
  return modified_;
}

std::vector<slot> &condition::get_slots()
{
  if (!slots_fetched_)
  {
    stringstream ss;
    ss << "SELECT * FROM `slots` WHERE `condition_id`=" << id_ << ";";
    MYSQL_RES *res = client_->query(ss.str());
    if (res)
    {
      // parse and get it
      MYSQL_ROW row;
      while ((row = mysql_fetch_row(res)) != NULL)
      {
        slot c(client_, atoi(row[0]), atoi(row[1]), string(row[2]), string(row[3]), string(row[4]), string(row[5]));
        slots_.push_back(c);
      }
      mysql_free_result(res);
      slots_fetched_ = true;
    }
  }
  return slots_;
}
