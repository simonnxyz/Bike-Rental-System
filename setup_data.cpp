#include "./include/Bicycle.h"
#include "./include/Database.h"
#include "./include/Date.h"
#include "./include/RentalStation.h"
#include "./include/User.h"
#include "./include/UserInterface.h"
#include <iomanip>

int main() {
  // Clear the files
  std::ofstream("../database/users.txt", std::ios::trunc);
  std::ofstream("../database/admins.txt", std::ios::trunc);
  std::ofstream("../database/bikes.txt", std::ios::trunc);
  std::ofstream("../database/stations.txt", std::ios::trunc);

  Date date;
  ++date;
  std::cout << date.str() << std::endl;

  Database<User> users("../database/users.txt");
  Database<User> admins("../database/admins.txt");
  Database<Bicycle> bikes("../database/bikes.txt");
  Database<RentalStation> stations("../database/stations.txt");

  // User(const std::string &user_name, const std::string &user_email,
  //      const std::string &password, const double &balance);
  std::unique_ptr<User> user1 =
      std::make_unique<User>("Michal", "michal05@gmail.com", "password", 100.0);
  std::unique_ptr<User> user2 =
      std::make_unique<User>("Kacper", "kacper07@gmail.com", "password", 150.0);
  std::unique_ptr<User> user3 =
      std::make_unique<User>("Wojtek", "wojtek89@gmail.com", "password", 200.0);
  std::unique_ptr<User> user4 =
      std::make_unique<User>("Mp", "mp69@gmail.com", "password", 250.0);

  // RentalStation(const std::string &name, const double &x, const double &y,
  //               const int &capacity, const int &empty_spaces);
  std::unique_ptr<RentalStation> station1 =
      std::make_unique<RentalStation>("Centrum", 52.2297, 21.0122, 100, 99);
  std::unique_ptr<RentalStation> station2 =
      std::make_unique<RentalStation>("Mokotow", 52.1934, 21.0458, 100, 99);
  std::unique_ptr<RentalStation> station3 =
      std::make_unique<RentalStation>("Praga", 52.2552, 21.0570, 100, 99);

  // Bicycle(const std::string &name, const double &price,
  //         const std::string &station_id, const bool &is_available);
  std::unique_ptr<Bicycle> bike1 =
      std::make_unique<Bicycle>("shimano turbo", 15, station1->get_id(), true);
  std::unique_ptr<Bicycle> bike2 =
      std::make_unique<Bicycle>("popierdalacz", 15, station2->get_id(), true);
  std::unique_ptr<Bicycle> bike3 = std::make_unique<Bicycle>(
      "miejski pogromca v2", 10, station3->get_id(), true);

  // Add the data
  admins.add(std::move(user1));
  admins.add(std::move(user2));
  users.add(std::move(user3));
  users.add(std::move(user4));

  stations.add(std::move(station1));
  stations.add(std::move(station2));
  stations.add(std::move(station3));

  bikes.add(std::move(bike1));
  bikes.add(std::move(bike2));
  bikes.add(std::move(bike3));
}