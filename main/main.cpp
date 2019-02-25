// Copyright [year] <Copyright Owner>

#include "base/log.h"
#include "base/platform.h"

using namespace nb;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    LOG_E << "usage: " << argv[0] << " config.json" << std::endl;
    return EXIT_FAILURE;
  }

  if (!platform::run(argv[1])) {
    LOG_E << "platform run failed.";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
