#include <Model.h>
#include <iterator>
#include <memory>

#pragma once

template <class T> class Database {
public:
  static_assert(std::is_base_of<Model, T>::value,
                "Database class only works on subclass of Model");
  // constructors
  Database(const std::string &filename = "");
  ~Database();

  // other
  T *find_by_id(const std::string &id);
  T *find(const std::map<std::string, std::string> &query);

  T *add(std::unique_ptr<T> obj);
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