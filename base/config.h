// Copyright [year] <Copyright Owner>

#pragma once

#include <string>
#include <fstream>
#include "base/macros.h"
#include "external/json.hpp"

NEW_BASE_BEGIN

using json = nlohmann::json;

NEW_BASE_EXPORT json load_config_from_file(const std::string& file_path);
NEW_BASE_EXPORT void save_config_to_file(const json& config,
                                         const std::string& file_path);

NEW_BASE_END
