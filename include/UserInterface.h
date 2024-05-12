#include "../include/BaseInterface.h"

class UserInterface : public BaseInterface {
public:
  // Konstruktor
  UserInterface();

  // Pętla interfejsu
  void run() override;
  void exit() override;

  // Funkcje wyświetlające interfejs
  void print_starting_text(int width = 100, std::string text_color = "cyan",
                           std::string border_color = "blue") const;
  void print_starting_menu(int width = 100, std::string text_color = "cyan",
                           std::string border_color = "blue") const;
  void print_exit() const;

  // Funkcje przekierowywujące
  void redirect_from_starting_menu(std::string text_color = "cyan",
                                   std::string border_color = "blue");

private:
  bool running;
};
