#include "../include/User.h"
#include "../include/SHA256.h"
#include <regex>

User::User(const std::string &user_name, const std::string &user_email,
           const std::string &password) {
  set_email(user_email);
  set_name(user_name);

  SHA256 sha;
  sha.update(password);
  std::array<uint8_t, 32> digest = sha.digest();

  pwd_hash = SHA256::toString(digest);
}

// virtuals
void User::load(const std::string &data) {
  // load user from line data
  // format: id,name,email,pwd_hash
  std::vector<std::string> parts;
  std::string part;
  std::istringstream ss(data);
  while (std::getline(ss, part, ',')) {
    parts.push_back(part);
  }

  if (parts.size() != 4) {
    throw std::invalid_argument("Invalid string to load user: " + data);
  }
  set_id(parts[0]);
  set_name(parts[1]);
  set_email(parts[2]);
  pwd_hash = parts[3];
};

std::string User::str() {
  return get_id() + "," + name + "," + email + "," + pwd_hash;
};

std::vector<std::string> User::get_attributes() const {
  return {"id", "name", "email"};
};

bool User::check_query(const std::map<std::string, std::string> &query) const {
  std::map<std::string, std::string> member_map = {
      {"name", get_name()}, {"email", get_email()}, {"id", get_id()}};

  for (auto const &pair : query) {
    auto it = member_map.find(pair.first);
    if (it != member_map.end() && it->second == pair.second) {
      // here if the member value exists
      // and the member value is the same as value in query
      // we continue to the next pair in query
      continue;
    }

    return false; // false if member is not in class
  }

  return true;
};

// setters
void User::set_email(const std::string &new_email) {
  const std::string email_regex = ".+@.+\..+";
  if (std::regex_match(new_email, std::regex(email_regex))) {
    email = new_email;
  } else {
    throw std::invalid_argument("Invalid email: " + new_email);
  }
}
void User::set_name(const std::string &new_name) { name = new_name; }

// getters
std::string User::get_email() const { return email; };
std::string User::get_name() const { return name; };

// operators
bool User::operator==(const User &other) {
  return (get_id() == other.get_id());
}
std::ostream &operator<<(std::ostream &os, const User &user) {
  os << "{ Id: " << user.get_id() << "\n";
  os << "Name: " << user.name << ", ";
  os << "Email: " << user.email << " }\n";
  // Don't print the password hash for security reasons
  return os;
}

// others
bool User::compare_password(const std::string &password) {
  SHA256 sha;
  sha.update(password);
  std::array<uint8_t, 32> digest = sha.digest();

  const std::string input_pwd_hash = SHA256::toString(digest);
  return (input_pwd_hash == pwd_hash);
}