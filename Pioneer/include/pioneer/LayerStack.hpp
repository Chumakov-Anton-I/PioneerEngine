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

#ifndef PIONEER_LAYER_STACK_HPP
#define PIONEER_LAYER_STACK_HPP

#include <pioneer/Support.hpp>
#include <vector>

namespace Pioneer
{

class PIONEER_API Layer;

class PIONEER_API LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);
    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin() { return m_layers.begin(); }
    std::vector<Layer *>::iterator end() { return m_layers.end(); }

private:
    std::vector<Layer *> m_layers;
    //std::vector<Layer *>::iterator m_layerInsert;
    size_t m_layerInserIndex;
};

}

#endif // !PIONEER_LAYER_STACK_HPP
