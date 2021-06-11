//
// Created by alexis_voila on 06.06.2021.
//

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>

namespace logging {
    class logger {
    public:
        enum class level : int {
            debug,
            trace,
            info,
            warning,
            error,
            fatal
        };

        enum output : int {
            none,
            console,
            file,
            file_and_console
        };

        static void initialize(const std::string& file_path = "",
                               output log_output = console, level log_level = level::info);

        template <typename T>
        static void debug(const T& message) { get().log(message, level::debug); }
        template <typename T>
        static void trace(const T& message) { get().log(message, level::trace); }
        template <typename T>
        static void info(const T& message) { get().log(message, level::info); }
        template <typename T>
        static void warning(const T& message) { get().log(message, level::warning); }
        template <typename T>
        static void error(const T& message) { get().log(message, level::error); }
        template <typename T>
        static void fatal(const T& message) { get().log(message, level::fatal); }

        logger& operator=(const logger& other) = delete;
        logger(logger&& other) = delete;
        logger& operator=(logger&& other) = delete;

    private:
        logger();
        ~logger();

        static logger& get();

        template<typename T>
        void log(const T& message, logger::level severity) {
            std::stringstream ss;
            ss << message;
            log(ss.str(), severity);
        }

        void log(const std::string& message, level severity = level::info);

        void initialize_impl(const std::string& file_path, output log_output, level severity);

        static void create();
        static std::string make_log_record_prefix(level severity);
        static std::string severity_to_string(level severity);
        static std::string timestamp();

    private:
        static inline logger* instance_ = nullptr;
        std::ofstream file_;
        output log_output_ = console;
        level severity_ = level::info;
    };
}

#endif //LOGGER_LOGGER_H
