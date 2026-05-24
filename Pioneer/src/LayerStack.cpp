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

#include <pioneer/LayerStack.hpp>
#include <pioneer/Layer.hpp>

#include <algorithm>

namespace Pioneer
{

LayerStack::LayerStack()
{
    m_layerInsert = m_layers.begin();
}

LayerStack::~LayerStack()
{
    for (auto *layer : m_layers)
        delete layer;
}

void LayerStack::pushLayer(Layer *layer)
{
    m_layerInsert = m_layers.emplace(m_layerInsert, layer);
}

void LayerStack::pushOverlay(Layer *overlay)
{
    m_layers.emplace_back(overlay);
}

void LayerStack::popLayer(Layer *layer)
{
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end())
    {
        m_layers.erase(it);
        m_layerInsert--;
    }
}

void LayerStack::popOverlay(Layer *overlay)
{
    auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
    if (it != m_layers.end())
        m_layers.erase(it);
}

}
