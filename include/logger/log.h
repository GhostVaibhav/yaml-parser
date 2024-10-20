#pragma once

// Including the Spdlog library
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace ypars {

extern std::shared_ptr<spdlog::logger> logger;

}  // namespace ypars
