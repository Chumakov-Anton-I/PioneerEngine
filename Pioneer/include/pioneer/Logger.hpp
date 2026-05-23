/* *****************************************************************************
PioneerEngine, a test game engine
Copyright (C) 2026  Chumakov Anton

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***************************************************************************** */

#ifndef PIONEER_LOGGER_HPP
#define PIONEER_LOGGER_HPP

#include <spdlog/spdlog.h>
#include <pioneer/Support.hpp>

#include <memory>

namespace Pioneer
{

class PIONEER_API Logger
{
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger> &coreLogger() { return s_coreLogger; }
    inline static std::shared_ptr<spdlog::logger> &clientLogger() { return s_clientLogger; }

private:
    static std::shared_ptr<spdlog::logger> s_coreLogger;
    static std::shared_ptr<spdlog::logger> s_clientLogger;
};

}

#ifndef NDEBUG
// Core log macroses
#define PNR_CORE_TRACE(...) ::Pioneer::Logger::coreLogger()->trace(__VA_ARGS__)
#define PNR_CORE_INFO(...)  ::Pioneer::Logger::coreLogger()->info(__VA_ARGS__)
#define PNR_CORE_WARN(...)  ::Pioneer::Logger::coreLogger()->warn(__VA_ARGS__)
#define PNR_CORE_ERROR(...) ::Pioneer::Logger::coreLogger()->error(__VA_ARGS__)
#define PNR_CORE_FATAL(...) ::Pioneer::Logger::coreLogger()->critical(__VA_ARGS__)

// Client log macroses
#define PNR_TRACE(...)      ::Pioneer::Logger::clientLogger()->trace(__VA_ARGS__)
#define PNR_INFO(...)       ::Pioneer::Logger::clientLogger()->info(__VA_ARGS__)
#define PNR_WARN(...)       ::Pioneer::Logger::clientLogger()->warn(__VA_ARGS__)
#define PNR_ERROR(...)      ::Pioneer::Logger::clientLogger()->error(__VA_ARGS__)
#define PNR_FATAL(...)      ::Pioneer::Logger::clientLogger()->critical(__VA_ARGS__)

#else

#define PNR_CORE_TRACE(...)
#define PNR_CORE_INFO(...)
#define PNR_CORE_WARN(...)
#define PNR_CORE_ERROR(...)
#define PNR_CORE_FATAL(...)

#define PNR_TRACE(...)
#define PNR_INFO(...)
#define PNR_WARN(...)
#define PNR_ERROR(...)
#define PNR_FATAL(...)

#endif // !NDEBUG

#endif // !PIONEER_LOGGER_HPP
