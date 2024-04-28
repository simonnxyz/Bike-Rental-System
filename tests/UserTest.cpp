#include "User.h"
#include <gtest/gtest.h>

// SHA256 hash of word 'password'
#define PASSWORD_HASH                                                          \
  "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"

TEST(UserTest, Constructor) {
  User user("John Doe", "john@example.com", "password");
  const std::string id = user.get_id();
  EXPECT_EQ(user.get_name(), "John Doe");
  EXPECT_EQ(user.get_email(), "john@example.com");
  EXPECT_TRUE(user.compare_password("password"));
  // test if the password was hashed correctly
  EXPECT_EQ(user.str(), id + ",John Doe,john@example.com," PASSWORD_HASH);
}

TEST(UserTest, SettersAndGetters) {
  User user("John Doe", "john@example.com", "password");
  user.set_name("Jane Doe");
  user.set_email("jane@example.com");
  EXPECT_EQ(user.get_name(), "Jane Doe");
  EXPECT_EQ(user.get_email(), "jane@example.com");
}

TEST(UserTest, LoadAndStr) {
  User user;
  user.load("1,John Doe,john@example.com,password123\n");
  EXPECT_EQ(user.str(), "1,John Doe,john@example.com,password123\n");
  EXPECT_EQ(user.get_email(), "john@example.com");
  EXPECT_EQ(user.get_id(), "1");
  EXPECT_EQ(user.get_name(), "John Doe");
}

TEST(UserTest, CheckQuery) {
  User user("John Doe", "john@example.com", "password123");
  std::map<std::string, std::string> query = {{"name", "John Doe"},
                                              {"email", "john@example.com"}};
  EXPECT_TRUE(user.check_query(query));
  query["email"] = "jane@example.com";
  EXPECT_FALSE(user.check_query(query));
}

TEST(UserTest, ComparePassword) {
  User user("John Doe", "john@example.com", "password123");
  EXPECT_TRUE(user.compare_password("password123"));
  EXPECT_FALSE(user.compare_password("password321"));
}

TEST(UserTest, EqualityOperator) {
  User user1("John Doe", "john@example.com", "password123");
  User user2("John Doe", "john@example.com", "password123");
  EXPECT_FALSE(user1 == user2);
  // only equal when id is equal
  const std::string id = user1.get_id();
  User user3;
  user3.load(id + ",name,email@example.com,password");
  EXPECT_TRUE(user1 == user3);
}

TEST(UserTest, LoadWithInvalidInputs) {
  User user;
  // too few arguments
  EXPECT_THROW(user.load("John Doe,john@example.com"), std::invalid_argument);
  EXPECT_THROW(user.load("1,John Doe,john@example.com"), std::invalid_argument);
  EXPECT_THROW(user.load("1,John Doe"), std::invalid_argument);
}

TEST(UserTest, SetEmailWithInvalidEmails) {
  User user;
  EXPECT_THROW(user.set_email("johnexample.com"), std::invalid_argument);
  EXPECT_THROW(user.set_email("john"), std::invalid_argument);
}