#include "../include/User.h"
#include "../include/SHA256.h"

User::User(std::string user_name, std::string user_email, std::string password)
    : name(user_name), email(user_email) {
  SHA256 sha;
  sha.update(password);
  std::array<uint8_t, 32> digest = sha.digest();

  pwd_hash = SHA256::toString(digest);
}