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
