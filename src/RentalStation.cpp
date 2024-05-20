/*
* Name: RentalStation.cpp
* Purpose: RentalStation methods
* @author ksiemion
*/

#include "../include/RentalStation.h"
#include <regex>
#include <sstream>

RentalStation::RentalStation(const std::string &name, const double &x,
                             const double &y, const int &capacity,
                             const int &empty_spaces) {
  if (capacity < 1) {
    throw std::invalid_argument("Pojemność nie może być mniejsza od 1.");
  };
  this->name = name;
  this->x = x;
  this->y = y;
  this->capacity = capacity;
  this->empty_spaces = empty_spaces;
}

// virtuals
void RentalStation::load(const std::string &data) {
  // load rental station from line data
  // format: id,name,x,y,capacity,empty_spaces
  std::vector<std::string> parts;
  std::string part;
  std::istringstream ss(data);
  while (std::getline(ss, part, ',')) {
    parts.push_back(part);
  }
  if (parts.size() != 6) {
    throw std::invalid_argument("Nieprawidłowy format danych: " + data);
  }
  set_id(parts[0]);
  set_name(parts[1]);
  set_x(std::stod(parts[2]));
  set_y(std::stod(parts[3]));
  set_capacity(std::stoi(parts[4]));
  set_empty_spaces(std::stoi(parts[5]));
}
std::string RentalStation::str() {
  return get_id() + ',' + name + ',' + std::to_string(x) + ',' +
         std::to_string(y) + ',' + std::to_string(capacity) + ',' +
         std::to_string(empty_spaces);
}
std::vector<std::string> RentalStation::get_attributes() const {
  return {"id", "name", "x", "y", "capacity", "empty spaces"};
}
bool RentalStation::check_query(
    const std::map<std::string, std::string> &query) const {
  std::map<std::string, std::string> member_map = {
      {"name", get_name()},
      {"x", std::to_string(get_x())},
      {"y", std::to_string(get_y())},
      {"capacity", std::to_string(get_capacity())},
      {"empty_spaces", std::to_string(get_empty_spaces())}};

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
}

// setters
void RentalStation::set_name(const std::string &name) { this->name = name; }

void RentalStation::set_x(const double &x) { this->x = x; }

void RentalStation::set_y(const double &y) { this->y = y; }

void RentalStation::set_capacity(const int &capacity) {
  if (capacity < 1) {
    throw std::invalid_argument("Pojemoność nie może być mniejsza od 1.");
  }
  this->capacity = capacity;
}

void RentalStation::set_empty_spaces(const int &empty_spaces) {
  if (empty_spaces < 0 || empty_spaces > capacity) {
    throw std::invalid_argument("Nieprawidłowa liczba wolnych miejsc.");
  }
  this->empty_spaces = empty_spaces;
}

// getters
// getters
std::string RentalStation::get_name() const { return name; }
double RentalStation::get_x() const { return x; }
double RentalStation::get_y() const { return y; }
int RentalStation::get_capacity() const { return capacity; }
int RentalStation::get_empty_spaces() const { return empty_spaces; }

// operators
bool RentalStation::operator==(const RentalStation &other) const {
  return (get_id() == other.get_id());
}
bool RentalStation::operator!=(const RentalStation &other) const {
  return !(*this == other);
}
std::ostream &operator<<(std::ostream &os, const RentalStation &rentalStation) {
  os << "{ Id: " << rentalStation.get_id() << '\n';
  os << "Name: " << rentalStation.get_name() << '\n';
  os << "X: " << std::to_string(rentalStation.get_x()) << '\n';
  os << "Y: " << std::to_string(rentalStation.get_y()) << '\n';
  os << "Capacity: " << std::to_string(rentalStation.get_capacity()) << '\n';
  os << "Empty spaces: " << std::to_string(rentalStation.get_empty_spaces())
     << " }\n";
  return os;
}