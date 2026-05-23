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

#include <pioneer/Logger.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Pioneer
{

std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
std::shared_ptr<spdlog::logger> Logger::s_clientLogger;

void Logger::init()
{
    spdlog::set_pattern("%^[%T] %n %v%$");
    s_coreLogger = spdlog::stderr_color_mt("PIONEER");
    s_coreLogger->set_level(spdlog::level::trace);
    s_clientLogger = spdlog::stdout_color_mt("APP");
    s_clientLogger->set_level(spdlog::level::trace);
}

}
