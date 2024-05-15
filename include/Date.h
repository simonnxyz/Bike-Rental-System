#include <iostream>
#include <string>

#pragma once

class Date {
public:
  Date(int day, int month, int year);
  Date(std::string date);
  Date();

  static bool is_valid_date(int day, int month, int year);

  int get_day();
  int get_month();
  int get_year();
  static std::string month_name(int month);

  void set_day(int day);
  void set_month(int month);
  void set_year(int year);

  std::string str();
  bool is_leap_year(int year) const;

  bool operator==(const Date &date) const;
  bool operator!=(const Date &date) const;
  bool operator<(const Date &date) const;
  bool operator>(const Date &date) const;
  bool operator<=(const Date &date) const;
  bool operator>=(const Date &date) const;

  Date operator+(int days) const;
  Date &operator++();

private:
  int day;
  int month;
  int year;
};