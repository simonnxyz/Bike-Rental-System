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

Zadaniem klasy 'BaseInterface' jest stworzenie solidnych fundamentów pod dziedziczące po niej inne klasy tworzące interfejs. Jej funkcjonalność opiera się na formatowaniu oraz odpowiednim wyświetlaniu znaków, oraz pobierania danych od użytkownika.

### Funkcje
- `void print_char(char printed_char, const int char_count, bool new_lines = false, std::string color = "none", bool bold = false, int time=0) const` :
    Pozwala na szybkie oraz wygodne zwrócenie w konsoli ciągu znaków. Służy głównie do tworzenia ramek, oraz pustych obszarów interfejsu.
- `void print_options(const std::vector<std::string> options, int width=50, std::string text_color = "yellow") const` :
     Umożliwia wygodne wyświetlenie odpowiednio sformatowanych opcji do wyboru dla użytkownika.
- `int get_user_int_input(std::string guide="") const` :
    Pobiera od użytkownika dane typu int.
- `std::string get_user_str_input(std::string guide="") const` :
    Pobiera od użytkownika dane typu string.
- `std::string get_color_code(bool bold=false, const std::string color="reset") const` :
    Formatuje tekst by nadać mu odpowiedni kolor.
- `bool is_proper_word(const std::string string) const` :
    Sprawdza poprawność podanego ciągu znaków.

## Klasa UserInterface

Autor: **Michał Pędziwiatr**

Klasa 'UserInterface' to klasa dziedzicząca po 'BaseInterface', której zadaniem jest stworzenie przejrzystego i funkcjonalnego interfejsu dla użytkownika programu.

### Funkcje
-  `void print_starting_text(int width=100, std::string text_color = "cyan", std::string border_color="blue") const` :
    Wyświetla tytułowy tekst programu.
- `void print_starting_menu(int width=100, std::string text_color = "cyan", std::string border_color="blue") const` :
    Wyświetla menu startowe interfejsu użytkownika.
- `void redirect_from_starting_menu(std::string text_color= "cyan", std::string border_color="blue") const` :
    Pobiera oraz interpretuje wybór użytkownika, odpowiednio przekierowywując go do dalszych funkcji.


