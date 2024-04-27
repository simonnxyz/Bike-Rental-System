#include <Model.h>
#include <memory>
#include <vector>

class Database {
public:
  Database();

  Model find_by_id();
  Model find();

private:
  std::vector<std::unique_ptr<Model>> members;
};