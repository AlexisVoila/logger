//
// Created by alexis_voila on 06.06.2021.
//

#include <iomanip>
#include <chrono>
#include <unordered_map>
#include <string>
#include "logger.h"

namespace logging {
    logger::logger() : log_output_{output::console}, severity_{level::info} {}

    logger& logging::logger::get() {
        if (instance_)
            return *instance_;
        else {
            create();
            return *instance_;
        }
    }

    void logger::create() {
        static logger the_instance;
        instance_ = &the_instance;
    }

    void logger::initialize(const std::string& file_path, logger::output log_output, logger::level log_level) {
        get().initialize_impl(file_path, log_output, log_level);
    }

    void logger::initialize_impl(const std::string& file_path, output log_output, level severity) {
        if (log_output == output::file || log_output == output::file_and_console)
            file_ = std::ofstream(file_path);
        log_output_ = log_output;
        severity_ = severity;
    }

    std::string logger::make_log_record_prefix(const level severity) {
        auto time = timestamp();
        auto wrapped_severity = "[" + severity_to_string(severity) + "]\t";
        return time + ' ' + wrapped_severity;
    }

    std::string logger::severity_to_string(level severity) {
        const static std::unordered_map<level, std::string> severity_map {
            {level::debug,   "debug"},
            {level::trace,   "trace"},
            {level::info,    "info"},
            {level::warning, "warning"},
            {level::error,   "error"},
            {level::fatal,   "fatal"},
        };

        auto it = severity_map.find(severity);
        if (it != severity_map.end())
            return it->second;

        return {};
    }

    std::string logging::logger::timestamp() {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t ( now );

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(localtime(&tt), "%F %T");
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return ss.str();
    }

    void logger::log(const std::string& message, logger::level severity) {
        if (severity < severity_ || message.empty() || log_output_ == none)
            return;

        auto pre_message = make_log_record_prefix(severity);
        auto total_message = pre_message + message;
        if (total_message[total_message.size() - 1] != '\n')
            total_message.push_back('\n');

        auto& out_stream = (severity <= level::info) ? std::cout : std::cerr;
        if (log_output_ == console || log_output_ == file_and_console)
            out_stream << total_message;

        if (file_.is_open() && (log_output_ & file))
            file_ << total_message;
    }

    logger::~logger() {
        instance_ = nullptr;
    }
}