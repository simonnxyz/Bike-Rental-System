#include <Model.h>
#include <Bicycle.h>
#include <vector>
#pragma once

class RentalStation : public Model {
public:
  // constructors
  RentalStation() = default;
  RentalStation(const std::string &name, const double &x, const double &y,
                const int &capacity, const std::vector<Bicycle> &bicycles);
  RentalStation(const std::string &name, const double &x, const double &y,
                const int &capacity);
  
  // virtuals
  virtual void load(const std::string &data) override;
  virtual std::string str() override;
  virtual std::vector<std::string> get_attributes() const override;
  virtual bool
  check_query(const std::map<std::string, std::string> &query) const override;

  // setters
  void setName(const std::string &name);
  void setX(const double &x);
  void setY(const double &y);
  void setCapacity(const int &capacity);
  void setBicycles(const std::vector<Bicycle> &bicycles);

  // getters
  std::string getName() const;
  double getX() const;
  double getY() const;
  int getCapacity() const;
  std::vector<Bicycle> getBicycles() const;

  // operators
  bool operator==(const RentalStation& other) const;
  bool operator!=(const RentalStation& other) const;
  friend std::ostream& operator<<(std::ostream& os, const RentalStation& rentalStation);

private:
  std::string name;
  double x, y;
  int capacity;
  std::vector<Bicycle> bicycles;
};