#include <iostream>

#pragma once

class Model {
public:
  Model();

  std::string get_id() const;
  void set_id(const std::string &id);

private:
  std::string id;
};