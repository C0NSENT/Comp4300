#include "Entity.hpp"

namespace lrh
{
    Entity::~Entity()
    {
        for (auto* component : m_vComponents) {
            delete component;
        }
    }

    constexpr bool Entity::getIsActive() const
    {
        return m_isActive;
    }

    constexpr std::uint32_t Entity::getId() const
    {
        return m_id;
    }

    constexpr Entity& Entity::setIsActive(const bool active)
    {
        this->m_isActive = active;
        return *this;
    }

    constexpr Entity&Entity::setId(const uint32_t id)
    {
        this->m_id = id;
        return *this;
    }
}