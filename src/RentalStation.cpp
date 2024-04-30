#include "../include/RentalStation.h"
#include <regex>


RentalStation::RentalStation(const std::string &name, const double &x,
                             const double &y, const int &capacity,
                             const std::vector<Bicycle> &bicycles) {
  if (capacity < 1) { throw std::invalid_argument("Pojemoność nie może być mniejsza od 1.")};
  this->name = name;
  this->x = x;
  this->y = y;
  this->capacity = capacity;
  this->bicycles = bicycles;
}

RentalStation::RentalStation(const std::string &name, const double &x,
                             const double &y, const int &capacity) {
  if (capacity < 1) { throw std::invalid_argument("Pojemoność nie może być mniejsza od 1.")};
  this->name = name;
  this->x = x;
  this->y = y;
  this->capacity = capacity;
  std::vector<Bicycle> bicycles_empty;
  this->bicycles = bicycles_empty;
}
