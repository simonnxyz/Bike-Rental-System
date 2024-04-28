#include "../include/Database.h"
#include <fstream>

#pragma once

template <class T>
Database<T>::Database(const std::string &file_name) : filename(file_name) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::invalid_argument("File not found");
  }
  load(file);
  file.close();
}

template <class T> Database<T>::~Database() {
  if (members.empty())
    return;
  std::ofstream file(filename);
  save(file);
  file.close();
}

template <class T> T *Database<T>::find_by_id(const std::string &id) {
  for (auto &member : members) {
    if (member->get_id() == id) {
      return member.get();
    }
  }
  return nullptr;as
};

template <class T>
T *Database<T>::find(const std::map<std::string, std::string> &query) {
  for (auto &member : members) {
    if (member->check_query(query)) {
      return member.get();
    }
  }

  return nullptr;
}

template <class T> T *Database<T>::add(std::unique_ptr<T> obj) {
  members.push_back(std::move(obj));
  return members.back().get();
}

template <class T>
T *Database<T>::extract(const std::map<std::string, std::string> &query) {
  for (auto it = members.begin(); it != members.end(); ++it) {
    if (it->get()->check_query(query)) {
      T *result = it->get();
      members.erase(it);
      return result;
    }
  }

  return nullptr;
}

template <class T>
bool Database<T>::remove(const std::map<std::string, std::string> &query) {
  for (auto it = members.begin(); it != members.end(); ++it) {
    if (it->get()->check_query(query)) {
      members.erase(it);
      return true;
    }
  }

  return false;
}

template <class T> void Database<T>::load(std::istream &file) {
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
}

template <class T> void Database<T>::save(std::ostream &file) {
  for (auto &member : members) {
    file << member->str() << "\n";
  }
}

template <class T> int Database<T>::size() const { return members.size(); }

template <class T>
typename std::vector<std::unique_ptr<T>>::const_iterator
Database<T>::begin() const {
  return members.begin();
}
template <class T>
typename std::vector<std::unique_ptr<T>>::const_iterator
Database<T>::end() const {
  return members.end();
}
template <class T>
typename std::vector<std::unique_ptr<T>>::iterator Database<T>::begin() {
  return members.begin();
}
template <class T>
typename std::vector<std::unique_ptr<T>>::iterator Database<T>::end() {
  return members.end();
}

template <class T> T *Database<T>::operator[](int ind) {
  return members.at(ind).get();
}