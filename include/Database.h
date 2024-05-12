#include <Model.h>
#include <fstream>
#include <iterator>
#include <memory>

#pragma once

/**
 * @class Database
 * @brief A class to represent a database of objects that inherit from model.
 * @param filepath - Path to file
 *
 * Data is saved to a file once the Database goes out of scope, there is no
 * need for manual saving.
 *
 * One database should be created for each Model from a file at the start of the
 * program, then all operations like find etc. can be performed on it.
 */
template <class T> class Database {
public:
  static_assert(std::is_base_of<Model, T>::value,
                "Database class only works on subclass of Model");

  // constructors
  Database() : filename(""){};
  Database(const std::string &file_name) : filename(file_name) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      throw std::invalid_argument("File not found: " + filename);
    }
    load(file);
    file.close();
  };

  // destructor which also saves to file
  ~Database() {
    if (members.empty())
      return;
    std::ofstream file(filename);
    save(file);
    file.close();
  };

  // other
  T *find_by_id(const std::string &id) {
    for (auto &member : members) {
      if (member->get_id() == id) {
        return member.get();
      }
    }
    return nullptr;
  };

  /**
   * @brief Finds a Model in the database.
   * @param query map<string,string> where first string is attribute being
   * searched and the second one is the value that is searched for
   * @return A pointer to the Model if found, nullptr otherwise.
   */
  T *find(const std::map<std::string, std::string> &query) {
    for (auto &member : members) {
      if (member->check_query(query)) {
        return member.get();
      }
    }

    return nullptr;
  };

  /**
   * @brief Adds a Model to the database.
   * @param user The unique_ptr to object to add.
   * @def: db.add(std::move(the_unique_ptr_to_add));
   */
  T *add(std::unique_ptr<T> obj) {
    members.push_back(std::move(obj));
    return members.back().get();
  };

  /**
   * @brief Removes the Model from the Database and returns a pointer to it.
   * @param query Same as in find.
   */
  T *extract(const std::map<std::string, std::string> &query) {
    for (auto it = members.begin(); it != members.end(); ++it) {
      if (it->get()->check_query(query)) {
        T *result = it->get();
        members.erase(it);
        return result;
      }
    }

    return nullptr;
  };
  // remove from database and return bool if removed
  bool remove(const std::map<std::string, std::string> &query) {
    for (auto it = members.begin(); it != members.end(); ++it) {
      if (it->get()->check_query(query)) {
        members.erase(it);
        return true;
      }
    }

    return false;
  };

  int size() const { return members.size(); };

  void load() {
    std::ifstream file(filename);
    if (!file.is_open()) {
      throw std::invalid_argument("File not found: " + filename);
    }
    load(file);
  }
  // load from a file stream
  void load(std::istream &file) {
    std::string line;
    while (std::getline(file, line)) {
      try {
        std::unique_ptr<T> obj = std::make_unique<T>();
        obj->load(line);
        members.push_back(std::move(obj));
      } catch (std::invalid_argument e) {
        std::cout << "Error when loading a database: " << e.what() << "\n";
      }
    }
  };

  // save to a file stream
  void save(std::ostream &file) {
    for (auto &member : members) {
      file << member->str() << "\n";
    }
  };

  // iterators
  typename std::vector<std::unique_ptr<T>>::const_iterator begin() const {
    return members.begin();
  };
  typename std::vector<std::unique_ptr<T>>::const_iterator end() const {
    return members.end();
  };

  typename std::vector<std::unique_ptr<T>>::iterator begin() {
    return members.begin();
  };
  typename std::vector<std::unique_ptr<T>>::iterator end() {
    return members.end();
  };

  T *operator[](int ind) { return members.at(ind).get(); };

  // move operator: db = std::move(db2);
  // used in BaseInterface
  Database<T> &operator=(Database<T> &&other) noexcept {
    members = std::move(other.members);
    filename = other.filename;
    other.members.clear();
    return *this;
  };

private:
  std::vector<std::unique_ptr<T>> members;
  std::string filename;
};