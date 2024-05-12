#include "../include/Database.h"
#include "../include/User.h"
#include "../src/Database.cpp"
#include <gtest/gtest.h>
#include <sstream>

// SHA256 hash of word 'password'
#define PASSWORD_HASH                                                          \
  "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"

void reset_file() {
  // open a file in ./build for tests
  std::ofstream file("test_db.txt", std::ios::trunc);
  file.close();
}

void populate_db(Database<User> &db, int num_users) {
  // util for populating db with num_users unique users
  for (int i = 0; i < num_users; ++i) {
    std::string user_name = "User" + std::to_string(i);
    std::string user_email = "user" + std::to_string(i) + "@example.com";
    std::unique_ptr<User> user =
        std::make_unique<User>(user_name, user_email, "password");
    db.add(std::move(user));
  }
}

void populate_db_with_stream(Database<User> &db, int num_users) {
  std::stringstream ss;
  for (int i = 0; i < num_users; ++i) {
    // id,User{num},user{num}@example.com,password_hash
    ss << i << ",User" << i << ","
       << "user" << i << "@example.com,"
       << "password," << i << '\n';
  }
  db.load(ss);
}

TEST(DatabaseUserTest, AddUser) {
  reset_file();
  Database<User> db("test_db.txt");
  std::unique_ptr<User> user =
      std::make_unique<User>("test_user", "test_user@example.com", "password");

  User *user_ptr = db.add(std::move(user));
  const std::string id = user_ptr->get_id();

  ASSERT_EQ(db.size(), 1);

  User *user_ptr2 = db[0];
  ASSERT_EQ(user_ptr2->get_id(), id);
  ASSERT_EQ(user_ptr2->get_name(), "test_user");
  ASSERT_EQ(user_ptr2->get_email(), "test_user@example.com");
}

TEST(DatabaseUserTest, LoadUser) {
  reset_file();
  Database<User> db("test_db.txt");
  std::stringstream ss;
  ss << "1,test_user,test_user@example.com," << PASSWORD_HASH << ",10.99";
  // SHA256 hash of "password"

  db.load(ss);

  std::cout << "Users: \n";
  for (const std::unique_ptr<User> &user_ptr : db) {
    std::cout << *user_ptr.get();
  };

  ASSERT_EQ(db.size(), 1);
  User *user = db.find_by_id("1");
  ASSERT_EQ(user->get_name(), "test_user");
  ASSERT_EQ(user->get_email(), "test_user@example.com");
  ASSERT_EQ(user->get_id(), "1");
}

TEST(DatabaseUserTest, SaveUser) {
  reset_file();
  Database<User> db("test_db.txt");
  std::unique_ptr<User> user =
      std::make_unique<User>("test_user", "test_user@example.com", "password");
  const std::string id = user.get()->get_id();
  db.add(std::move(user));

  std::stringstream ss;
  db.save(ss);

  std::string expected =
      id + ",test_user,test_user@example.com," PASSWORD_HASH + ",0.00\n";
  ASSERT_EQ(ss.str(), expected);
}

TEST(DatabaseUserTest, QueryFound) {
  reset_file();
  Database<User> db("test_db.txt");
  std::unique_ptr<User> user =
      std::make_unique<User>("John Doe", "john@example.com", "password");
  db.add(std::move(user));

  std::map<std::string, std::string> query = {{"name", "John Doe"},
                                              {"email", "john@example.com"}};
  User *foundUser = db.find(query);
  ASSERT_TRUE(foundUser != nullptr);
  EXPECT_EQ(foundUser->get_name(), "John Doe");
}

TEST(DatabaseUserTest, QueryNotFound) {
  reset_file();
  Database<User> db("test_db.txt");
  std::unique_ptr<User> user =
      std::make_unique<User>("John Doe", "john@example.com", "password");
  db.add(std::move(user));

  std::map<std::string, std::string> query = {{"name", "John Kowalski"}};
  User *foundUser = db.find(query);
  ASSERT_TRUE(foundUser == nullptr);
}

TEST(DatabaseUserTest, Extract) {
  reset_file();
  Database<User> db("test_db.txt");
  std::unique_ptr<User> user =
      std::make_unique<User>("John Doe", "john@example.com", "password");
  db.add(std::move(user));

  std::map<std::string, std::string> query = {{"name", "John Doe"}};
  User *extractedUser = db.extract(query);
  ASSERT_TRUE(extractedUser != nullptr);
  EXPECT_EQ(extractedUser->get_name(), "John Doe");

  // the user should no longer be in the database
  User *notFoundUser = db.find(query);
  ASSERT_TRUE(notFoundUser == nullptr);
}

TEST(DatabaseUserTest, Remove) {
  reset_file();
  Database<User> db("test_db.txt");
  std::unique_ptr<User> user =
      std::make_unique<User>("John Doe", "john@example.com", "password");
  db.add(std::move(user));

  bool removed = db.remove({{"name", "John Doe"}});
  ASSERT_TRUE(removed);

  User *notFoundUser = db.find({{"name", "John Doe"}});
  ASSERT_TRUE(notFoundUser == nullptr);
}

TEST(DatabaseUserTest, AddMultipleUsers) {
  reset_file();
  Database<User> db("test_db.txt");
  populate_db(db, 10);

  ASSERT_EQ(db.size(), 10);

  for (int i = 0; i < 10; ++i) {
    User *user_ptr = db[i];
    ASSERT_EQ(user_ptr->get_name(), "User" + std::to_string(i));
    ASSERT_EQ(user_ptr->get_email(),
              "user" + std::to_string(i) + "@example.com");
  }
}

TEST(DatabaseUserTest, FindMultipleUsers) {
  reset_file();
  Database<User> db("test_db.txt");
  populate_db(db, 10);

  for (int i = 0; i < 10; ++i) {
    std::map<std::string, std::string> query = {
        {"name", "User" + std::to_string(i)}};
    User *foundUser = db.find(query);
    ASSERT_TRUE(foundUser != nullptr);
    EXPECT_EQ(foundUser->get_name(), "User" + std::to_string(i));
  }
}

TEST(DatabaseUserTest, RemoveMultipleUsers) {
  reset_file();
  Database<User> db("test_db.txt");
  populate_db(db, 10);

  for (int i = 0; i < 10; ++i) {
    bool removed = db.remove({{"name", "User" + std::to_string(i)}});
    ASSERT_TRUE(removed);

    User *notFoundUser = db.find({{"name", "User" + std::to_string(i)}});
    ASSERT_TRUE(notFoundUser == nullptr);
  }

  ASSERT_EQ(db.size(), 0);
}

TEST(DatabaseUserTest, ExtractMultipleUsers) {
  reset_file();
  Database<User> db("test_db.txt");
  populate_db(db, 10);

  for (int i = 0; i < 10; ++i) {
    std::map<std::string, std::string> query = {
        {"name", "User" + std::to_string(i)}};
    User *extractedUser = db.extract(query);
    ASSERT_TRUE(extractedUser != nullptr);
    EXPECT_EQ(extractedUser->get_name(), "User" + std::to_string(i));

    User *notFoundUser = db.find(query);
    ASSERT_TRUE(notFoundUser == nullptr);
  }

  ASSERT_EQ(db.size(), 0);
}

TEST(DatabaseUserTest, AddMultipleUsersWithStream) {
  reset_file();
  Database<User> db("test_db.txt");
  populate_db_with_stream(db, 10);

  int i = 0;
  for (auto &user_ptr : db) {
    ASSERT_EQ(user_ptr->get_name(), "User" + std::to_string(i));
    ASSERT_EQ(user_ptr->get_email(),
              "user" + std::to_string(i) + "@example.com");
    i++;
  }

  ASSERT_EQ(db.size(), 10);
}

TEST(DatabaseUserTest, AddRemoveSaveAndCheckStream) {
  reset_file();
  Database<User> db("test_db.txt");

  populate_db_with_stream(db, 3);

  // Remove middle user
  std::map<std::string, std::string> query = {{"name", "User1"}};
  bool removed = db.remove(query);
  ASSERT_TRUE(removed);

  // Save to stringstream
  std::stringstream ss;
  db.save(ss);

  // Check if stringstream is equal to the 2 users left
  std::string expected_output = "0,User0,user0@example.com,password,0.00\n"
                                "2,User2,user2@example.com,password,2.00\n";
  ASSERT_EQ(ss.str(), expected_output);
}