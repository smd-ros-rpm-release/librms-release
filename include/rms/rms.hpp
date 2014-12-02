#ifndef LIBRMS_RMS_HPP_
#define LIBRMS_RMS_HPP_

#include <mysql/mysql.h>
#include <rms/study.hpp>
#include <string>
#include <vector>

namespace librms
{

class study;

#define RMS_DEFAULT_SERVER "localhost"

#define RMS_DEFAULT_PORT 3306

#define RMS_DEFAULT_USER "ros"

#define RMS_DEFAULT_PASSWORD ""

#define RMS_DEFAULT_DATABASE "rms"

class rms
{
public:
  rms(std::string host, unsigned int port, std::string user, std::string password, std::string database);

  ~rms();

  unsigned int get_port() const;

  std::string get_host() const;

  std::string get_user() const;

  std::string get_password() const;

  std::string get_database() const;

  bool connected();

  bool connect();

  librms::study get_study(unsigned int id);

  MYSQL_RES *query(std::string query);

private:
  MYSQL *conn_; /** Main MySQL connection */

  std::string host_, user_, password_, database_;
  bool connected_;
  unsigned int port_;
};

}

#endif
