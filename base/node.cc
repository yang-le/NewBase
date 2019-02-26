// Copyright [year] <Copyright Owner>

#include "base/node.h"

namespace nb {

node_base* create_node_obj(const std::string& class_name) {
  return create_class_obj<node_base>(class_name);
}

}
