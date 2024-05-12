#include "../include/UserInterface.h"

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
  std::string title_text = "=== WITAMY W ROWEROWNI ===";
  std::cout << std::endl;
  print_char(' ', (width - title_text.length()) / 2, false);
  std::cout << get_color_code(true, text_color) << title_text
            << get_color_code(false, "reset");
  std::cout << std::endl << std::endl << get_color_code(false, "reset");
}

void UserInterface::print_starting_menu(int width, std::string text_color,
                                        std::string border_color) const {
  std::string option_1 = "1: >Wybierz punkt wypożyczenia<";
  std::string option_2 = "2: >Wyświetl saldo<";
  std::string option_3 = "3: >Doładuj środki<";
  std::string option_4 = "4: >Wyświetl informacje o koncie<";
  std::string option_5 = "5: >Wyświetl historię wypożyczeń<";
  std::string option_6 = "6: >Wyjdź<";

  std::vector<std::string> options;
  options.push_back(option_1);
  options.push_back(option_2);
  options.push_back(option_3);
  options.push_back(option_4);
  options.push_back(option_5);
  options.push_back(option_6);

  print_options(options, width, text_color);

  std::cout << std::endl;
  print_char('=', width, true, border_color, true, 10);
  std::cout << std::endl << get_color_code();
}

void UserInterface::redirect_from_starting_menu(std::string text_color,
                                                std::string border_color) {
  std::cout << get_color_code(true, "cyan");
  int choice = get_user_int_input("Wybierz opcję");
  std::cout << get_color_code() << std::endl;

  // Szkielet funkcji, jak już będzie wiadomo co i jak można w miejsca wyjść
  // konsoli wrzucić odpowiednie funkcje z innych klas wraz z jakąś graficzną
  // reprezentacją.
  if (choice == 1) {
    // Wybranie punktu wypożyczenia (następnie wybranie również roweru)
    std::cout << "Wybrano opcję 1\n";
    // TODO: logika wyświetlania oraz wyboru stacji rowerowych i znajdujących
    // się w nich rowerów
  } else if (choice == 2) {
    // Wyświetlenie salda
    print_char('=', 100, true, "blue", true);
    std::cout << get_color_code(true, "cyan") << "\nTwoje saldo wynosi: ";
    // TODO: logika wyświetlania salda użytkownika
    std::cout << std::endl << get_color_code();
  } else if (choice == 3) {
    // Doładowanie środków
    print_char('=', 100, true, "blue", true);
    float value = get_user_float_input("Podaj wartość doładowania");
    std::cout << std::endl
              << std::endl
              << get_color_code(false, "cyan")
              << "Pomyślnie wpłacono kwotę o wartości: "
              << get_color_code(true, "green") << value
              << get_color_code(false, "cyan") << " złotych na twoje konto!\n\n"
              << get_color_code();
    // TODO: logika zwiększania salda użytkownika o podaną wartość

  } else if (choice == 4) {
    // Wyświetlenie informacji o koncie
    print_char('=', 100, true, "blue", true);
    std::cout << get_color_code(true, "blue") << " == Twoje Konto ==\n\n"
              << get_color_code(true, "cyan") << ">> Nazwa: "
              << "\n>> Email: " << std::endl;
  } else if (choice == 5) {
    // Wyświetlenie historii wypożyczeń
    print_char('=', 100, true, "blue", true);
    std::cout << get_color_code(true, "cyan") << " == HISTORIA ==\n\n";
    // TODO: logika wyświetlająca historię wczęśniejszych wypożyczeń
    std::cout << get_color_code();

  } else if (choice == 6) {
    // Wyjście
    exit();
  } else {
    std::cout << "Wybierz jedną z dostępnych opcji (1-6)\n";
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