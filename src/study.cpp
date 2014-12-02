#include <rms/study.hpp>
#include <sstream>
#include <cstdlib>

using namespace std;
using namespace librms;

study::study(rms *client, unsigned int id, string name, string start, string end, unsigned int length, bool otf, bool parallel, bool repeatable, string created, string modified)
    :
    name_(name), start_(start), end_(end), created_(created), modified_(modified)
{
  id_ = id;
  length_ = length;
  otf_ = otf;
  parallel_ = parallel;
  repeatable_ = repeatable;
  client_ = client;
}

unsigned int study::get_id() const
{
  return id_;
}

string study::get_name() const
{
  return name_;
}

string study::get_start() const
{

  return start_;
}

string study::get_end() const
{
  return end_;
}

unsigned int study::get_length() const
{
  return length_;
}

bool study::get_otf() const
{
  return otf_;
}

bool study::get_parallel() const
{
  return parallel_;
}

bool study::get_repeatable() const
{
  return repeatable_;
}

string study::get_created() const
{
  return created_;
}

string study::get_modified() const
{
  return modified_;
}

std::vector<condition> &study::get_conditions()
{
  if (!conditions_fetched_)
  {
    stringstream ss;
    ss << "SELECT * FROM `conditions` WHERE `study_id`=" << id_ << ";";
    MYSQL_RES *res = client_->query(ss.str());
    if (res)
    {
      // parse and get it
      MYSQL_ROW row;
      while ((row = mysql_fetch_row(res)) != NULL)
      {
        condition c(client_, atoi(row[0]), string(row[1]), atoi(row[2]), atoi(row[3]), atoi(row[4]), string(row[5]), string(row[6]));
        conditions_.push_back(c);
      }
      mysql_free_result(res);
      conditions_fetched_ = true;
    }
  }
  return conditions_;
}