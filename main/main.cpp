#include <crtdbg.h>
#include <iostream>
#include "base/platform.h"
#include "base/log.h"

using namespace nb;

int main(int argc, char* argv[]) {

    if (!platform::run(argv[1])) {
        LOG_E << "platform run failed.";
        return -1;
    }

    return 0;
}
