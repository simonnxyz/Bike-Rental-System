/*
* Name: DateTest.cpp
* Purpose: Date tests
* @author wzieziul
*/

#include "Date.h"
#include <gtest/gtest.h>

TEST(DateTest, Constructor) {
	Date date(12, 11, 2018);
  EXPECT_EQ(date.get_day(), 12);
  EXPECT_EQ(date.get_month(), 11);
  EXPECT_EQ(date.get_year(), 2018);
}

TEST(DateTest, ConstructorStr) {
  Date date("12.11.2018");
  EXPECT_EQ(date.get_day(), 12);
  EXPECT_EQ(date.get_month(), 11);
  EXPECT_EQ(date.get_year(), 2018);
}

TEST(DateTest, ConstructorInvalid) {
  EXPECT_THROW(Date(50, 9, 2020), std::invalid_argument);
  EXPECT_THROW(Date(12, 18, 2023), std::invalid_argument);
  EXPECT_THROW(Date(0, 1, 2023), std::invalid_argument);
  EXPECT_THROW(Date(12, -5, 2023), std::invalid_argument);
  EXPECT_THROW(Date(12, 1, -12), std::invalid_argument);
  EXPECT_THROW(Date(29, 2, 2023), std::invalid_argument);
}

TEST(DateTest, SetDay) {
  Date date("12.11.2018");
  date.set_day(15);
  EXPECT_EQ(date.get_day(), 15);
  EXPECT_THROW(date.set_day(31), std::invalid_argument);
}

TEST(DateTest, SetMonth) {
  Date date("31.12.2018");
  EXPECT_THROW(date.set_month(2), std::invalid_argument);
  date.set_month(1);
  EXPECT_EQ(date.get_month(), 1);
  EXPECT_THROW(date.set_month(13), std::invalid_argument);
}

TEST(DateTest, SetYear) {
  Date date("18.02.2024");
  date.set_year(2025);
  EXPECT_EQ(date.get_year(), 2025);
  EXPECT_THROW(date.set_year(0), std::invalid_argument);
}

TEST(DateTest, Str) {
  Date date(1, 5, 2021);
  EXPECT_EQ(date.str(), "01/05/2021");
}

TEST(DateTest, MonthName) {
  EXPECT_EQ(Date::month_name(12), "December");
  EXPECT_THROW(Date::month_name(0), std::invalid_argument);
  EXPECT_THROW(Date::month_name(13), std::invalid_argument);
}

TEST(DateTest, EqualityOperator) {
  Date date1(12, 12, 1212);
  Date date2(12, 12, 1212);
  EXPECT_TRUE(date1 == date2);
}

TEST(DateTest, InequalityOperator) {
  Date date1(11, 11, 2011);
  Date date2(12, 11, 2011);
  EXPECT_TRUE(date1 != date2);
}

TEST(DateTest, LessOperator) {
  Date date1(11, 11, 2011);
  Date date2(12, 11, 2011);
  EXPECT_TRUE(date1 < date2);
}

TEST(DateTest, GreaterOperator) {
  Date date1(11, 11, 2011);
  Date date2(12, 11, 2011);
  EXPECT_TRUE(date2 > date1);
}

TEST(DateTest, LessEqualOperator) {
  Date date1(11, 11, 2011);
  Date date2(12, 11, 2011);
  Date date3(12, 11, 2011);
  EXPECT_TRUE(date1 <= date2);
  EXPECT_TRUE(date2 <= date3);
}

TEST(DateTest, GreaterEqualOperator) {
  Date date1(11, 11, 2011);
  Date date2(12, 11, 2011);
  Date date3(12, 11, 2011);
  EXPECT_TRUE(date2 >= date1);
  EXPECT_TRUE(date3 >= date2);
}

TEST(DateTest, PlusOperator) {
  Date date(22, 2, 2024);
  Date date2 = date + 8;
  EXPECT_TRUE(date2 == Date(1, 3, 2024));
  Date date3(22, 2, 2023);
  Date date4 = date3 + 8;
  EXPECT_TRUE(date4 == Date(2, 3, 2023));
}

TEST(DateTest, IncrementationOperator) {
  Date date(31, 12, 2024);
  ++date;
  EXPECT_TRUE(date == Date(1, 1, 2025));
}

TEST(DateTest, IsLeapYear) {
  EXPECT_TRUE(Date::is_leap_year(2024));
  EXPECT_TRUE(Date::is_leap_year(2000));
  EXPECT_FALSE(Date::is_leap_year(1900));
  EXPECT_FALSE(Date::is_leap_year(2023));
}