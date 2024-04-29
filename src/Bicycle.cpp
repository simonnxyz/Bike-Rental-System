#include "../include/Bicycle.h"
#include "../include/SHA256.h"
#include <regex>

Bicycle::Bicycle(const std::string &name, const double &price,
                    const std::string &station_id, const bool &is_available) {
  if (price < 0) { throw std::invalid_argument("Cena nie może być ujemna.");};
  this->name = name;
  this->price = price;
  this->station_id = station_id;
  this->is_available = is_available;
};

// virtuals
void Bicycle::load(const std::string &data) {
  // load bicycle from line data
  // format: id,name,price,station_id,is_available
  std::vector<std::string> parts;
  std::string part;
  std::istringstream ss(data);
  bool is_available = false;
  while (std::getline(ss, part, ',')) {
    parts.push_back(part);
  }

  if (parts.size() != 5) {
    throw std::invalid_argument("Nieprawidłowy format danych: " + data);
  }
  set_id(parts[0]);
  set_name(parts[1]);
  set_price(std::stod(parts[2]));
  set_station(parts[3]);
  set_availability(parts[4] == "1");
};

std::string Bicycle::str() {
  return get_id() + "," + get_name() + "," + std::to_string(get_price()) +
  "," + get_station() + "," + std::to_string(get_availability());
};

std::vector<std::string> Bicycle::get_attributes() const {
  return {"id", "name", "price", "station_id", "is_available"};
};

bool Bicycle::check_query(const std::map<std::string, std::string> &query) const {
std::map<std::string, std::string> bike_map = {
      {"id", get_id()}, {"name", get_name()},
      {"price", std::to_string(get_price())},
      {"station_id", get_station()},
      {"is_available", std::to_string(get_availability())}};
  for (auto const &pair : query) {
    auto it = bike_map.find(pair.first);
    if (it != bike_map.end() && it->second == pair.second) {
      continue;
    }
    return false;
  }
  return true;
};

// setters
void Bicycle::set_name(const std::string &name) {
  this->name = name;
};

void Bicycle::set_price(const double &price) {
  if (price < 0) {
    throw std::invalid_argument("Cena nie może być ujemna.");
  }
  this->price = price;
};

void Bicycle::set_station(const std::string &station_id) {
  this->station_id = station_id;
};

void Bicycle::set_availability(const bool &is_available) {
  this->is_available = is_available;
};

// getters
std::string Bicycle::get_name() const { return name; };
double Bicycle::get_price() const { return price; };
std::string Bicycle::get_station() const { return station_id; };
bool Bicycle::get_availability() const { return is_available; };

// overloaded operators
bool Bicycle::operator==(const Bicycle& other) const {
  return (get_id() == other.get_id());
};

bool Bicycle::operator!=(const Bicycle& other) const {
  return !(*this == other);
};

std::ostream& operator<<(std::ostream& os, const Bicycle& bicycle) {
  os << "{ Id: " << bicycle.get_id() << '\n';
  os << "Name: " << bicycle.get_name() << '\n';
  os << "Price: " << std::to_string(bicycle.get_price()) << '\n';
  os << "Station: " << bicycle.get_station() << '\n';
  std::string availability = "false";
  if (bicycle.get_availability()) { availability = "true";};
  os << "Is available: " << availability << " }\n";
  return os;
};