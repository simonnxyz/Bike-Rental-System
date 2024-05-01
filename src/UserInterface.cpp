#include "../include/UserInterface.h"

void UserInterface::print_starting_text(int width, std::string text_color, std::string border_color) const
{
    if(width < 40 || width > 200)
        width = 100;
    print_char('=', width, true, border_color, true, 10);
    std::string title_text = "=== WITAMY W ROWEROWNI ===";
    std::cout << std::endl;
    print_char(' ', (width - title_text.length())/2, false);
    std::cout << get_color_code(true, text_color) << title_text << get_color_code(false, "reset");
    std::cout << std::endl << std::endl << get_color_code(false, "reset");
    print_starting_menu(width, text_color, border_color);
}

void UserInterface::print_starting_menu(int width, std::string text_color, std::string border_color) const
{
    std::string option_1 = "1: >Pierwsza Opcja<";
    std::string option_2 = "2: >Druga Opcja<";
    std::string option_3 = "3: >Trzecia Opcja<";
    std::string option_4 = "4: >Czwarta Opcja<";
    std::string tbc = "...";

    std::vector<std::string> options;
    options.push_back(option_1);
    options.push_back(option_2);
    options.push_back(option_3);
    options.push_back(option_4);
    options.push_back(tbc);

    print_options(options, width, text_color);

    std::cout << std::endl;
    print_char('=', width, true, border_color, true, 10);
    std::cout << std::endl << get_color_code();
}
