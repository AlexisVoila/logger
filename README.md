# Simple logger implementation
___
Simple C++ logger for single threaded programs

## Dependencies
___
* CMake
* C++17 

## Usage example
___
```
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
```
### output
```
2021-06-11 23:03:49.418 [info]  info message
2021-06-11 23:03:49.418 [warning]       warning message
2021-06-11 23:03:49.418 [error] error message
2021-06-11 23:03:49.418 [fatal] fatal message

```
