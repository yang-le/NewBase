#include "base/node.h"

NEW_BASE_BEGIN

std::shared_ptr<node_base> create_node_obj(const std::string& class_name) {
    return create_class_obj<node_base>(class_name);
}

NEW_BASE_END
