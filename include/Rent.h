#include <Model.h>

#pragma once

class Rent : public Model {
public:
  // Constructors
  Rent() = default;
  Rent(const std::string &date, const std::string &user_id,
       const std::string &bicycle_id);

  // Virtuals
  virtual void load(const std::string &data) override;
  virtual std::string str() override;
  virtual std::vector<std::string> get_attributes() const override;
  virtual bool
  check_query(const std::map<std::string, std::string> &query) const override;

  // Setters
  void set_date(const std::string &date);
  void set_user(const std::string &user_id);
  void set_bicycle(const std::string &bicycle_id);
  void set_has_ended(bool);

  // Getters
  std::string get_date() const;
  std::string get_user() const;
  std::string get_bicycle() const;
  bool get_has_ended() const;

  // Overloaded operators
  bool operator==(const Rent &other) const;
  bool operator!=(const Rent &other) const;
  friend std::ostream &operator<<(std::ostream &os, const Rent &rent);

  // Others
private:
  std::string date;
  std::string user_id;
  std::string bicycle_id;

  bool has_ended = false;
};