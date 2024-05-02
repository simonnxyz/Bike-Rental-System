#include"../include/BaseInterface.h"

struct UserInterface: public BaseInterface
{
    // Konstruktor
    UserInterface() {};

    // Funkcje wyświetlające interfejs
    void print_starting_text(int width=100, std::string text_color = "cyan", std::string border_color="blue") const;
    void print_starting_menu(int width=100, std::string text_color = "cyan", std::string border_color="blue") const;

    // Funkcje przekierowywujące
    void redirect_from_starting_menu(std::string text_color= "cyan", std::string border_color="blue") const;
};
