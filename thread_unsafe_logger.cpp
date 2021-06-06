//
// Created by alexis_voila on 06.06.2021.
//

#include "thread_unsafe_logger.h"
#include <unordered_map>
#include <chrono>
#include <iomanip>

namespace logging {

    thread_unsafe_logger& thread_unsafe_logger::get() {
        if (instance_)
            return *instance_;
        else {
            create();
            return *instance_;
        }
    }

    thread_unsafe_logger::thread_unsafe_logger() : file_{}, output_{Output::console}, severity_{Severity::info} {}

    void thread_unsafe_logger::create() {
        static thread_unsafe_logger the_instance;
        instance_ = &the_instance;
    }

    std::string thread_unsafe_logger::make_log_record_prefix(const logger::Severity severity) {
        auto time = timestamp();
        auto wrapped_severity = "[" + severity_to_string(severity) + "] ";
        return time + ' ' + wrapped_severity;
    }

    void thread_unsafe_logger::log_impl(const std::string& msg, logger::Severity severity) {
        if (severity < severity_ || msg.empty() || output_ == none)
            return;

        auto pre_message = make_log_record_prefix(severity);
        auto total_message = pre_message + msg;
        if (total_message[total_message.size() - 1] != '\n')
            total_message.push_back('\n');

        auto& out_stream = (severity <= info) ? std::cout : std::cerr;
        if (output_ == console || output_ == file_and_console)
            out_stream << total_message;

        if (file_.is_open() && (output_ & file))
            file_ << total_message;
    }

    void thread_unsafe_logger::init_impl(const std::string& file_path, logger::Output output, logger::Severity severity) {
        if (output == file || output == file_and_console) {
            file_.open(file_path);
            if (!file_.is_open())
                throw std::runtime_error("Can't open a log file");
        }

        output_ = output;
        severity_ = severity;
    }

    std::string thread_unsafe_logger::severity_to_string(logger::Severity severity) {
        const static std::unordered_map<Severity, std::string> severity_map {
            {debug, "debug"},
            {trace, "strace"},
            {info, "info"},
            {warning, "warning"},
            {error, "error"},
            {fatal, "fatal"},
        };

        auto it = severity_map.find(severity);
        if (it != severity_map.end())
            return it->second;

        return {};
    }

    std::string thread_unsafe_logger::timestamp() {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t ( now );

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(localtime(&tt), "%F %T");
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return ss.str();
    }
}
