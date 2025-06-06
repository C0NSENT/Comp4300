//
// Created by consent_ on 21/05/25.
//

#pragma once

#include "Components.hpp"

#include <array>
#include <source_location>

namespace lrh
{
    class Entity
    {

        friend class EntityManager;

        constexpr static bool isIndexesValid(const std::array<std::int8_t, 6>& arrComponentsIndexes);

        constexpr static void throwIfIndexesInvalid(const std::array<std::int8_t, 6>& arrComponentsIndexes,
            const std::source_location& location = std::source_location::current());

    public:
        enum class ComponentType : std::uint8_t
        {
            transform = 0, shape, collision, score, lifeSpan, input
        };

        [[nodiscard]] constexpr bool getIsExist() const;
        [[nodiscard]] constexpr std::int8_t getIndex(ComponentType type) const;

        [[nodiscard]] constexpr bool hasComponent(ComponentType type) const;

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

