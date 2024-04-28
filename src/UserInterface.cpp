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

void UserInterface::print_options(const std::vector<std::string> options, int width,
     std::string text_color) const
{
    int longest_option = 0;
    for(const std::string option : options)
    {
        if(option.length() > longest_option)
            longest_option = option.length();
    }

    for(const std::string option : options)
    {
        print_char(' ', int((width - longest_option)/2), false);
        std::cout << get_color_code(false, text_color) << option << get_color_code(false, "reset") << std::endl;
    }
}

int UserInterface::get_user_int_input(std::string guide) const
{
    std::string str_input;
    int int_input;
    bool correct_input = false;

    while (!correct_input)
    {
        std::cout << "\n >>> " << guide << ": ";
        std::getline(std::cin, str_input);
        try
        {
            int_input = std::stoi(str_input);
            correct_input = true;
        }
        catch (const std::invalid_argument& exception)
        {
            std::cerr << "Wprowadzono niepoprawny typ argumentu (oczekiwany typ: int)\n";
        }
    }
    return int_input;
}

bool UserInterface::is_proper_word(const std::string string) const
{
	for (char c : string)
	{
		if (!std::isalpha(c))
		{
			if ((c != '"') && (c != '.') && (c != ',') && (c != ' ') && (c != '!'))
				return false;
		}
	}
	return true;
}

std::string UserInterface::get_user_str_input(std::string guide) const
{
    std::string input;
    bool correct_input = false;

    while(!correct_input)
    {
        try
        {
            std::cout << "\n >>> " << guide << ": ";
            std::getline(std::cin, input);
            correct_input = is_proper_word(input);
            if(!correct_input)
                throw std::invalid_argument("Wprowadzono niepoprawny typ argumentu (oczekiwany typ: string)");
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return input;
}


std::string UserInterface::get_color_code(bool bold, const std::string color) const
{
    std::string output = "";
    std::map<std::string, std::string> color_codes =
    {
        {"reset", "\033[0m"},
        {"black", "\033[30m"},
        {"red", "\033[31m"},
        {"green", "\033[32m"},
        {"yellow", "\033[33m"},
        {"blue", "\033[34m"},
        {"magenta", "\033[35m"},
        {"cyan", "\033[36m"},
        {"white", "\033[37m"}
    };
    if (color_codes.count(color) == 0)
        output += color_codes["reset"];
    else
        output += color_codes[color];
    if(bold)
        output += "\033[1m";
    return output;
}

void UserInterface::print_char( char printed_char, const int char_count,
 bool new_lines, std::string color, bool bold, int time) const
{
    if(new_lines)
        std::cout << std::endl;
    if(color != "none")
        std::cout << get_color_code(bold, color);
    for (int i = 0; i < char_count; i++)
    {
        Sleep(time);
        std::cout << printed_char;
    }
    if(new_lines)
        std::cout << std::endl;

}

