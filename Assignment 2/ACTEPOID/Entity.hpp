#pragma once

#include "Components.hpp"

#include <vector>
#include <type_traits>
#include <cstdint>

namespace lrh
{
    template<typename T>
    concept isComponent = std::is_base_of_v<Component, T>
        and not std::is_same_v<T, Component>;

    class Entity
    {
        template<typename T> requires isComponent
        size_t getIndex() const;

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

        constexpr Entity& setIsActive(bool active);

        constexpr Entity& setId(uint32_t id);

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
        : m_isActive(isActive), m_id(id) {}

    template<typename T> requires isComponent<T>
   constexpr const T* Entity::getComponent() const
    {
        for (const Component* component : this->m_vComponents)
        {
            //Да знаю принцип DRY пошел нахуй
            if (dynamic_cast<const T*>(component) != nullptr) {
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

    template<typename T> requires isComponent
    size_t Entity::getIndex() const
    {
        for (auto i )
    }

    template<typename T> requires isComponent<T>
  Entity& Entity::addComponent()
    {
        this->m_vComponents.push_back(new T());
        return *this;
    }

    template<typename T> requires isComponent<T>
    Entity& Entity::addComponent(const T& component)
    {
        this->m_vComponents.push_back(new T(component));
        return *this;
    }
}

