#ifndef LIBRMS_SLOT_HPP_
#define LIBRMS_SLOT_HPP_

#include <string>
#include <rms/rms.hpp>
#include "appointment.hpp"

namespace librms
{

class rms;
class appointment;

class slot
{
public:
  slot(librms::rms *client, unsigned int id, unsigned int condition_id, std::string start, std::string end, std::string created, std::string modified);

  ~slot();

  unsigned int get_id() const;

  unsigned int get_condition_id() const;

  std::string get_start() const;

  std::string get_end() const;

  std::string get_created() const;

  std::string get_modified() const;

  bool has_appointment();

  librms::appointment &get_appointment();

private:
  std::string start_, end_, created_, modified_;
  unsigned int id_, condition_id_;
  bool appointment_checked_, has_appointment_, appointment_fetched_;
  librms::rms *client_;
  librms::appointment *appointment_;
};

}

#endif
