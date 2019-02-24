#include "base/platform.h"
#include "base/log.h"

using namespace nb;

int main(int argc, char* argv[]) {

    if (argc < 1) {
        LOG_E << "usage: " << argv[0] << "config.json";
        return EXIT_FAILURE;
    }

    if (!platform::run(argv[1])) {
        LOG_E << "platform run failed.";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
