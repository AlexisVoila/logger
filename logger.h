//
// Created by alexis_voila on 06.06.2021.
//

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>

namespace logging {
    class logger {
    public:
        enum Severity : int {
            debug,
            trace,
            info,
            warning,
            error,
            fatal
        };

        enum Output : int {
            none,
            console,
            file,
            file_and_console
        };

        void log(const std::string& message, Severity severity = info);

        void init(const std::string& file_path = "", Output output = console, Severity severity = info);

        logger() = default;

        logger(const logger& other) = delete;

        logger& operator=(const logger& other) = delete;

        logger(logger&& other) = delete;

        logger& operator=(logger&& other) = delete;

    protected:
        virtual ~logger() = default;

    private:
        virtual void log_impl(const std::string& msg, Severity severity) = 0;

        virtual void init_impl(const std::string& file_path, Output output, Severity severity) = 0;
    };
}

#endif //LOGGER_LOGGER_H
