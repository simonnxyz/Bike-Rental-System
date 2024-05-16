#include "../include/AdminInterface.h"
#include "../include/Date.h"
#include <math.h>

AdminInterface::AdminInterface(){};

void AdminInterface::run() {
  running = true;
  while (running) {
    print_starting_text();
    print_starting_menu();
    redirect_from_starting_menu();
  }
}

void AdminInterface::print_starting_text(int width, std::string text_color,
                                         std::string border_color) const {
  if (width < 40 || width > 200)
    width = 100;
  print_char('=', width, true, border_color, true, 10);
  std::string title_text = "=== PANEL ADMINA ROWEROWNI ===\n\n";
  std::string date_str = current_date.str();
  std::cout << std::endl;
  print_char(' ', (width - title_text.length()) / 2, false);
  std::cout << get_color_code(true, text_color) << title_text
            << get_color_code(false, "reset") << std::endl;
  print_char(' ', (width - date_str.length() - 2) / 2, false);
  std::cout << get_color_code(true, text_color) << date_str
            << get_color_code(false, "reset");
  std::cout << std::endl << std::endl << get_color_code(false, "reset");
}

void AdminInterface::print_starting_menu(int width, std::string text_color,
                                         std::string border_color) const {
  std::string option_1 = "1: >Dodaj punkt wypożyczenia<";
  std::string option_2 = "2: >Dodaj rower<";
  std::string option_3 = "3: >Medytuj przez 24h<";
  std::string option_4 = "4: >Wyjdź<";

  std::vector<std::string> options;
  options.push_back(option_1);
  options.push_back(option_2);
  options.push_back(option_3);
  options.push_back(option_4);

  print_options(options, width, text_color);

  std::cout << std::endl;
  print_char('=', width, true, border_color, true, 10);
  std::cout << std::endl << get_color_code();
}

void AdminInterface::redirect_from_starting_menu(std::string text_color,
                                                 std::string border_color) {
  std::cout << get_color_code(true, text_color);
  int choice = get_user_int_input("Wybierz opcję");
  std::cout << get_color_code() << std::endl;

  if (choice == 1) {
    // add rental point
    std::string name = get_user_str_input("Podaj nazwę punktu wypożyczenia");
    double x = get_user_double_input("Podaj współrzędną x");
    double y = get_user_double_input("Podaj współrzędną y");
    int capacity = get_user_int_input("Podaj pojemność");

    std::unique_ptr<RentalStation> new_station =
        std::make_unique<RentalStation>(name, x, y, capacity, capacity);
    station_data.add(std::move(new_station));
    station_data.save();
  } else if (choice == 2) {
    // add bike
    std::string name = get_user_str_input("Podaj nazwę roweru");
    double price = get_user_double_input("Podaj cenę wypożyczenia (za dzień)");
    RentalStation *selected_station = choose_station(text_color, border_color);
    if (selected_station == nullptr) {
      return;
    }
    std::unique_ptr<Bicycle> new_bike = std::make_unique<Bicycle>(
        name, price, selected_station->get_id(), true);
    bikes_data.add(std::move(new_bike));
  } else if (choice == 3) {
    // medytuj przez 24h
    ++current_date;
    save_date();
    // Loop over users and check if they have rented bikes,
    // if so take money from their account
    for (auto &rental : rent_data) {
      if (rental->get_has_ended())
        continue;

      User *user = users_data.find_by_id(rental->get_user());
      if (user == nullptr)
        continue;

      Bicycle *bike = bikes_data.find_by_id(rental->get_bicycle());
      if (bike == nullptr)
        continue;

      user->set_balance(user->get_balance() - bike->get_price());
      if (user->get_balance() > 0)
        continue;

      // if user doesnt have any more money
      user->set_balance(0);
      // return bike
      bike->set_availability(true);
      rental->set_has_ended(true);
      // choose first station
      for (auto &station : station_data) {
        if (station->get_empty_spaces() != 0) {
          station->set_empty_spaces(station->get_empty_spaces() - 1);
          bike->set_station(station->get_id());
          break;
        }
      }
    }
    std::cout << "Medytacja zakończona (uzupełniono misktury)\n";
  } else if (choice == 7) {
    // Wyjście
    exit();
  } else if (choice == 966 || choice == 1385 || choice == 1410 ||
             choice == 1610 || choice == 1918 || choice == 1989) {
    print_char('=', 50, false, "white", true);
    print_char('=', 50, true, "red", true);
    std::cout << std::endl
              << get_color_code(true, "white") << "Chwała "
              << get_color_code(true, "red") << "Wielkiej "
              << get_color_code(true, "white") << "Polsce "
              << get_color_code(true, "red") << "!!!\n";
    print_char('=', 50, true, "white", true);
    print_char('=', 50, false, "red", true);
  } else {
    std::cout << "Wybierz jedną z dostępnych opcji (1-7)\n";
  }
}

void AdminInterface::exit() {
  print_exit();
  running = false;
}

void AdminInterface::print_exit() const {
  std::cout << std::endl
            << get_color_code(true, "blue") << "Do zobaczenia!\n\n"
            << get_color_code();
}

std::vector<Bicycle *>
AdminInterface::list_available_bikes(std::string selected_station_id,
                                     std::string text_color) {
  int counter = 0;
  std::vector<Bicycle *> available_bikes;
  for (auto &bike : bikes_data) {
    if ((bike->get_station() == selected_station_id) &&
        bike->get_availability()) {
      counter += 1;
      std::cout << "   " << counter << "> Rower: " << bike->get_name()
                << " | Cena wypożyczenia: " << bike->get_price() << " zł"
                << std::endl;
      available_bikes.push_back(bike.get());
    }
  }
  return available_bikes;
}

std::vector<Bicycle *>
AdminInterface::list_rented_bikes(std::string text_color) {

  std::vector<Bicycle *> rented_bikes;
  int counter = 0;
  for (auto &rental : rent_data) {
    if (rental->get_user() == get_user()->get_id()) {
      counter += 1;
      Bicycle *bike = bikes_data.find_by_id(rental->get_bicycle());
      std::cout << "   " << counter << "> Rower: " << bike->get_name()
                << " | Cena wypożyczenia: " << bike->get_price() << " zł"
                << std::endl;
      rented_bikes.push_back(bike);
    }
  }
  return rented_bikes;
}

RentalStation *AdminInterface::choose_station(std::string text_color,
                                              std::string border_color) {
  print_char('=', 100, true, border_color, true);
  std::cout << std::endl;
  int counter = 0;
  for (auto &station : station_data) {
    int bikes_on_station =
        station->get_capacity() - station->get_empty_spaces();
    std::cout << get_color_code(true, text_color);
    counter++;
    std::cout << "   " << counter << "> STACJA: " << station->get_name()
              << get_color_code(false, text_color)
              << " | lokalizacja: x=" << station->get_x()
              << ", y=" << station->get_y()
              << " | ilość rowerów: " << bikes_on_station << std::endl;
  }

  if (counter > 0) {
    print_char('=', 100, true, border_color, true);
    std::cout << get_color_code(true, text_color);
    int choice = get_user_int_input("Wybierz stację");
    std::cout << get_color_code();

    if (choice > counter || choice <= 0) {
      std::cout << std::endl
                << get_color_code(true, "red")
                << "Nie ma takiego punktu wypożyczenia! :(\n";
    } else {
      RentalStation *selected_station = station_data[choice - 1];
      print_char('=', 100, true, border_color, true);
      return selected_station;
    }
  } else {
    std::cout << std::endl
              << get_color_code(true, "red")
              << "Brak dostępnych punktów wypożyczenia! :(\n";
  }
  std::cout << get_color_code() << std::endl;
  return nullptr;
}