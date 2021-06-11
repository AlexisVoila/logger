#include "logger.h"

void usage_example() {
    using log = logging::logger;

    log::initialize("../test.log", log::console, log::level::info);
    log::debug("debug message");
    log::trace("trace message");
    log::info("info message");
    log::warning("warning message");
    log::error("error message");
    log::fatal("fatal message");
}

int main()
{
    usage_example();
    return 0;
}