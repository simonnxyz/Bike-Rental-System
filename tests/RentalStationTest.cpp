/*
* Name: RentalStation.cpp
* Purpose: RentalStation tests
* @author ksiemion
*/

#include "RentalStation.h"
#include <gtest/gtest.h>
#include <string>

TEST(RentalStationTest, Constructor) {
  RentalStation station("ul. Marszałkowska 1", 14.123133, 65.523411, 30, 12);

  EXPECT_EQ(station.get_name(), "ul. Marszałkowska 1");
  EXPECT_DOUBLE_EQ(station.get_x(), 14.123133);
  EXPECT_DOUBLE_EQ(station.get_y(), 65.523411);
  EXPECT_EQ(station.get_capacity(), 30);
  EXPECT_EQ(station.get_empty_spaces(), 12);
}

TEST(RentalStationTest, SetName) {
  RentalStation station("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  station.set_name("ul. Nowy Świat 2");
  
  EXPECT_EQ(station.get_name(), "ul. Nowy Świat 2");
}

TEST(RentalStationTest, SetX) {
  RentalStation station("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  station.set_x(52.2350);

  EXPECT_DOUBLE_EQ(station.get_x(), 52.2350);
}

TEST(RentalStationTest, SetY) {
  RentalStation station("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  station.set_y(21.0106);

  EXPECT_DOUBLE_EQ(station.get_y(), 21.0106);
}

TEST(RentalStationTest, SetCapacity) {
  RentalStation station("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  station.set_capacity(15);

  EXPECT_EQ(station.get_capacity(), 15);
}

TEST(RentalStationTest, SetEmptySpaces) {
  RentalStation station("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  station.set_empty_spaces(5);

  EXPECT_EQ(station.get_empty_spaces(), 5);
}

TEST(RentalStationTest, EqualityOperator) {
  RentalStation station1("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  RentalStation station2("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  std::string data = "1234,ul. Marszałkowska 1,52.2297,21.0122,10,5";
  station1.load(data);
  station2.load(data);

  EXPECT_TRUE(station1 == station2);
}

TEST(RentalStationTest, OutputOperator) {
  RentalStation station("ul. Marszałkowska 1", 52.2297, 21.0122, 10, 5);
  std::string data = "1234,ul. Marszałkowska 1,52.2297,21.0122,10,5";
  station.load(data);

  std::ostringstream oss;
  oss << station;
  std::string expected = "{ Id: 1234\nName: ul. Marszałkowska 1\nX: 52.229700\nY: 21.012200\nCapacity: 10\nEmpty spaces: 5 }\n";
  EXPECT_EQ(oss.str(), expected);
}
