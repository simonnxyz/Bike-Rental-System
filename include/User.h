#include <Model.h>
#include <iostream>

class User : Model {
public:
  // constructors
  User(const std::string user_name, const std::string user_email,
       const std::string password);

  // setters
  void set_name(const std::string &name);
  void set_email(const std::string &email);

  // getters
  std::string get_name() const;
  std::string get_email() const;

  // overloaded operators
  bool operator=(const User &other);

  // other
  bool compare_password(std::string password);

private:
  std::string name;
  std::string email;
  std::string pwd_hash;
};