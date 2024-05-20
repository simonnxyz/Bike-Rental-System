/*
* Name: Bicycle.h
* Purpose: Bicycle header file
* @author ksiemion
*/

#include <Model.h>
#include <iostream>
#pragma once

class Bicycle : public Model {
public:
  // constructors
  Bicycle() = default;
  Bicycle(const std::string &name, const double &price,
          const std::string &station_id, const bool &is_available);

  // virtuals
  virtual void load(const std::string &data) override;
  virtual std::string str() override;
  virtual std::vector<std::string> get_attributes() const override;
  virtual bool
  check_query(const std::map<std::string, std::string> &query) const override;

  // setters
  void set_name(const std::string &name);
  void set_price(const double &price);
  void set_station(const std::string &station_id);
  void set_availability(const bool &availability);

  // getters
  std::string get_name() const;
  double get_price() const;
  std::string get_station() const;
  bool get_availability() const;

  // overloaded operators
  bool operator==(const Bicycle &other) const;
  bool operator!=(const Bicycle &other) const;
  friend std::ostream &operator<<(std::ostream &os, const Bicycle &bicycle);

  // other
private:
  std::string name;
  double price;
  std::string station_id;
  bool is_available;
};