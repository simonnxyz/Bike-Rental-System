# Symulator wypożyczalni rowerów miejskich.

Aplikacja umożliwia dodawanie nowych kont użytkowników, rowerów, punktów dostępu. Informacje o użytkownikach, rowerach, punktach dostępu oraz wypożyczeniach są zapisywane do plików txt. Uruchomienie symulatora rozpocznie proces logowania, gdzie użytkownik może wpisać adres email lub numer telefonu oraz hasło, ewentualnie założyć nowe konto podając wszystkie potrzebne do tego dane. Użytkownicy mogą sprawdzić lub doładować stan konta, wyświetlić informacje o swoim koncie, historii wypożyczeń, otrzymać listę stacji wypożyczeń oraz aktualnie dostępne w nich rowery, wypożyczyć lub zwrócić jeden z nich. Administratorzy mają pełny dostęp do aplikacji. Oznacza to, że mogą dodawać/usuwać punkty wypożyczeń, rowery, czy konta użytkowników.

## Klasa Database

Autor: **Michał Mizia**

Klasa `Database` reprezentuje bazę danych obiektów, które dziedziczą po klasie `Model`. Zapewnia funkcje takie jak find, remove, extract etc. Dane są automatycznie zapisywane do pliku, gdy obiekt `Database` wyjdzie z zakresu(zostanie zniszczony), eliminując potrzebę ręcznego zapisywania.

- `T`: Typ obiektów przechowywanych w bazie danych. `T` musi być podklasą `Model`.
- Użycie: `Database<User> db("../database/users.txt");`

### Funkcje

- `~Database()`: Niszczy obiekt `Database` i automatycznie zapisuje dane do pliku.
- `T *find_by_id(const std::string &id)`: Wyszukuje `Model` w bazie danych według jego ID.
- `T *find(const std::map<std::string, std::string> &query)`: Wyszukuje `Model` w bazie danych na podstawie zapytania.
- `T *add(std::unique_ptr<T> obj)`: Dodaje `Model` do bazy danych.
- `Użycie db.add(std::move(the_unique_ptr_to_model));`
- `T *extract(const std::map<std::string, std::string> &query)`: Usuwa `Model` z `Database` i zwraca do niego wskaźnik.
- `bool remove(const std::map<std::string, std::string> &query)`: Usuwa `Model` z `Database`.
- `int size() const`: Zwraca liczbę obiektów `Model` w `Database`.
- `void load(std::istream &file)`: Ładuje dane z strumienia wejściowego do `Database`.
- `void save(std::ostream &file)`: Zapisuje dane w `Database` do strumienia wyjściowego.
- `T *operator[](int ind)`: Zwraca wskaźnik do `Model` na określonym indeksie.

### Iteratory

Dodatkowo `Database` dostarcza funkcje do iteracji przez co możliwe jest
`for(auto &member : db) {};`

# Klasa Model

Autor: **Michał Mizia**

Klasa `Model` jest bazową klasą utrzymywaną w bazie danych, wszystkie klasy w niej przechowywane dziedziczą po niej. Umożliwia ładowanie danych z std::string oraz do std::string, sprawdzenie czy wyszukanie użytkownika zgadza się z atrybutami klasy oraz zwrócenie listy atrybutów po której można wyszukiwać

## Funkcje członkowskie

- `Model()`: Konstruuje obiekt `Model` i tworzy dla niego losowe uuid po którym można później wyszukiwać dane.
- `std::string get_id() const`: Zwraca ID modelu.
- `virtual void load(const std::string &data) = 0`: Wczytuje dane do modelu z std::string.
- `virtual std::string str() = 0`: Zwraca std::string reprezentujący model w bazie danych.
- `virtual std::vector<std::string> get_attributes() const = 0`: Zwraca atrybuty po których można wyszukiwać.
- `virtual bool check_query(const std::map<std::string, std::string> &query) const = 0`: Sprawdza, czy model spełnia zapytanie określone przez użytkownika. Zapytanie jest przekazywane jako std::map, gdzie kluczem jest nazwa atrybutu, a wartością - oczekiwana wartość atrybutu.

- `protected: void set_id(const std::string &new_id)`: Ustawia ID modelu, do użycia w klasach pochodnych. Klauzula protected zapewnia że ID modelu nie jest modyfikowane po utworzeniu modelu(chyba że przez klasę dziedziczącą w funkcji load).

## Klasa BaseInterface

Autor: **Michał Pędziwiatr**

Zadaniem klasy `BaseInterface` jest stworzenie solidnych fundamentów pod dziedziczące po niej inne klasy tworzące interfejs. Jej funkcjonalność opiera się na formatowaniu i odpowiednim wyświetlaniu znaków w terminalu, oraz pobierania danych od użytkownika.

### Funkcje
-   `virtual void run() = 0`,
    `virtual void exit() = 0`:
    Funkcje wirtualne służące do uruchomienia oraz zakończenia działania pętli interfejsu.
-   `void print_char(char printed_char, const int char_count, bool new_lines = false, std::string color = "none", bool bold = false, int time=0) const` :
    Pozwala na szybkie oraz wygodne zwrócenie w konsoli ciągu znaków. Służy głównie do tworzenia ramek, oraz pustych obszarów interfejsu.
-   `void print_options(const std::vector<std::string> options, int width=50, std::string text_color = "yellow") const` :
    Umożliwia wygodne wyświetlenie odpowiednio sformatowanych opcji do wyboru dla użytkownika.
-   `int get_user_int_input(std::string guide="") const`,
    `std::string get_user_str_input(std::string guide="") const`,
    `float get_user_float_input(std::string guide="") const`,
    `double get_user_double_input(std::string guide="") const`:
    Funkcje pobierające i sprawdzające poprawność typu podanych przez użytkownika danych.
-   `void set_users_data(Database<User> & new_users_data)`,
    `void set_bikes_data(Database<Bicycle> &new_bikes_data)`,
    `void set_admins_data(Database<User> & new_admin_data)`,
    `void set_station_data(Database<RentalStation> & new_station_data)`,
    `void set_rentals_data(Database<Rent> & new_rentals)`,
    `void set_user(User *user)`:
    Settery odpowiednich obiektów klasy Database.
-   `std::string get_color_code(bool bold=false, const std::string color="reset") const` :
    Formatuje tekst nadając mu odpowiedni kolor i ewentualne pogrubienie.
-   `bool is_proper_word(const std::string string) const` :
    Sprawdza czy podany ciąg znaków jest prawidłowym słowem (czyli czy zawiera w sobie jedynie litery).
-    `bool login()`:
    Funkcja służąca do zalogowania, zwraca wartość zależną od tego czy użytkownik jest administratorem czy klientem.
-   `User *get_user()`:
    Getter zwracający wskaźnik na zalogowanego użytkownika.
-   `save_date()`:
    Funkcja nadpisująca obecną datę.

## Klasa UserInterface

Autor: **Michał Pędziwiatr**

Klasa `UserInterface` to klasa dziedzicząca po `BaseInterface`, której zadaniem jest stworzenie przejrzystego i funkcjonalnego interfejsu dla użytkownika programu.

### Funkcje
-   `void run() override`,
    `void exit() override` :
    Nadpisanie metod wirtualnych klasy BaseInterface, służących do uruchomienia i zatrzymania pętli działania interfejsu.
-  `void print_starting_text(int width=100, std::string text_color = "cyan", std::string border_color="blue") const` :
    Wyświetla tytułowy tekst programu.
-   `void print_starting_menu(int width=100, std::string text_color = "cyan", std::string border_color="blue") const` :
    Wyświetla menu startowe interfejsu użytkownika.
-   `void redirect_from_starting_menu(std::string text_color= "cyan", std::string border_color="blue") const` :
    Pobiera oraz interpretuje wybór użytkownika, odpowiednio przekierowywując go do dalszych funkcji.
-   `show_balance(std::string text_color="cyan")` :
    Wyświetla dostępne saldo użytkownika.
-   `void show_user_info(std::string text_color= "cyan")` :
    Wyświetla dane o zalogowanym użytkowniku.
-   `void show_history(std::string text_color)` :
    Wyświetla historię wypożyczeń zalogowanego użytkownika.
-   `std::vector<Bicycle*> list_available_bikes(std::string selected_station_id,
                                    std::string text_color="cyan")` :
    Zwraca wektor wskaźników do każdego dostępnego roweru na danej stacji.
-   `std::vector<Bicycle*> list_rented_bikes(std::string text_color="cyan")` :
    Zwaraca wektor wskaźników do każdego roweru, wypożyczonego obecnie przez zalogowanego użytkownika.
-   `void add_balance(std::string text_color="cyan")`
    Funkcja służąca do wpłaty podanej przez użytkownika kwoty na jego konto.
-   `RentalStation* choose_station(std::string mode="rent", std::string text_color="cyan", std::string border_color = "blue")` :
    Pozwala użytkownikowi wybrać jedną z wyświetlanych stacji.
-   `Bicycle* choose_bike(RentalStation* selected_station, std::string mode="rent", std::string text_color="cyan", std::string border_color="blue")` :
    Pozwala użytkownikowi wybrać jeden z wyświetlonych rowerów na danej stacji.
-   `void rent_bike(RentalStation* selected_station, Bicycle *selected_bike, std::string text_color= "cyan")` :
    Umożliwia wypożyczenie roweru przez użytkownika.
-   `void return_bike(RentalStation* selected_station, Bicycle *selected_bike, std::string text_color= "cyan")` :
    Umożliwia zwrot wypożyczonego przez użytkownika roweru.
-   `void print_exit() const` :
    Wyświetla tekst pożegnalny.

## Klasa Bicycle

Autor: **Kacper Siemionek**

Klasa `Bicycle` dziedziczy po klasie `Model` oraz reprezentuje rower w wypożyczalni. Zawiera nazwę, cenę związaną z wypożyczeniem roweru, ID stacji, w której obecnie się znajduje oraz znacznik dostępności. Umożliwia swobodną kontrolę nad obiektem roweru, zapis i odczyt z std::string.

## Funkcje

- `Bicycle(const std::string &name, const double &price, const std::string &station_id, const bool &is_available)` : Konstruktor tworzący nowy obiekt roweru z podanymi atrybutami.
- `void load(const std::string &data)` : Wczytuje dane o rowerze z std::string.
- `std::string str()` : Zwraca std::string z atrybutami roweru oddzielonymi przecinkami.
- `std::vector<std::string> get_attributes() const` : Zwraca atrybuty, po których można wyszukiwać.
- `bool check_query(const std::map<std::string, std::string> &query) const` : Sprawdza, czy rower spełnia zapytanie określone przez użytkownika.
- `void set_xxx(const std::string &xxx)` : Ustawia wybrany atrybut.
- `??? get_xxx() const` : Zwraca wybrany atrybut.

## Klasa RentalStation

Autor: **Kacper Siemionek**

Klasa `RentalStation` dziedziczy po klasie `Model` oraz reprezentuje stację wypożyczeń rowerów. Zawiera nazwę, współrzędne, pojemność oraz ilość wolnych miejsc na rowery. Umożliwia swobodną kontrolę nad obiektem stacji, zapis i odczyt z std::string.

## Funkcje

- `RentalStation(const std::string &name, const double &x, const double &y, const int &capacity, const int &empty_spaces)` : Konstruktor tworzący nowy obiekt stacji z podanymi atrybutami.
- `void load(const std::string &data)` : Wczytuje dane o stacji z std::string.
- `std::string str()` : Zwraca std::string z atrybutami stacji oddzielonymi przecinkami.
- `std::vector<std::string> get_attributes() const` : Zwraca atrybuty, po których można wyszukiwać.
- `bool check_query(const std::map<std::string, std::string> &query)` : Sprawdza, czy stacja spełnia zapytanie określone przez użytkownika.
- `void set_xyz(const xyz &xyz)` : Ustawia wybrany atrybut.
- `xyz get_xyz() const` : Zwraca wybrany atrybut.

## Klasa Rent

Autor: **Wojciech Zieziula**

Klasa `Rent` dziedziczy po klasie `Model`. Jej zadaniem jest reprezentacja pojedynczego wypożyczenia roweru ze stacji. Zawiera datę wypożyczenia, ID użytkownika wypożyczającego, ID wypożyczanego roweru oraz informację o tym, czy wypożyczenie zostało zakończone.

### Funkcje

- ``Rent(const std::string &date, const std::string &user_id, const std::string &bicycle_id)` : Konstruktor tworzący nowy obiekt reprezentujący wypożyczenie o podanych argumentach.
- `void load(const std::string &data)` : Wczytuje dane wypożyczenia z podanego obiektu std::string.
- `std::string str()` : Zwraca reprezentację obiektu jakos std::string. Zwrócony ciąg znaków może zostać użyty w funkcji `load` w celu wczytania danych.
- `std::vector<std::string> get_attributes()` : Zwraca atrybuty, po których można wyszukiwać.
- `bool check_query(const std::map<std::string, std::string> &query)` : Sprawdza, czy wypożyczenie spełnia zapytanie określone przez użytkownika.
- `void set_attribute(const class &object)` : Ustawia wybrany atrybut.
- `attribute_type get_attribute() const` : Zwraca wybrany atrybut.


## Klasa AdminInterface

## Klasa Date

## Klasa DragonBicycle??

## Klasa User