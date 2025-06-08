/**
* @date 08-06-2025
 * @author consent_
 *
 * @brief
 */

#pragma once

#include "Components.hpp"
#include "Logger.hpp"

#include <vector>
#include <type_traits>
#include <cstdint>
#include <numeric>

namespace lrh
{
    template<typename T>
    concept isComponent = std::is_base_of_v<Component, T>
        and not std::is_same_v<T, Component>;

    class Entity
    {
        template<typename T> requires isComponent<T>
        constexpr size_t getComponentIndex() const;

        template<typename T> requires isComponent<T>
        constexpr void throwIfHasComponent() const;

    public:
        constexpr Entity(uint32_t id, bool isActive = true);
        ~Entity();

        [[nodiscard]] constexpr bool getIsActive() const;
        [[nodiscard]] constexpr auto getId() const -> uint32_t;
        template <typename T> requires isComponent<T>
        [[nodiscard]] constexpr const T* getComponent() const;

        template <typename T> requires isComponent<T>
        [[nodiscard]] constexpr T* getComponentMutable();

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
        //Опять принцип dry пошел нахуй
        const auto index{ this-> getComponentIndex<T>() };

        if (index != std::numeric_limits<size_t>::max())
        {
            const T* component{ static_cast<const T*>(m_vComponents[index])};
            return component;
        }
        return nullptr;
    }

    template<typename T> requires isComponent<T>
    constexpr T* Entity::getComponentMutable()
    {
        const auto index{ this->getComponentIndex<T>() };
        if ( index != std::numeric_limits<size_t>::max())
        {
            T* component{static_cast<T*>(m_vComponents[index])};
            return component;
        }
        return nullptr;
    }

    template<typename T> requires isComponent<T>
    constexpr bool Entity::hasComponent() const
    {
        return (this->getComponentIndex<T>() != -1);
    }

    template<typename T> requires isComponent<T>
    constexpr size_t Entity::getComponentIndex() const
    {
        for (size_t i = 0u; i < this->m_vComponents.size(); ++i)
        {
            if (dynamic_cast<const T*>(this->m_vComponents[i]) != nullptr)
                return i;
        }
        ///Индекс массива никогда не будет равен максимуму
        return std::numeric_limits<size_t>::max();
    }

    template<typename T> requires isComponent<T>
    constexpr void Entity::throwIfHasComponent() const
    {
        if (this->hasComponent<T>())
        {
            Logger::fatal("Entity already exists!");
            throw std::logic_error("Entity::addComponent<T>() : Component  already exists");
        }
    }

    template<typename T> requires isComponent<T>
    Entity& Entity::addComponent()
    {
        throwIfHasComponent<T>();
        this->m_vComponents.push_back(new T());
        return *this;
    }

    template<typename T> requires isComponent<T>
    Entity& Entity::addComponent(const T& component)
    {
        throwIfHasComponent<T>();
        this->m_vComponents.push_back(new T(component));
        return *this;
    }
}

