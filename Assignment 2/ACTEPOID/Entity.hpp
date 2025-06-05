//
// Created by consent_ on 21/05/25.
//

#pragma once

#include "Components.hpp"

#include <tuple>

namespace lrh
{
    class Entity
    {
        friend class EntityManager;

        enum class tag : std::uint8_t
        {
            player, enemy ///дописать теги
        };

        bool m_isActive;
        std::uint8_t m_id;
        tag m_tag;

        constexpr Entity(std::uint8_t id, tag tag);

    public:

        std::tuple<CTransform, CShape, CCollision,
        CInput, CScore, CLifespan> tComponents;

        [[nodiscard]] constexpr bool getIsActive() const;

        [[nodiscard]] constexpr tag getTag() const;

        [[nodiscard]] constexpr std::uint8_t id() const;

        constexpr void destroy();


    };
}

