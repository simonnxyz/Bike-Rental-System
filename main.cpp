#include "./include/User.h"
#include <iostream>

int main() {
  User u("hello", "world", "at124");

  std::cout << u.toString();
}