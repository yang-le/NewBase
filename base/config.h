#pragma once

#include <fstream>
#include "external/json.hpp"
#include "base/macros.h"

NEW_BASE_BEGIN

using json = nlohmann::json;

NEW_BASE_EXPORT json load_config_from_file(const std::string & file_path);
NEW_BASE_EXPORT void save_config_to_file(const json& config, const std::string & file_path);

NEW_BASE_END
