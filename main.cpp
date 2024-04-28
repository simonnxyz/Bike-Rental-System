#include "./include/Database.h"
#include "./include/User.h"
#include "./src/Database.cpp"
#include <iomanip>

int main() {
  try {
    Database<User> db("../database/test/users.txt");

    
  } catch (std::invalid_argument e) {
    std::cout << e.what() << "\n";
  };

  User u1("John Kowalski", "sample123@gmail.com", "at124");
  User u2("John Kowalski", "sample123@gmail.com", "at124");

  std::cout << std::boolalpha;

  std::cout << u1.compare_password("at124") << "\n";
  std::cout << (u1 == u2); // comparison by id should return false
}