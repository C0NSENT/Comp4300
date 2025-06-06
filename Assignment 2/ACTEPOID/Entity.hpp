//
// Created by consent_ on 21/05/25.
//

#pragma once

#include "Components.hpp"

#include <array>

namespace lrh
{
    class Entity
    {
        using arrComponentsIndexes = std::array<std::int8_t, 6>;
        friend class EntityManager;

        constexpr static bool isIndexesValid(const std::array<std::int8_t, 6>& arrComponentsIndexes);

    public:

        enum class ComponentType : std::uint8_t
        {
            transform = 0, shape, collision, score, lifeSpan, input
        };

        constexpr bool getIsExist() const;
        constexpr std::int8_t getIndex(ComponentType type) const;

        constexpr bool hasComponent(ComponentType type) const;

        constexpr void setIsExist(bool isExist);
        constexpr void setIndex(ComponentType type, std::int8_t index);
        constexpr void setIndexes(const std::array<std::int8_t, 6>& arrComponentsIndexes);

    private:

        constexpr Entity() : m_isExist(true) {}
        constexpr Entity(const std::array<std::int8_t, 6>& arrComponentsIndexes);
        constexpr Entity(bool isExist, const std::array<std::int8_t, 6>& arrComponentsIndexes);

        bool m_isExist{false};
        std::array<std::int8_t, 6> m_arrComponentsIndexes{-1, -1, -1, -1, -1, -1};
    };
}

