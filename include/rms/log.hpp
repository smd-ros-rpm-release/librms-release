#ifndef LIBRMS_LOG_HPP_
#define LIBRMS_LOG_HPP_

#include <string>
#include <rms/rms.hpp>

namespace librms
{

class rms;

class log
{
public:
  log(librms::rms *client, unsigned int id, unsigned int appointment_id, unsigned int type_id, std::string label, std::string entry, std::string created, std::string modified);

  unsigned int get_id() const;

  unsigned int get_appointment_id() const;

  unsigned int get_type_id() const;

  std::string get_label() const;

  std::string get_entry() const;

  std::string get_created() const;

  std::string get_modified() const;

private:
  std::string label_, entry_, created_, modified_;
  unsigned int id_, appointment_id_, type_id_;
  librms::rms *client_;
};

}

#endif
