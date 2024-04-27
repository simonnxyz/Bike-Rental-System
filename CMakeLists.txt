cmake_minimum_required(VERSION 3.12)
project(Rowerownia)

include_directories(include) # header files there

add_library(user include/User.h src/User.cpp)
add_library(sha256 include/SHA256.h src/SHA256.cpp)
add_library(model include/Model.h src/Model.cpp)
add_library(uuid src/Uuid.cpp)

target_link_libraries(model PRIVATE uuid)

target_link_libraries(user PRIVATE sha256)
target_link_libraries(user PRIVATE model)

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

target_link_libraries(main PRIVATE user sha256)

enable_testing()

add_executable(
  google_testing
  tests/UtilsTest.cpp
)
target_link_libraries(
  google_testing
  GTest::gtest_main
  user
  sha256
  model
  uuid
)

include(GoogleTest)
gtest_discover_tests(google_testing)