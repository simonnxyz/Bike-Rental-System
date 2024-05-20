/*
* Name: Date.cpp
* Purpose: Date methods
* @author mmizia
*/

#include "../include/Date.h"
#include <iomanip>


//Constructors
Date::Date(const int &day, const int &month, const int &year) {
  if (is_valid_date(day, month, year) == false) {
    throw std::invalid_argument("Invalid date");
  }

  this->day = day;
  this->month = month;
  this->year = year;
}

// format DD/MM/YYYY
Date::Date(const std::string &date) {
  int day = std::stoi(date.substr(0, 2));
  int month = std::stoi(date.substr(3, 2));
  int year = std::stoi(date.substr(6, 4));

  if (is_valid_date(day, month, year) == false) {
    throw std::invalid_argument("Invalid date");
  }

  this->day = day;
  this->month = month;
  this->year = year;
}

Date::Date() {
  // get the system date
  time_t now = time(0);
  tm *ltm = localtime(&now);

  day = ltm->tm_mday;
  month = ltm->tm_mon + 1; // tm_mon is in the range [0, 11], so add 1
  year = ltm->tm_year +
         1900; // tm_year is the number of years since 1900, so add 1900
}

//Setters
void Date::set_day(const int &day) {
  if (is_valid_date(day, this->month, this->year) == false) {
    throw std::invalid_argument("Invalid day" + std::to_string(day));
  }

  this->day = day;
}

void Date::set_month(const int &month) {
  if (is_valid_date(this->day, month, this->year) == false) {
    throw std::invalid_argument("Invalid month" + std::to_string(month));
  }

  this->month = month;
}

void Date::set_year(const int &year) {
  if (is_valid_date(this->day, this->month, year) == false) {
    throw std::invalid_argument("Invalid year" + std::to_string(year));
  }

  this->year = year;
}

//Getters
int Date::get_day() const { return day; }
int Date::get_month() const { return month; }
int Date::get_year() const { return year; }

//Overloaded operators
bool Date::operator==(const Date &date) const {
  return day == date.day && month == date.month && year == date.year;
}
bool Date::operator!=(const Date &date) const { return !(*this == date); }
bool Date::operator<(const Date &date) const {
  if (year < date.year) {
    return true;
  } else if (year == date.year) {
    if (month < date.month) {
      return true;
    } else if (month == date.month) {
      if (day < date.day) {
        return true;
      }
    }
  }

  return false;
}
bool Date::operator>(const Date &date) const {
  return !(*this < date) && !(*this == date);
}
bool Date::operator<=(const Date &date) const {
  return *this < date || *this == date;
}
bool Date::operator>=(const Date &date) const {
  return *this > date || *this == date;
}
Date Date::operator+(const int &days) const {
  Date new_date = *this;
  static const int days_in_month[] = {31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31};

  for (int i = 0; i < days; i++) {
    new_date.day++;
    int month_index =
        new_date.month - 1; // array is 0-based, months are 1-based
    int days_this_month = days_in_month[month_index];

    // Check for leap year
    if (new_date.month == 2 && is_leap_year(new_date.year)) {
      days_this_month = 29;
    }

    if (new_date.day > days_this_month) {
      new_date.day = 1;
      new_date.month++;
      if (new_date.month > 12) {
        new_date.month = 1;
        new_date.year++;
      }
    }
  }

  return new_date;
}
Date &Date::operator++() {
  *this = *this + 1;
  return *this;
}

//Static methods
std::string Date::month_name(const int &month) {
  if (month < 1 || month > 12) {
    throw std::invalid_argument("Invalid month" + std::to_string(month));
  }

  std::string months[12] = {"January",   "February", "March",    "April",
                            "May",       "June",     "July",     "August",
                            "September", "October",  "November", "December"};

  return months[month - 1];
}

bool Date::is_valid_date(const int &day, const int &month, const int &year) {
  if (month < 1 || month > 12) {
    return false;
  }

  int max_days = 31;
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    max_days = 30;
  } else if (month == 2) {
    max_days = 28;
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
      max_days = 29;
    }
  }

  if (day < 1 || day > max_days) {
    return false;
  }

  if (year <= 0) {
    return false;
  }

  return true;
}

bool Date::is_leap_year(const int &year) {
  if (year % 4 != 0) {
    return false;
  } else if (year % 100 != 0) {
    return true;
  } else if (year % 400 != 0) {
    return false;
  } else {
    return true;
  }
}

//Others
std::string Date::str() const {
  std::ostringstream date_stream;
  // stringstream used to add leading zeros to day and month, for e.g 1 -> 01
  date_stream << std::setw(2) << std::setfill('0') << day << "/" << std::setw(2)
              << std::setfill('0') << month << "/" << year;
  return date_stream.str();
}