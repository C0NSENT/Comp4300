#pragma once

#include <algorithm>
#include <cstdint>

#include "Components.hpp"

#include <vector>

namespace lrh
{
    template<typename T>
    concept isComponent = std::is_base_of_v<Component, T>
        and not std::is_same_v<T, Component>;

    class Entity
    {
        enum class ComponentType : uint8_t {
            transform=0, shape, collision, score, lifeSpan, input
        };


    public:
        constexpr Entity(uint32_t id, bool isActive = true);
        ~Entity();

        [[nodiscard]] constexpr bool getIsActive() const;
        [[nodiscard]] constexpr auto getId() const -> uint32_t;
        template <typename T>
        requires isComponent<T>
        constexpr const T* getComponent() const;

        template <typename T> requires isComponent<T>
        [[nodiscard]] constexpr bool hasComponent() const;

        void setIsActive(bool active);
        void setId(uint32_t id);

        template <typename T> requires isComponent<T>
        Entity& addComponent();

        template <typename T> requires isComponent<T>
        Entity& addComponent(const T& component);

    private:

        bool m_isActive;
        uint32_t m_id;
        std::vector<Component*> m_vComponents;
    };

    constexpr Entity::Entity(const uint32_t id, const bool isActive)
    : m_isActive(isActive), m_id(id)
    {
    }



    constexpr bool Entity::getIsActive() const
    {
        return m_isActive;
    }

    constexpr std::uint32_t Entity::getId() const
    {
        return m_id;
    }

    template<typename T> requires isComponent<T>
    constexpr const T* Entity::getComponent() const
    {
        for (const Component* component : this->m_vComponents)
        {
            if (this->hasComponent<T>()) {
                return static_cast<const T*>(component);
            }
        }
        return nullptr;
    }

    template<typename T> requires isComponent<T>
    constexpr bool Entity::hasComponent() const
    {
        for (const auto* component : m_vComponents)
        {
            if (dynamic_cast<const T*>(component) != nullptr)
                return true;
        }
        return false;
    }

    inline void Entity::setIsActive(const bool active)
    {
        this->m_isActive = active;
    }

    inline void Entity::setId(const uint32_t id)
    {
        this->m_id = id;
    }

    template<typename T> requires isComponent<T>
    Entity& Entity::addComponent()
    {
        this->m_vComponents.push_back(new T());
    }

    template<typename T> requires isComponent<T>
    Entity& Entity::addComponent(const T& component)
    {
        this->m_vComponents.push_back(new T(component));
    }
}

