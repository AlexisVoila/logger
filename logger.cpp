//
// Created by alexis_voila on 06.06.2021.
//

#include "logger.h"
#include <string>

namespace logging {
    void logger::init(const std::string& file_path, logger::Output output, logger::Severity severity) {
        init_impl(file_path, output, severity);
    }

    void logger::log(const std::string& message, logger::Severity severity) {
        log_impl(message, severity);
    }
}