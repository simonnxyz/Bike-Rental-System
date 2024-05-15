#include "../include/BaseInterface.h"

BaseInterface::BaseInterface() {
  std::fstream date_file("../database/date.txt");
  std::string date_str;
  date_file >> date_str;
  current_date = Date(date_str);
};

BaseInterface::~BaseInterface() { save_date(); }

void BaseInterface::save_date() {
  std::ofstream date_file("../database/date.txt", std::ios::trunc);
  date_file.write(current_date.str().c_str(), 10);
  date_file.close();
}

void BaseInterface::print_options(const std::vector<std::string> options,
                                  int width, std::string text_color) const {
  int longest_option = 0;
  for (const std::string option : options) {
    if (option.length() > longest_option)
      longest_option = option.length();
  }

  for (const std::string option : options) {
    print_char(' ', int((width - longest_option) / 2), false);
    std::cout << get_color_code(false, text_color) << option << get_color_code()
              << std::endl;
  }
}

int BaseInterface::get_user_int_input(std::string guide) const {
  std::string str_input;
  int int_input;
  bool correct_input = false;

  while (!correct_input) {
    std::cout << "\n >>> " << guide << ": ";
    std::getline(std::cin, str_input);
    try {
      int_input = std::stoi(str_input);
      correct_input = true;
    } catch (const std::invalid_argument &exception) {
      std::cerr
          << "Wprowadzono niepoprawny typ argumentu (oczekiwany typ: int)\n";
    }
  }
  return int_input;
}

float BaseInterface::get_user_float_input(std::string guide) const {
  std::string str_input;
  float float_input;
  bool correct_input = false;

  while (!correct_input) {
    std::cout << "\n >>> " << guide << ": ";
    std::getline(std::cin, str_input);
    try {
      float_input = std::stof(str_input);
      correct_input = true;
    } catch (const std::invalid_argument &exception) {
      std::cerr
          << "Wprowadzono niepoprawny typ argumentu (oczekiwany typ: float)\n";
    }
  }
  return float_input;
}

double BaseInterface::get_user_double_input(std::string guide) const {
  std::string str_input;
  double double_input;
  bool correct_input = false;

  while (!correct_input) {
    std::cout << "\n >>> " << guide << ": ";
    std::getline(std::cin, str_input);
    try {
      double_input = std::stod(str_input);
      correct_input = true;
    } catch (const std::invalid_argument &exception) {
      std::cerr
          << "Wprowadzono niepoprawny typ argumentu (oczekiwany typ: double)\n";
    } catch (const std::out_of_range &exception) {
      std::cerr << "Wprowadzona liczba jest poza zakresem typu double\n";
    }
  }
  return double_input;
}

bool BaseInterface::is_proper_word(const std::string string) const {
  for (char c : string) {
    if (!std::isalpha(c)) {
      if ((c != '"') && (c != '.') && (c != ',') && (c != ' ') && (c != '!'))
        return false;
    }
  }
  return true;
}

std::string BaseInterface::get_user_str_input(std::string guide) const {
  std::string input;
  bool correct_input = false;

  while (!correct_input) {
    try {
      std::cout << "\n >>> " << guide << ": ";
      std::getline(std::cin, input);
      // correct_input = is_proper_word(input);
      correct_input = true;
      if (!correct_input)
        throw std::invalid_argument(
            "Wprowadzono niepoprawny typ argumentu (oczekiwany typ: string)");
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
  return input;
}

std::string BaseInterface::get_color_code(bool bold,
                                          const std::string color) const {
  std::string output = "";
  std::map<std::string, std::string> color_codes = {
      {"reset", "\033[0m"},    {"black", "\033[30m"},  {"red", "\033[31m"},
      {"green", "\033[32m"},   {"yellow", "\033[33m"}, {"blue", "\033[34m"},
      {"magenta", "\033[35m"}, {"cyan", "\033[36m"},   {"white", "\033[37m"}};
  if (color_codes.count(color) == 0)
    output += color_codes["reset"];
  else
    output += color_codes[color];
  if (bold)
    output += "\033[1m";
  return output;
}

void BaseInterface::print_char(char printed_char, const int char_count,
                               bool new_lines, std::string color, bool bold,
                               int time) const {
  if (new_lines)
    std::cout << std::endl;
  if (color != "none")
    std::cout << get_color_code(bold, color);
  for (int i = 0; i < char_count; i++) {
    std::cout << printed_char;
  }
  std::cout << get_color_code();
  if (new_lines)
    std::cout << std::endl;
}

// returns is_admin
bool BaseInterface::login() {
  int width = 100;
  std::string border_color = "blue";
  std::string login;
  std::string password;
  bool logged_in = false;
  bool is_admin = false;
  while (!logged_in) {
    print_char('=', width, true, border_color, true, 10);
    std::string title_text = "=== WITAMY W ROWEROWNI ===";
    std::string register_success = "=== Zarejestrowano ===";
    std::string login_success = "=== Zalogowano ===";
    std::string login_fail = "=== Nie ma takiego użytkownika ===";
    std::cout << std::endl;

    print_char(' ', (width - title_text.length()) / 2, false);
    std::cout << get_color_code(true, border_color) << title_text;
    std::cout << std::endl << std::endl << get_color_code();
    // print login options
    std::vector<std::string> options = {"1. Login", "2. Rejestracja"};
    print_options(options, width, "cyan");
    print_char('=', width, true, "blue", true);
    std::cout << get_color_code(true, "cyan");

    int choice = get_user_int_input("Wybierz opcję");
    std::cout << get_color_code();
    print_char('=', width, true, "blue", true);
    if (choice > 2 || choice < 1) {
      std::cerr << "Niepoprawny wybór\n";
      continue;
    }

    std::cout << get_color_code(true, "blue") << options[choice - 1]
              << get_color_code() << std::endl;
    std::string login = get_user_str_input("Email");
    std::string password = get_user_str_input("Password");

    if (choice == 2) {
      // register
      std::string name = get_user_str_input("Name");
      std::unique_ptr<User> user =
          std::make_unique<User>(name, login, password);
      users_data.add(std::move(user));
      print_char(' ', (width - register_success.length()) / 2, false);
      std::cout << get_color_code(true, border_color) << register_success;
      std::cout << std::endl << std::endl << get_color_code();
    } else {
      for (auto &admin : admins_data) {
        if (admin->get_email() == login && admin->compare_password(password)) {
          set_user(admin.get());
          logged_in = true;
          is_admin = true;
        }
      }
      for (auto &user : users_data) {
        if (user->get_email() == login && user->compare_password(password)) {
          set_user(user.get());
          logged_in = true;
        }
      }

      if (logged_in) {
        print_char(' ', (width - login_success.length()) / 2, false);
        std::cout << get_color_code(true, border_color) << login_success;
        std::cout << std::endl << std::endl << get_color_code();
      } else {
        print_char(' ', (width - login_fail.length()) / 2, false);
        std::cout << get_color_code(true, "red") << login_fail;
        std::cout << std::endl << std::endl << get_color_code();
      }
    }
  }

  std::cout << get_color_code(false, "reset");
  return is_admin;
}

void BaseInterface::set_users_data(Database<User> &new_users_data) {
  users_data = std::move(new_users_data);
}
void BaseInterface::set_bikes_data(Database<Bicycle> &new_bikes_data) {
  bikes_data = std::move(new_bikes_data);
}
void BaseInterface::set_admins_data(Database<User> &new_admins_data) {
  admins_data = std::move(new_admins_data);
}
void BaseInterface::set_station_data(
    Database<RentalStation> &new_station_data) {
  station_data = std::move(new_station_data);
}

void BaseInterface::set_rentals_data(Database<Rent> &new_rentals_data) {
  rent_data = std::move(new_rentals_data);
}

void BaseInterface::set_user(User *user) { user_ptr = user; };
User *BaseInterface::get_user() { return user_ptr; };