//
// Created by alexis_voila on 06.06.2021.
//

#ifndef LOGGER_THREAD_UNSAFE_LOGGER_H
#define LOGGER_THREAD_UNSAFE_LOGGER_H

#include "logger.h"
#include <fstream>

namespace logging {
    class thread_unsafe_logger final : public logger {
    public:
        static thread_unsafe_logger& get();

    private:
        thread_unsafe_logger();
        ~thread_unsafe_logger() override { instance_ = nullptr; }

        static void create();

        static std::string make_log_record_prefix(Severity severity);

        void log_impl(const std::string& msg, Severity severity) final;

        void init_impl(const std::string& file_path, Output output, Severity severity) final;

        static std::string severity_to_string(Severity severity);

        static std::string timestamp();

        static inline thread_unsafe_logger* instance_ = nullptr;

        std::ofstream file_;
        Output output_;
        Severity severity_;
    };
}


#endif //LOGGER_THREAD_UNSAFE_LOGGER_H
