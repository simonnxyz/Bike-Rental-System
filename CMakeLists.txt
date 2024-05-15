cmake_minimum_required(VERSION 3.12)
project(Rowerownia)

include_directories(include) # header files there

add_library(sha256 include/SHA256.h src/SHA256.cpp)
add_library(model include/Model.h src/Model.cpp)
add_library(uuid src/Uuid.cpp)
add_library(date include/Date.h src/Date.cpp)
add_library(database include/Database.h)
add_library(user include/User.h src/User.cpp)
add_library(BaseInterface include/BaseInterface.h src/BaseInterface.cpp)
add_library(UserInterface include/UserInterface.h src/UserInterface.cpp)
add_library(AdminInterface include/AdminInterface.h src/AdminInterface.cpp)
add_library(bicycle include/Bicycle.h src/Bicycle.cpp)
add_library(rentalStation include/RentalStation.h src/RentalStation.cpp)
add_library(rent include/Rent.h src/Rent.cpp)

target_link_libraries(model PRIVATE uuid)

target_link_libraries(user PRIVATE model)
target_link_libraries(user PRIVATE sha256)

target_link_libraries(bicycle PRIVATE model)

target_link_libraries(rentalStation PRIVATE model)

target_link_libraries(rent PRIVATE model)

# trzeba dolaczyc do nich klase model
# cos takiego target_link_libraries(bike PRIVATE model)

target_link_libraries(database PRIVATE model)
target_link_libraries(database PRIVATE user)
target_link_libraries(database PRIVATE bicycle)
target_link_libraries(database PRIVATE rentalStation)
target_link_libraries(database PRIVATE rent)

target_link_libraries(BaseInterface PRIVATE user)
target_link_libraries(BaseInterface PRIVATE bicycle)
target_link_libraries(BaseInterface PRIVATE rentalStation)
target_link_libraries(BaseInterface PRIVATE rent)
target_link_libraries(BaseInterface PRIVATE model)
target_link_libraries(BaseInterface PRIVATE database)
target_link_libraries(BaseInterface PRIVATE date)

target_link_libraries(UserInterface PRIVATE BaseInterface)
target_link_libraries(AdminInterface PRIVATE BaseInterface)

add_executable(
  main
  main.cpp
)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_executable(
  setup_data
  setup_data.cpp
)

# jak w mainie uzywacie swoich funkcji to tez trzeba dorzucic
target_link_libraries(main PRIVATE user)
target_link_libraries(main PRIVATE bicycle)
target_link_libraries(main PRIVATE rentalStation)
target_link_libraries(main PRIVATE rent)
target_link_libraries(main PRIVATE database)
target_link_libraries(main PRIVATE BaseInterface)
target_link_libraries(main PRIVATE UserInterface)
target_link_libraries(main PRIVATE AdminInterface)

target_link_libraries(setup_data PRIVATE user)
target_link_libraries(setup_data PRIVATE bicycle)
target_link_libraries(setup_data PRIVATE rentalStation)
target_link_libraries(setup_data PRIVATE database)
target_link_libraries(setup_data PRIVATE date)

enable_testing()

add_executable(
  google_testing
  tests/UtilsTest.cpp
  tests/UserTest.cpp
  tests/DatabaseTest.cpp
  tests/BicycleTest.cpp
  tests/RentalStationTest.cpp
  tests/RentTest.cpp
)
# tutaj dodawajcie pliki tekstowe
target_link_libraries(
  google_testing
  GTest::gtest_main
  user
  sha256
  model
  uuid
  database
  bicycle
  rentalStation
)
# tu musicie dorzucić nazwy klas ktore zrobiliscie

include(GoogleTest)
gtest_discover_tests(google_testing)
