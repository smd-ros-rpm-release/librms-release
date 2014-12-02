#ifndef LIBRMS_CONDITION_HPP_
#define LIBRMS_CONDITION_HPP_

#include <string>
#include <rms/rms.hpp>
#include <rms/slot.hpp>
#include <vector>

namespace librms
{

class rms;
class slot;

class condition
{
public:
  condition(librms::rms *client, unsigned int id, std::string name, unsigned int study_id, unsigned int iface_id, unsigned int environment_id, std::string created, std::string modified);

  unsigned int get_id() const;

  std::string get_name() const;

  unsigned int get_study_id() const;

  unsigned int get_iface_id() const;

  unsigned int get_environment_id() const;

  std::string get_created() const;

  std::string get_modified() const;

  std::vector<librms::slot> &get_slots();

private:
  std::string name_, created_, modified_;
  unsigned int id_, study_id_, iface_id_, environment_id_;
  bool slots_fetched_;
  librms::rms *client_;
  std::vector<librms::slot> slots_;
};

}

#endif
