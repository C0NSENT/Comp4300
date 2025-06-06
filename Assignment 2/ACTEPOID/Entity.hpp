#pragma once

#include "Components.hpp"

#include <vector>
//#include<type_traits>

namespace lrh
{
    class Entity
    {
    public:
        constexpr Entity(std::uint32_t id, bool isActive = true);
        ~Entity();

        constexpr bool getIsActive() const;
        constexpr std::uint32_t getId() const;

        template <typename T> requires std::is_base_of_v<T, Component>
        constexpr T getComponent() const;

        template <typename T> requires std::is_base_of_v<Component, T>
        constexpr bool hasComponent() const;

        void setIsActive(bool active);
        void setId(std::uint32_t id);

        template <typename T> requires std::is_base_of_v<Component, T>
        void addComponent();

    private:
        bool m_isActive;
        std::uint32_t m_id;
        std::vector<Component*> m_vComponents;
    };

    constexpr Entity::Entity(const std::uint32_t id, const bool isActive)
        : m_isActive(isActive), m_id(id)
    {
    }

    inline Entity::~Entity() {
    }

    constexpr bool Entity::getIsActive() const
    {
        return m_isActive;
    }

    constexpr std::uint32_t Entity::getId() const
    {
        return m_id;
    }

    template<typename T> requires std::is_base_of_v<T, Component>
    constexpr T Entity::getComponent() const
    {

    }

    template<typename T> requires std::is_base_of_v<Component, T>
    constexpr bool Entity::hasComponent() const
    {
        for (const auto* component : m_vComponents) {

        }
    }

    inline void Entity::setIsActive(bool active)
    {
    }

    inline void Entity::setId(std::uint32_t id) {
    }

    template<typename T> requires std::is_base_of_v<Component, T>
    void Entity::addComponent() {
    }
}

