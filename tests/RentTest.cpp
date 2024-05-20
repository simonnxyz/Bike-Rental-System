/*
* Name: RentTest.cpp
* Purpose: Rent tests
* @author wzieziul
*/

#include "Rent.h"
#include <gtest/gtest.h>

TEST(RentTest, Constructor) {
	Rent rent("12.05.2024", "123", "456");
	EXPECT_EQ(rent.get_date(), "12.05.2024");
	EXPECT_EQ(rent.get_user(), "123");
	EXPECT_EQ(rent.get_bicycle(), "456");
	EXPECT_TRUE(rent.get_has_ended() == false);
}

TEST(RentTest, LoadAndStr) {
  Rent rent;
	std::string data = "1234,12.05.2024,123,321,true";
	rent.load(data);

  EXPECT_EQ(rent.get_id(), "1234");
	EXPECT_EQ(rent.get_date(), "12.05.2024");
	EXPECT_EQ(rent.get_user(), "123");
	EXPECT_EQ(rent.get_bicycle(), "321");
	EXPECT_TRUE(rent.get_has_ended());
  EXPECT_EQ(rent.str(), "1234,12.05.2024,123,321,true");
}

TEST(RentTest, GetAttributes) {
  Rent rent("12.05.2024", "123", "456");
	std::vector<std::string> expected = {"id", "date", "user_id", "bicycle_id", "has_ended"};

	EXPECT_EQ(rent.get_attributes(), expected);
}

// TEST(RentTest, CheckQuery) {
// 	Rent rent("12.05.2024", "123", "456");
// 	std::map<std::string, std::string> query = {{"date", "12.05.2024"}, {"user_id", "123"}, {"bicycle_id", "456"}};
// 	EXPECT_TRUE(rent.check_query(query));
// }

TEST(RentTest, SetDate) {
  Rent rent("12.05.2024", "123", "456");
  rent.set_date("05.12.2021");
  EXPECT_EQ(rent.get_date(), "05.12.2021");
}

TEST(RentTest, SetUser) {
  Rent rent("12.05.2024", "50", "456");
  rent.set_user("21");
  EXPECT_EQ(rent.get_user(), "21");
}

TEST(RentTest, SetBicycle) {
  Rent rent("12.05.2024", "50", "997");
  rent.set_bicycle("122");
  EXPECT_EQ(rent.get_bicycle(), "122");
}

TEST(RentTest, SetHasEnded) {
  Rent rent("12.05.2024", "50", "997");
  rent.set_has_ended(true);
  EXPECT_TRUE(rent.get_has_ended());
}

TEST(RentTest, EqualityOperator) {
  Rent rent1, rent2;
  std::string data = "1234,12.05.2024,123,321,true";
  rent1.load(data);
  rent2.load(data);
  EXPECT_TRUE(rent1 == rent2);
}

TEST(RentTest, InequalityOperator) {
  Rent rent1("12.05.2024", "50", "997");
  Rent rent2("12.05.2024", "50", "997");
	EXPECT_TRUE(rent1 != rent2);
}

TEST(RentTest, OutputOperator) {
	Rent rent;
	std::string data = "1234,12.05.2024,123,321,true";
	rent.load(data);
	std::ostringstream oss;
	oss << rent;
	std::string expected = "{ Id: 1234\nDate: 12.05.2024\nUser id: 123\nBicycle id: 321\nHas ended: true }\n";
	EXPECT_EQ(oss.str(), expected);
}