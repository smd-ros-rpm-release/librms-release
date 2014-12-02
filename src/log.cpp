#include <rms/log.hpp>

using namespace std;
using namespace librms;

log::log(rms *client, unsigned int id, unsigned int appointment_id, unsigned int type_id, string label, string entry, string created, string modified)
    :
    label_(label), entry_(entry), created_(created), modified_(modified)
{
  id_ = id;
  appointment_id_ = appointment_id;
  type_id_ = type_id;
  client_ = client;
}

unsigned int log::get_id() const
{
  return id_;
}

unsigned int log::get_appointment_id() const
{
  return appointment_id_;
}


unsigned int log::get_type_id() const
{
  return type_id_;
}

string log::get_label() const
{
  return label_;
}

string log::get_entry() const
{
  return entry_;
}

string log::get_created() const
{
  return created_;
}

string log::get_modified() const
{
  return modified_;
}
