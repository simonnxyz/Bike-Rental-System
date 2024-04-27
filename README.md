# 209.2 Rowery miejskie

Symulator wypożyczalni rowerów miejskich. Aplikacja umożliwia dodawanie nowych kont użytkowników, rowerów, punktów dostępu. Użytkownicy mogą doładować stan konta, wypożyczyć lub zwrócić rower.

# Klasy

### 1. Aplikacja

#### Atrybuty

- kolekcja użytkowników
- kolekcja rowerów
- kolekcja punktów dostępu
- kolekcja wypożyczeń

#### Metody

- dodawanie/usuwanie użytkowników
- dodawanie/usuwanie rowerów
- dodawanie/usuwanie punktów dostępu
- dodawanie wypożyczeń

### 2. Rower (struct?)

#### Atrybuty

- cena
- historia wypożyczeń
- obecny punkt
- obecny właściciel

### 3. Wypożyczenie (struct?)

#### Atrybuty

- data wypożyczenia
- ID wypożyczenia
- użytkownik, który wypożyczył
- rower, który był wypożyczony

### 4. Punkt dostępu (struct?)

#### Atrybuty

- współrzędne
- dostępne rowery
- ilość miejsc

### 5. Konto użytkownika (w razie potrzeby zostanie dodane konto administratora)

#### Atrybuty

- imię
- nazwisko
- email
- hasło
- numer telefonu
- stan konta
- historia wypożyczeń

#### Metody

- doładowanie konta
- wypożyczenie roweru
- zwrócenie roweru

