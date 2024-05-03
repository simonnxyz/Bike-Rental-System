#include <Model.h>
#include <Bicycle.h>
#include <vector>
#pragma once

class RentalStation : public Model {
public:
  // constructors
  RentalStation() = default;
  RentalStation(const std::string &name, const double &x, const double &y,
                const int &capacity);
  
  // virtuals
  virtual void load(const std::string &data) override;
  virtual std::string str() override;
  virtual std::vector<std::string> get_attributes() const override;
  virtual bool
  check_query(const std::map<std::string, std::string> &query) const override;

  // setters
  void set_name(const std::string &name);
  void set_x(const double &x);
  void set_y(const double &y);
  void set_capacity(const int &capacity);
  void set_empty_spaces(const int &empty_spaes);

  // getters
  std::string get_name() const;
  double get_x() const;
  double get_y() const;
  int get_capacity() const;
  int get_empty_spaces() const;

  // operators
  bool operator==(const RentalStation& other) const;
  bool operator!=(const RentalStation& other) const;
  friend std::ostream& operator<<(std::ostream& os, const RentalStation& rentalStation);

private:
  std::string name;
  double x, y;
  int capacity;
  int empty_spaces;
};