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
  std::ofstream("../database/rentals.txt", std::ios::trunc);
  std::ofstream date_file("../database/date.txt", std::ios::trunc);

  Date date;
  std::cout << date.str() << std::endl;
  date_file.write(date.str().c_str(), 10);
  date_file.close();

  Database<User> users("../database/users.txt");
  Database<User> admins("../database/admins.txt");
  Database<Bicycle> bikes("../database/bikes.txt");
  Database<RentalStation> stations("../database/stations.txt");

  // User(const std::string &user_name, const std::string &user_email,
  //      const std::string &password, const double &balance);
  std::unique_ptr<User> user1 =
      std::make_unique<User>("Michal", "michal@gmail.com", "password", 100.0);
  std::unique_ptr<User> user2 =
      std::make_unique<User>("Kacper", "kacper@gmail.com", "password", 150.0);
  std::unique_ptr<User> user3 =
      std::make_unique<User>("Wojtek", "wojtek@gmail.com", "password", 200.0);
  std::unique_ptr<User> user4 =
      std::make_unique<User>("Mp", "michalp@gmail.com", "password", 250.0);
  // admins
  std::unique_ptr<User> admin1 =
      std::make_unique<User>("Michal", "michal@admin.com", "password", 100.0);
  std::unique_ptr<User> admin2 =
      std::make_unique<User>("Kacper", "kacper@admin.com", "password", 150.0);
  std::unique_ptr<User> admin3 =
      std::make_unique<User>("Wojtek", "wojtek@admin.com", "password", 200.0);
  std::unique_ptr<User> admin4 =
      std::make_unique<User>("Mp", "michalp@admin.com", "password", 250.0);

  // RentalStation(const std::string &name, const double &x, const double &y,
  //               const int &capacity, const int &empty_spaces);
  std::unique_ptr<RentalStation> centrum =
      std::make_unique<RentalStation>("Centrum", 430, 375, 100, 98);
  std::unique_ptr<RentalStation> mokotow =
      std::make_unique<RentalStation>("Mokotow", 410, 500, 100, 98);
  std::unique_ptr<RentalStation> praga =
      std::make_unique<RentalStation>("Praga", 550, 325, 100, 98);
  std::unique_ptr<RentalStation> wola =
      std::make_unique<RentalStation>("Wola", 260, 350, 100, 99);
  std::unique_ptr<RentalStation> ursynow =
      std::make_unique<RentalStation>("Ursynow", 415, 725, 100, 99);
  std::unique_ptr<RentalStation> bemowo =
      std::make_unique<RentalStation>("Bemowo", 180, 325, 100, 99);

  // Bicycle(const std::string &name, const double &price,
  //         const std::string &station_id, const bool &is_available);
  std::unique_ptr<Bicycle> bike1 =
      std::make_unique<Bicycle>("shimano turbo", 15, centrum->get_id(), true);
  std::unique_ptr<Bicycle> bike2 =
      std::make_unique<Bicycle>("speedster", 15, mokotow->get_id(), true);
  std::unique_ptr<Bicycle> bike3 = std::make_unique<Bicycle>(
      "miejski pogromca v2", 10, praga->get_id(), true);
  std::unique_ptr<Bicycle> bike4 =
      std::make_unique<Bicycle>("uliczny popylacz", 10, wola->get_id(), true);
  std::unique_ptr<Bicycle> bike5 = std::make_unique<Bicycle>(
      "terenowy wariacik", 10, ursynow->get_id(), true);
  std::unique_ptr<Bicycle> bike6 = std::make_unique<Bicycle>(
      "szosowy mastermind", 10, bemowo->get_id(), true);
  std::unique_ptr<Bicycle> bike7 = std::make_unique<Bicycle>(
      "cannondale ultra light", 10, praga->get_id(), true);
  std::unique_ptr<Bicycle> bike8 =
      std::make_unique<Bicycle>("duch armstronga", 10, centrum->get_id(), true);
  std::unique_ptr<Bicycle> bike9 =
      std::make_unique<Bicycle>("iamspeed", 10, mokotow->get_id(), true);

  // Add the data
  users.add(std::move(user1));
  users.add(std::move(user2));
  users.add(std::move(user3));
  users.add(std::move(user4));

  admins.add(std::move(admin1));
  admins.add(std::move(admin2));
  admins.add(std::move(admin3));
  admins.add(std::move(admin4));

  stations.add(std::move(centrum));
  stations.add(std::move(mokotow));
  stations.add(std::move(praga));
  stations.add(std::move(wola));
  stations.add(std::move(ursynow));
  stations.add(std::move(bemowo));

  bikes.add(std::move(bike1));
  bikes.add(std::move(bike2));
  bikes.add(std::move(bike3));
  bikes.add(std::move(bike4));
  bikes.add(std::move(bike5));
  bikes.add(std::move(bike6));
  bikes.add(std::move(bike7));
  bikes.add(std::move(bike8));
  bikes.add(std::move(bike9));
}