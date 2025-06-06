//
// Created by consent_ on 21/05/25.
//

#include "Entity.hpp"

#include "Logger.hpp"
#include <source_location>


namespace lrh
{
    constexpr bool Entity::isIndexesValid(const std::array<std::int8_t, 6>& arrComponentsIndexes)
    {
        for (const auto index : arrComponentsIndexes)
        {
            if (index < 0) return false;
        }
        return true;
    }

    constexpr bool Entity::getIsExist() const
    {
        return m_isExist;
    }

    constexpr std::int8_t Entity::getIndex(const ComponentType type) const
    {
        return m_arrComponentsIndexes[static_cast<std::uint8_t>(type)];
    }

    constexpr bool Entity::hasComponent(const ComponentType type) const
    {
        if (m_arrComponentsIndexes[static_cast<std::uint8_t>(type)] == -1)
            return false;

        return true;
    }

    constexpr void Entity::setIsExist(const bool isExist)
    {
        this->m_isExist = isExist;
    }

    constexpr void Entity::setIndex(const ComponentType type, const std::int8_t index)
    {
        m_arrComponentsIndexes[static_cast<std::uint8_t>(type)] = index;
    }

    constexpr void Entity::setIndexes(const std::array<std::int8_t, 6>& arrComponentsIndexes)
    {
        static_assert(isIndexesValid(arrComponentsIndexes),
            "Entity::setIndexes(): indexes are not valid");

        m_arrComponentsIndexes = arrComponentsIndexes;
    }

    constexpr Entity::Entity(const std::array<std::int8_t, 6> &arrComponentsIndexes)
        : Entity(true, arrComponentsIndexes) {}

    constexpr Entity::Entity(const bool isExist, const std::array<std::int8_t, 6> &arrComponentsIndexes)
        : m_isExist(isExist), m_arrComponentsIndexes(arrComponentsIndexes)
    {
        static_assert(isIndexesValid(m_arrComponentsIndexes), "Entity::Entity(): indexes are not valid");
    }
}