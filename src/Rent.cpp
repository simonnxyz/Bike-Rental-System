/*
* Name: Rent.cpp
* Purpose: Rent methods
* @author wzieziul
*/

#include "../include/Rent.h"
#include <sstream>

// Constructor
Rent::Rent(const std::string &date, const std::string &user_id,
           const std::string &bicycle_id) {
  this->set_date(date);
  this->set_user(user_id);
  this->set_bicycle(bicycle_id);
}

// Virtuals
void Rent::load(const std::string &data) {
  std::vector<std::string> parts;
  std::string part;
  std::istringstream ss(data);
  while (std::getline(ss, part, ',')) {
    parts.push_back(part);
  }
  if (parts.size() != 5) {
    throw std::invalid_argument("Nieprawidłowy format danych: " + data);
  }
  this->set_id(parts[0]);
  this->set_date(parts[1]);
  this->set_user(parts[2]);
  this->set_bicycle(parts[3]);
  this->set_has_ended(parts[4] == "true" ? true : false);
}

std::string Rent::str() {
  return this->get_id() + "," + this->get_date() + "," + this->get_user() +
         "," + this->get_bicycle() + "," +
         (this->get_has_ended() ? "true" : "false");
}

std::vector<std::string> Rent::get_attributes() const {
  return {"id", "date", "user_id", "bicycle_id", "has_ended"};
}

bool Rent::check_query(const std::map<std::string, std::string> &query) const {
  std::stringstream ss;
  std::map<std::string, std::string> rent_map = {
      {"id", get_id()},
      {"date", get_date()},
      {"user_id", get_user()},
      {"bicycle_id", get_bicycle()},
      {"has_ended", get_has_ended() ? "true" : "false"}};

  for (auto const &pair : query) {
    auto it = rent_map.find(pair.first);
    if (it != rent_map.end() && it->second == pair.second) {
      continue;
    }
    return false;
  }
  return true;
}

// Setters
void Rent::set_date(const std::string &date) { this->date = date; }
void Rent::set_user(const std::string &user_id) { this->user_id = user_id; }
void Rent::set_bicycle(const std::string &bicycle_id) {
  this->bicycle_id = bicycle_id;
}
void Rent::set_has_ended(const bool &new_has_ended) {
  this->has_ended = new_has_ended;
}

// Getters
std::string Rent::get_date() const { return this->date; }
std::string Rent::get_user() const { return this->user_id; }
std::string Rent::get_bicycle() const { return this->bicycle_id; }
bool Rent::get_has_ended() const { return this->has_ended; }

// Overloaded operators
bool Rent::operator==(const Rent &other) const {
  return (this->get_id() == other.get_id());
}

bool Rent::operator!=(const Rent &other) const { return !(*this == other); }

std::ostream &operator<<(std::ostream &os, const Rent &rent) {
  os << "{ Id: " << rent.get_id() << "\n";
  os << "Date: " << rent.get_date() << "\n";
  os << "User id: " << rent.get_user() << "\n";
  os << "Bicycle id: " << rent.get_bicycle() << "\n";
  os << "Has ended: " << (rent.get_has_ended() ? "true" : "false") << " }\n";
  return os;
}