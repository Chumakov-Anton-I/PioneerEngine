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

#include <pioneer/Support.hpp>
#include <version.h>

#ifndef PIONEER_VERSION_MAJOR
#define PIONEER_VERSION_MAJOR 0
#endif
#ifndef PIONEER_VERSION_MINOR
#define PIONEER_VERSION_MINOR 0
#endif
#ifndef PIONEER_VERSION_PATCH
#define PIONEER_VERSION_PATCH 0
#endif
#ifndef PIONEER_VERSION_BUILD
#define PIONEER_VERSION_BUILD "0"
#endif

#define VERS(version, build) "Pioneer Engine v"##version" build "##build

namespace Pioneer
{

PIONEER_API const char *engineVersion()
{
    return VERS(PIONEER_VERSION_STR, PIONEER_VERSION_BUILD);
}

}
