#include "../include/UserInterface.h"
#include <math.h>

UserInterface::UserInterface(){};

void UserInterface::run() {
  running = true;
  while (running) {
    print_starting_text();
    print_starting_menu();
    redirect_from_starting_menu();
  }
}

void UserInterface::print_starting_text(int width, std::string text_color,
                                        std::string border_color) const {
  if (width < 40 || width > 200)
    width = 100;
  print_char('=', width, true, border_color, true, 10);
  std::string title_text = "=== WITAMY W ROWEROWNI ===\n\n";
  std::cout << std::endl;
  print_char(' ', (width - title_text.length()) / 2, false);
  std::cout << get_color_code(true, text_color) << title_text
            << get_color_code(false, "reset");
  std::cout << std::endl << std::endl << get_color_code(false, "reset");
}

void UserInterface::print_starting_menu(int width, std::string text_color,
                                        std::string border_color) const {
  std::string option_1 = "1: >Wybierz punkt wypożyczenia<";
  std::string option_2 = "2: >Zakończ wypożyczenie roweru<";
  std::string option_3 = "3: >Wyświetl saldo<";
  std::string option_4 = "4: >Doładuj środki<";
  std::string option_5 = "5: >Wyświetl informacje o koncie<";
  std::string option_6 = "6: >Wyświetl historię wypożyczeń<";
  std::string option_7 = "7: >Wyjdź<";

  std::vector<std::string> options;
  options.push_back(option_1);
  options.push_back(option_2);
  options.push_back(option_3);
  options.push_back(option_4);
  options.push_back(option_5);
  options.push_back(option_6);
  options.push_back(option_7);

  print_options(options, width, text_color);

  std::cout << std::endl;
  print_char('=', width, true, border_color, true, 10);
  std::cout << std::endl << get_color_code();
}

void UserInterface::redirect_from_starting_menu(std::string text_color,
                                                std::string border_color) {
  std::cout << get_color_code(true, text_color);
  int choice = get_user_int_input("Wybierz opcję");
  std::cout << get_color_code() << std::endl;

  if (choice == 1) {
    // Wybranie punktu wypożyczenia (następnie wybranie również roweru)
    RentalStation *selected_station = choose_station(text_color, border_color);
    if (selected_station) {
      Bicycle *selected_bike =
          choose_bike(selected_station, "rent", text_color, border_color);
      std::cout << selected_bike->str() << std::endl;
      if (selected_bike) {
        rent_data.add(std::make_unique<Rent>("07.08.2005", get_user()->get_id(),
                                             selected_bike->get_id()));
        if (selected_bike) {
          selected_bike->set_availability(false);
          selected_station->set_empty_spaces(
              std::max(selected_station->get_empty_spaces() + 1,
                       selected_station->get_capacity()));
        }
      }
    }
  } else if (choice == 2) {
    // Oddanie roweru na wybranej stacji
    RentalStation *selected_station = choose_station(text_color, border_color);
    if (selected_station) {
      Bicycle *selected_bike =
          choose_bike(selected_station, "return", text_color, border_color);
      if (selected_bike) {
        selected_bike->set_availability(true);
        selected_station->set_empty_spaces(
            std::max(selected_station->get_empty_spaces() - 1, 0));
        selected_bike->set_station(selected_station->get_id());
      }

      // wez wyprintuj ze zwrocono i wyzej ze wypozyczono
    }
  } else if (choice == 3) {
    // Wyświetlenie salda
    print_char('=', 100, true, border_color, true);
    show_balance(text_color);

  } else if (choice == 4) {
    // Doładowanie środków
    print_char('=', 100, true, border_color, true);
    add_balance(text_color);

  } else if (choice == 5) {
    // Wyświetlenie informacji o koncie
    print_char('=', 100, true, border_color, true);
    show_user_info(text_color);
  } else if (choice == 6) {
    // Wyświetlenie historii wypożyczeń
    print_char('=', 100, true, border_color, true);
    show_history(text_color);
    std::cout << get_color_code();

  } else if (choice == 7) {
    // Wyjście
    exit();
  } else if (choice == 966 || choice == 1385 || choice == 1410 ||
             choice == 1610 || choice == 1918 || choice == 1989) {
    std::cout << get_color_code(true, "white") << "Chwała "
              << get_color_code(true, "red") << "Wielkiej "
              << get_color_code(true, "white") << "Polsce "
              << get_color_code(true, "red") << "!!!\n";
  } else {
    std::cout << "Wybierz jedną z dostępnych opcji (1-7)\n";
  }
}

void UserInterface::exit() {
  print_exit();
  running = false;
}

void UserInterface::print_exit() const {
  std::cout << std::endl
            << get_color_code(true, "blue") << "Do zobaczenia!\n\n"
            << get_color_code();
}

void UserInterface::show_balance(std::string text_color) {
  std::cout << get_color_code(true, text_color) << "\nTwoje saldo wynosi: ";
  std::cout << get_color_code(true, "green") << get_user()->get_balance()
            << " zł";
  std::cout << std::endl << get_color_code();
}

void UserInterface::add_balance(std::string text_color) {
  std::cout << get_color_code(true, text_color);
  double value = get_user_double_input("Podaj wartość doładowania");
  std::stringstream round_stream;
  round_stream << std::fixed << std::setprecision(2) << value;
  double rounded_value;
  round_stream >> rounded_value;

  double current_balance = get_user()->get_balance();
  get_user()->set_balance(current_balance + rounded_value);

  std::cout << std::endl
            << std::endl
            << get_color_code(false, text_color)
            << "Pomyślnie wpłacono kwotę o wartości: "
            << get_color_code(true, "green") << rounded_value
            << get_color_code(false, text_color)
            << " złotych na twoje konto!\n\n"
            << get_color_code();
}

void UserInterface::show_user_info(std::string text_color) {
  std::cout << get_color_code(true, text_color) << "\n == Twoje Konto ==\n\n"
            << get_color_code(true, text_color)
            << ">> Nazwa: " << get_user()->get_name()
            << "\n>> Email: " << get_user()->get_email() << std::endl;
  std::cout << get_color_code();
}

RentalStation *UserInterface::choose_station(std::string text_color,
                                             std::string border_color) {
  print_char('=', 100, true, border_color, true);
  std::cout << std::endl;
  int counter = 0;
  for (auto &station : station_data) {
    int bikes_on_station =
        station->get_capacity() - station->get_empty_spaces();
    if (bikes_on_station >= 1) {
      std::cout << get_color_code(true, text_color);
      counter++;
      std::cout << "   " << counter << "> STACJA: " << station->get_name()
                << get_color_code(false, text_color)
                << " | lokalizacja: x=" << station->get_x()
                << ", y=" << station->get_y()
                << " | ilość rowerów: " << bikes_on_station << std::endl;
    }
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

Bicycle *UserInterface::choose_bike(RentalStation *selected_station,
                                    std::string mode, std::string text_color,
                                    std::string border_color) {
  if (selected_station) {
    std::string station_id = selected_station->get_id();
    std::cout << get_color_code(false, text_color) << std::endl;

    std::vector<Bicycle *> bikes;
    if (mode == "rent") {
      bikes = list_available_bikes(station_id, text_color);
    } else if (mode == "return") {
      bikes = list_rented_bikes(text_color);
    }

    if (!(bikes.empty())) {
      print_char('=', 100, true, border_color, true);
      std::cout << get_color_code(true, text_color);
      int choice = get_user_int_input("Wybierz rower");
      std::cout << get_color_code() << std::endl;

      if ((choice > bikes.size()) || choice <= 0) {
        std::cout << std::endl
                  << get_color_code(true, "red")
                  << "Nie ma takiego roweru! :(\n";
      } else {
        std::cout << bikes[choice - 1]->str() << std::endl;
        Bicycle *selected_bike = bikes[choice - 1];
        return selected_bike;
      }
    } else {
      std::cout << std::endl
                << get_color_code(true, "red")
                << "Brak dostępnych rowerów! :(\n";
    }
  } else {
    std::cerr << std::endl
              << get_color_code(true, "red")
              << "Błąd przy wczytywaniu stacji! :(\n";
  }
  return nullptr;
}

std::vector<Bicycle *>
UserInterface::list_available_bikes(std::string selected_station_id,
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
UserInterface::list_rented_bikes(std::string text_color) {

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

void UserInterface::show_history(std::string text_color) {
  std::cout << get_color_code(false, text_color) << std::endl;
  int counter = 0;
  for (auto &rental : rent_data) {
    std::cout << "wchodzimy do petli";
    if (rental->get_user() == get_user()->get_id()) {
      counter += 1;
      if (counter == 1)
        std::cout << get_color_code(true, "cyan") << " == HISTORIA ==\n\n";
      std::cout << "> " << counter << ": " << rental->get_date()
                << " wypożyczono rower: " << rental->get_bicycle() << std::endl;
    }
  }
  if (counter < 1) {
    std::cout << std::endl
              << get_color_code(true, "red")
              << "Jeszcze nie wypożyczono żadnego roweru\n";
  }
  std::cout << std::endl;
}
