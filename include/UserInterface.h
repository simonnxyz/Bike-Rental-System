#include "../include/BaseInterface.h"
#include<sstream>
#include<iomanip>

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
  void show_balance(std::string text_color="cyan");
  void add_balance(std::string text_color="cyan");
  void show_user_info(std::string text_color= "cyan");
  RentalStation* choose_station(std::string text_color="cyan", std::string border_color = "blue");
  Bicycle* choose_bike(RentalStation* selected_station, std::string mode="rent", std::string text_color="cyan", std::string border_color="blue");
  std::vector<Bicycle*> list_available_bikes(std::string selected_station_id,
                                    std::string text_color="cyan");
  std::vector<Bicycle*> list_rented_bikes(std::string text_color="cyan");
  void show_history(std::string text_color);

  void print_exit() const;


  // Funkcje przekierowywujące
  void redirect_from_starting_menu(std::string text_color = "cyan",
                                   std::string border_color = "blue");

private:
  bool running;
};
