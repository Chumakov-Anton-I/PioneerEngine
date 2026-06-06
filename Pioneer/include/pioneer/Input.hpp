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

#ifndef PIONEER_INPUT_HPP
#define PIONEER_INPUT_HPP

#include <pioneer/Support.hpp>

namespace Pioneer
{

/**
* @brief The Input class
* 
* Global input control object
*/
class PIONEER_API Input
{
public:
    inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
    inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
    inline static std::pair<float, float> mousePos() { return s_instance->mousePosImpl(); }
    inline static float mousePosX() { return s_instance->mousePosXImpl(); }
    inline static float mousePosY() { return s_instance->mousePosYImpl(); }

protected:
    virtual bool isKeyPressedImpl(int keycode);
    virtual bool isMouseButtonPressedImpl(int button);
    virtual std::pair<float, float> mousePosImpl();
    virtual float mousePosXImpl();
    virtual float mousePosYImpl();

private:
    static Input *s_instance;
};

}

#endif // !PIONEER_INPUT_HPP

