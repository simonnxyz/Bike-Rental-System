#include <Model.h>
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
  Database(const std::string &filename = "");
  ~Database();

  // other
  T *find_by_id(const std::string &id);
  /**
   * @brief Finds a Model in the database.
   * @param query map<string,string> where first string is attribute being
   * searched and the second one is the value that is searched for
   * @return A pointer to the Model if found, nullptr otherwise.
   */
  T *find(const std::map<std::string, std::string> &query);

  /**
   * @brief Adds a Model to the database.
   * @param user The unique_ptr to object to add.
   * @def: db.add(std::move(the_unique_ptr_to_add));
   */
  T *add(std::unique_ptr<T> obj);

  /**
   * @brief Removes the Model from the Database and returns a pointer to it.
   * @param query Same as in find.
   */
  T *extract(const std::map<std::string, std::string> &query);
  bool remove(const std::map<std::string, std::string> &query);

  int size() const;

  void load(std::istream &file);
  void save(std::ostream &file);

  // iterators
  typename std::vector<std::unique_ptr<T>>::const_iterator begin() const;
  typename std::vector<std::unique_ptr<T>>::const_iterator end() const;

  typename std::vector<std::unique_ptr<T>>::iterator begin();
  typename std::vector<std::unique_ptr<T>>::iterator end();

  T *operator[](int ind);

private:
  std::vector<std::unique_ptr<T>> members;
  std::string filename;
};