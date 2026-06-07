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

#ifndef PIONEER_SUPPORT_HPP
#define PIONEER_SUPPORT_HPP

#ifdef _WIN32
#   ifndef PIONEER_BUILD_STATIC_LIB
#       ifdef PIONEER_LIBRARY_BUILD
#           define PIONEER_API __declspec(dllexport)
#       else
#           define PIONEER_API __declspec(dllimport)
#       endif
#   else
#       define PIONEER_API
#   endif
#else // *nix || MacOS
#   ifndef PIONEER_BUILD_STATIC_LIB
#       ifdef PIONEER_LIBRARY_BUILD
#           define PIONEER_API __attribute__((visibility("default")))
#       else
#           define PIONEER_API
#       endif
#   else
#       define PIONEER_API
#   endif
#endif

#ifdef PIONEER_ENABLE_ASSERTS
#   include <cassert>
#   define PNR_ASSERT(x, ...) { if (!(x)) { PNR_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(false); } }
#   define PNR_CORE_ASSERT(x, ...) { if (!(x)) { PNR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); assert(false); } }
#else
#   define PNR_ASSERT(x, ...)
#   define PNR_CORE_ASSERT(x, ...)
#endif // PIONEER_ENABLE_ASSERTS

template<typename T>
constexpr auto BIT(T x) { return (1 << x); }

#define PNR_BIND_EVENT_FCN(fcn) std::bind(&fcn, this, std::placeholders::_1)

namespace Pioneer
{

PIONEER_API const char *engineVersion();

}

#endif // !PIONEER_SUPPORT_HPP
