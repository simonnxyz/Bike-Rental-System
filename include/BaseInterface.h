#include<string>
#include<iostream>
#include<map>
#include<vector>

class BaseInterface
{
    public:

    // Konstruktor
    BaseInterface()
    {};
    virtual void run() = 0;
    virtual void exit() = 0;

    // Funkcje wyświetlające interfejs
    void print_char( char printed_char, const int char_count, bool new_lines = false,
     std::string color = "none", bool bold = false, int time=0) const;

    void print_options(const std::vector<std::string> options, int width=50,
     std::string text_color = "yellow") const;


    // Funkcje pobierające wybory użytkownika
    int get_user_int_input(std::string guide="") const;
    std::string get_user_str_input(std::string guide="") const;
    float get_user_float_input(std::string guide="") const;

    // Funkcje pomocnicze
    std::string get_color_code(bool bold=false, const std::string color="reset") const;
    bool is_proper_word(const std::string string) const;
};
