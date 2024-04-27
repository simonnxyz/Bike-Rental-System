# Instrukcje utrzymywania, budowania i dodawania do programu

## Odpalanie programu

Korzystając z CMake należy stworzyć folder build i przejść do niego za pomocą

```
mkdir build
cd build
```

następnie należy użyc cmake z opcją dla odpowiedniego kompilatora np.

```bash
# windows
cmake .. -G "MinGW Makefiles"
# linux
cmake ..
```

i zbudować projekt

```bash
# windows
mingw32-make
# linux
make
```

```bash
# włączenie pliku main
./main
# włączenie testów
./google_testing
```

## Instrukcje formatowania

W środowisku visual studio code do formatowania używamy rozszerzenia:

```bash
Name: Clang-Format
Id: xaver.clang-format
Description: Use Clang-Format in Visual Studio Code
Version: 1.9.0
Publisher: Xaver Hellauer
VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=xaver.clang-format
```

oraz narzędzia clang format

klasy piszemy w następującym formacie

```cpp
class User : Model {
public:
  // constructors
  User(const std::string user_name, const std::string user_email,
       const std::string password);

  // setters
  void set_name(const std::string &name);
  void set_email(const std::string &email);

  // getters
  std::string get_name() const;
  std::string get_email() const;

  // overloaded operators
  bool operator=(const User &other);

  // other
  bool compare_password(std::string password);

private:
  std::string name;
  std::string email;
  std::string pwd_hash;
};
```