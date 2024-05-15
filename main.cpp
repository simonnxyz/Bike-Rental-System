// #include "./include/AdminInterface.h"
#include "./include/AdminInterface.h"
#include "./include/Bicycle.h"
#include "./include/Database.h"
#include "./include/Rent.h"
#include "./include/RentalStation.h"
#include "./include/User.h"
#include "./include/UserInterface.h"
#include <iomanip>


int main() {
  Database<User> users("../database/users.txt");
  Database<User> admins("../database/admins.txt");
  Database<Bicycle> bikes("../database/bikes.txt");
  Database<RentalStation> stations("../database/stations.txt");
  Database<Rent> rentals("../database/rentals.txt");

  try {
    // login
    BaseInterface *interface = new UserInterface();
    interface->set_users_data(users);
    interface->set_admins_data(admins);

    bool is_admin = interface->login();

    if (is_admin) {
      User *admin = interface->get_user();

      // change this to AdminInterface when its ready
      interface = new AdminInterface();
      interface->set_user(admin);
    }

    // when the interface sets its user_data it is moved into it because users
    // is a vector of unique_ptr because of that we need to reload the data from
    // the file in case the user registered which changed our database
    users.load();
    interface->set_users_data(users);
    interface->set_bikes_data(bikes);
    interface->set_station_data(stations);
    interface->set_rentals_data(rentals);

    // run the main loop on the interface
    interface->run();

    delete interface;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}