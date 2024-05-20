/*
* Name: Model.h
* Purpose: Model header file
* @author mmizia
*/

#include <iostream>
#include <map>
#include <vector>

#pragma once

class Model {
public:
  Model();

  std::string get_id() const;

  virtual void load(const std::string &data) = 0;

  virtual std::string str() = 0;

  virtual std::vector<std::string> get_attributes() const = 0;

  virtual bool
  check_query(const std::map<std::string, std::string> &query) const = 0;

protected:
  void set_id(const std::string &new_id);

private:
  std::string id;
};