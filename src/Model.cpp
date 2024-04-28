#include "../include/Model.h"
#include "Uuid.cpp"

Model::Model() { id = uuid::generate_uuid_v4(); }

std::string Model::get_id() const { return id; }

void Model::set_id(const std::string &new_id) { id = new_id; }