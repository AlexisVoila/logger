# Simple logger implementation
___
Simple C++ logger for single threaded programs

## Dependencies
___
* CMake

## Usage example
___
```
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
```
### Output
```
2021-05-06 22:54:39.930 [info] info message
2021-05-06 22:54:39.930 [warning] warning message
2021-05-06 22:54:39.930 [error] error message
2021-05-06 22:54:39.930 [fatal] fatal message
2021-05-06 22:54:39.930 [warning] record from thread_unsafe_logger

```
