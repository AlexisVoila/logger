#include "thread_unsafe_logger.h"

void usage_example() {
    using logging::logger;

    logger& lg = logging::thread_unsafe_logger::get();

    lg.init("../test.log", logger::file_and_console);
    lg.log("debug message", logger::debug);
    lg.log("trace message", logger::trace);
    lg.log("info message", logger::info);
    lg.log("warning message", logger::warning);
    lg.log("error message", logger::error);
    lg.log("fatal message", logger::fatal);

    logging::thread_unsafe_logger::get().log("record from thread_unsafe_logger", logger::warning);
}

int main()
{
    usage_example();
    return 0;
}