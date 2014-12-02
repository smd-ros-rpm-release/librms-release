#include <rms/appointment.hpp>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace librms;

appointment::appointment(rms *client, unsigned int id, unsigned int user_id, unsigned int slot_id, string created, string modified)
    :
    created_(created), modified_(modified)
{
  id_ = id;
  user_id_ = user_id;
  slot_id_ = slot_id;
  client_ = client;
  logs_fetched_ = false;
}

unsigned int appointment::get_id() const
{
  return id_;
}

unsigned int appointment::get_user_id() const
{
  return user_id_;
}

unsigned int appointment::get_slot_id() const
{
  return slot_id_;
}

string appointment::get_created() const
{
  return created_;
}

string appointment::get_modified() const
{
  return modified_;
}

std::vector<log> &appointment::get_logs()
{
  if (!logs_fetched_)
  {
    stringstream ss;
    ss << "SELECT * FROM `logs` WHERE `appointment_id`=" << id_ << ";";
    MYSQL_RES *res = client_->query(ss.str());
    if (res)
    {
      // parse and get it
      MYSQL_ROW row;
      while ((row = mysql_fetch_row(res)) != NULL)
      {
        // fix the JSON
        string entry(row[4]);
        if (!entry.empty())
        {
          string from("&quot;");
          string to("\"");
          size_t start_pos = 0;
          while ((start_pos = entry.find(from, start_pos)) != std::string::npos)
          {
            entry.replace(start_pos, from.length(), to);
            start_pos += to.length();
          }
        }
        log l(client_, atoi(row[0]), atoi(row[1]), atoi(row[2]), string(row[3]), entry, string(row[5]), string(row[6]));
        logs_.push_back(l);
      }
      mysql_free_result(res);
      logs_fetched_ = true;
    }
  }
  return logs_;
}
