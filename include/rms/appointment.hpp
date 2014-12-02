#ifndef LIBRMS_APPOINTMENT_HPP_
#define LIBRMS_APPOINTMENT_HPP_

#include <string>
#include <vector>
#include <rms/rms.hpp>
#include <rms/log.hpp>

namespace librms
{

class rms;
class log;

class appointment
{
public:
  appointment(librms::rms *client, unsigned int id, unsigned int user_id, unsigned int slot_id, std::string created, std::string modified);

  unsigned int get_id() const;

  unsigned int get_user_id() const;

  unsigned int get_slot_id() const;

  std::string get_created() const;

  std::string get_modified() const;

  std::vector<librms::log> &get_logs();

private:
  std::string created_, modified_;
  unsigned int id_, user_id_, slot_id_;
  bool logs_fetched_;
  librms::rms *client_;
  std::vector<librms::log> logs_;
};

}

#endif
