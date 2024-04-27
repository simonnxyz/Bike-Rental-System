#include <iostream>

class User {
public:
  User(std::string user_name, std::string user_email, std::string password);

  bool compare_password(std::string password);

  std::string toString();

private:
  std::string name;
  std::string email;
  std::string pwd_hash;
};