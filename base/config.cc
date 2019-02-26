// Copyright [year] <Copyright Owner>

#include "base/config.h"

namespace nb {
json load_config_from_file(const std::string& file_path) {
  std::ifstream ifs(file_path);
  json config;
  ifs >> config;
  return config;
}

void save_config_to_file(const json& config, const std::string& file_path) {
  std::ofstream ofs(file_path);
  config >> ofs;
}
}  // namespace nb
