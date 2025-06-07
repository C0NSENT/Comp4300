#include "Entity.hpp"

namespace lrh
{
    Entity::~Entity()
    {
        for (auto* component : m_vComponents) {
            delete component;
        }
    }
}