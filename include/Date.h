#include <iostream>
#include <string>

#pragma once

class Date {
public:
  //Constructors
  Date(const int &day, const int &month, const int &year);
  Date(const std::string &date);
  Date();

  //Setters
  void set_day(const int &day);
  void set_month(const int &month);
  void set_year(const int &year);

  //Getters
  int get_day() const;
  int get_month() const;
  int get_year() const;

  //Overloaded operators
  bool operator==(const Date &date) const;
  bool operator!=(const Date &date) const;
  bool operator<(const Date &date) const;
  bool operator>(const Date &date) const;
  bool operator<=(const Date &date) const;
  bool operator>=(const Date &date) const;

  Date operator+(const int &days) const;
  Date &operator++();

  //Static methods
  static std::string month_name(const int &month);
  static bool is_valid_date(const int &day, const int &month, const int &year);
  static bool is_leap_year(const int &year);

  //Others
  std::string str() const;

private:
  int day;
  int month;
  int year;
};