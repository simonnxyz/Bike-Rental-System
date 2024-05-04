#include "Bicycle.h"
#include <gtest/gtest.h>

TEST(BicycleTest, Constructor) {
	Bicycle bicycle("Cross", 23.0, "1234", true);

	EXPECT_EQ(bicycle.get_name(), "Cross");
	EXPECT_EQ(bicycle.get_price(), 23.0);
	EXPECT_EQ(bicycle.get_station(), "1234");
	EXPECT_TRUE(bicycle.get_availability());
}

TEST(BicycleTest, LoadAndStr) {
	Bicycle bicycle;
	std::string data = "1234,Cross,54.00,1234,0";
	bicycle.load(data);

	EXPECT_EQ(bicycle.get_name(), "Cross");
	EXPECT_EQ(bicycle.get_price(), 54.0);
	EXPECT_EQ(bicycle.get_station(), "1234");
	EXPECT_FALSE(bicycle.get_availability());
	EXPECT_EQ(bicycle.str(), "1234,Cross,54.00,1234,0");
}

TEST(BicycleTest, GetAttributes) {
	Bicycle bicycle("Cross", 53.0, "1234", true);
	std::vector<std::string> expected = {"id", "name", "price", "station_id", "is_available"};
	
	EXPECT_EQ(bicycle.get_attributes(), expected);
}

TEST(BicycleTest, CheckQuery) {
	Bicycle bicycle("Canyon", 27.00, "123", true);
	std::map<std::string, std::string> query = {{"name", "Canyon"}, {"price", "27.00"}};
	
	EXPECT_TRUE(bicycle.check_query(query));
}

TEST(BicycleTest, SetName) {
	Bicycle bicycle("Cross", 21.0, "1234", true);
	bicycle.set_name("Canyon");

	EXPECT_EQ(bicycle.get_name(), "Canyon");
}

TEST(BicycleTest, SetPrice) {
	Bicycle bicycle("Cross", 21.0, "1234", true);
	bicycle.set_price(22.0);

	EXPECT_EQ(bicycle.get_price(), 22.0);
}

TEST(BicycleTest, SetStation) {
	Bicycle bicycle("Cross", 21.0, "1234", true);
	bicycle.set_station("5678");

	EXPECT_EQ(bicycle.get_station(), "5678");
}

TEST(BicycleTest, SetAvailability) {
	Bicycle bicycle("Cross", 21.0, "1234", true);
	bicycle.set_availability(false);

	EXPECT_FALSE(bicycle.get_availability());
}

TEST(BicycleTest, EqualityOperator) {
	Bicycle bicycle1("Cross", 21.0, "1234", true);
	Bicycle bicycle2("Cross", 21.0, "1234", true);
	std::string data = "1234,Cross,21.00,1234,1";
	bicycle1.load(data);
	bicycle2.load(data);

	EXPECT_TRUE(bicycle1 == bicycle2);
}

TEST(BicycleTest, InequalityOperator) {
	Bicycle bicycle1("Cross", 21.0, "1234", true);
	Bicycle bicycle2("Cross", 21.0, "1234", true);

	EXPECT_TRUE(bicycle1 != bicycle2); // different id
}
TEST(BicycleTest, OutputOperator) {
	Bicycle bicycle("Cross", 21.0, "1234", true);
	std::string data = "1234,Cross,21.00,1234,1";
	bicycle.load(data);
	std::ostringstream oss;
	oss << bicycle;
	std::string expected = "{ Id: 1234\nName: Cross\nPrice: 21.00\nStation: 1234\nIs available: true }\n";
	EXPECT_EQ(oss.str(), expected);
}