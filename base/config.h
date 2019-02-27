// Copyright [year] <Copyright Owner>

#pragma once

#include <string>
#include "base/macros.h"
#include "base/external/jsoncpp/json/json.h"

namespace nb {

using json = Json::Value;

NEW_BASE_EXPORT json load_config_from_file(const std::string& file_path);
NEW_BASE_EXPORT void save_config_to_file(const json& config,
                                         const std::string& file_path);

}  // namespace nb
