#ifndef LIBRMS_STUDY_HPP_
#define LIBRMS_STUDY_HPP_

#include <string>
#include <rms/rms.hpp>
#include <rms/condition.hpp>
#include <vector>

namespace librms
{

class rms;
class condition;

class study
{
public:
  study(librms::rms *client, unsigned int id, std::string name, std::string start, std::string end, unsigned int length, bool otf, bool parallel, bool repeatable, std::string created, std::string modified);

  unsigned int get_id() const;

  std::string get_name() const;

  std::string get_start() const;

  std::string get_end() const;

  unsigned int get_length() const;

  bool get_otf() const;

  bool get_parallel() const;

  bool get_repeatable() const;

  std::string get_created() const;

  std::string get_modified() const;

  std::vector<librms::condition> &get_conditions();

private:
  std::string name_, start_, end_, created_, modified_;
  bool otf_, parallel_, repeatable_, conditions_fetched_;
  unsigned int id_, length_;
  librms::rms *client_;
  std::vector<librms::condition> conditions_;
};

}

#endif
