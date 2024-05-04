#include <Model.h>
#include <iostream>

#pragma once

class User : public Model {
public:
  // constructors
  User() = default;
  User(const std::string &user_name, const std::string &user_email,
       const std::string &password, const double &balance);
  User(const std::string &user_name, const std::string &user_email,
       const std::string &password);

  // virtuals
  virtual void load(const std::string &data) override;
  virtual std::string str() override;
  virtual std::vector<std::string> get_attributes() const override;
  virtual bool
  check_query(const std::map<std::string, std::string> &query) const override;

  // setters
  void set_name(const std::string &name);
  void set_email(const std::string &email);
  void set_balance(const double &new_balance);

  // getters
  std::string get_name() const;
  std::string get_email() const;
  double get_balance() const;

  // overloaded operators
  bool operator==(const User &other);
  friend std::ostream &operator<<(std::ostream &os, const User &user);

  // other
  bool compare_password(const std::string &password);

private:
  std::string name;
  std::string email;
  std::string pwd_hash;
  double balance;
};