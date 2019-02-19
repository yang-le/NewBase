#include <crtdbg.h>
#include <iostream>
#include "base/node.h"
#include "base/config.h"
#include "base/dynamic_lib.h"
#include "base/log.h"

void main(int argc, char* argv[]) {
    auto cfg = load_config_from_file(argv[1]);
    
    for (auto m : cfg["modules"]) {
        LOG_I << "module_library: " << m["module_library"] << std::endl;
        load_dynamic_lib(m["module_library"].get<std::string>());
        for (auto c : m["components"]) {
            LOG_I << "class_name: " << c["class_name"] << std::endl;
            auto n = create_node_obj(c["class_name"]);
            if (!n->init(c["config_file_path"])) {
                LOG_E << "init node" << c["class_name"] << "failed!" << std::endl;
            }
            LOG_I << "name: " << c["name"] << std::endl;
            LOG_I << "config_file_path: " << c["config_file_path"] << std::endl;
            //delete n;
        }
    }

    for (;;);
}
