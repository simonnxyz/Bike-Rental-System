#include "../include/Bicycle.h"
#include "../include/Database.h"
#include "../include/RentalStation.h"
#include "../include/User.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

class BaseInterface {
public:
  // Konstruktor
  BaseInterface();

  virtual void run() = 0;
  virtual void exit() = 0;

  // Funkcje wyświetlające interfejs
  void print_char(char printed_char, const int char_count,
                  bool new_lines = false, std::string color = "none",
                  bool bold = false, int time = 0) const;

  void print_options(const std::vector<std::string> options, int width = 50,
                     std::string text_color = "yellow") const;

  // Funkcje pobierające wybory użytkownika
  int get_user_int_input(std::string guide = "") const;
  std::string get_user_str_input(std::string guide = "") const;
  float get_user_float_input(std::string guide = "") const;

  // Funkcje pomocnicze
  std::string get_color_code(bool bold = false,
                             const std::string color = "reset") const;
  bool is_proper_word(const std::string string) const;

  // Settery
  void set_users_data(Database<User> &new_users_data);
  void set_bikes_data(Database<Bicycle> &new_bikes_data);
  void set_admins_data(Database<User> &new_bikes_data);
  void set_station_data(Database<RentalStation> &new_bikes_data);

  // returns is_admin
  bool login();

private:
  Database<User> users_data;
  Database<User> admins_data;
  Database<Bicycle> bikes_data;
  Database<RentalStation> station_data;
};
