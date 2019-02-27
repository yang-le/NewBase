// Copyright [year] <Copyright Owner>

#include <fstream>
#include "base/config.h"

namespace nb {
json load_config_from_file(const std::string& file_path) {
  json config;

  std::ifstream(file_path) >> config;

  return config;
}

void save_config_to_file(const json& config, const std::string& file_path) {
  std::ofstream(file_path) << config;
}
}  // namespace nb
