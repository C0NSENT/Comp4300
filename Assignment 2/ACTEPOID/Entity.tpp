/**
* @date 08-06-2025
 * @author consent_
 *
 * @brief Контейнер, который хранит компоненты
 */

#pragma once

#include "Components.hpp"
#include "Logger.hpp"

#include <cstdint>
#include <numeric>
#include <type_traits>
#include <vector>

namespace lrh
{
	template<typename T>
	concept isComponent = std::is_base_of_v<Component, T>
												and not std::is_same_v<T, Component>;


	class Entity
	{
		friend class EntityManager;

		template<typename T> requires isComponent<T>
		constexpr size_t getComponentIndex() const;

		template<typename T> requires isComponent<T>
		constexpr void throwIfHasComponent() const;


		constexpr explicit Entity( uint32_t id, bool isActive = true, uint8_t size = 4 );
		constexpr Entity( const Entity& rhs );
		~Entity();

		[[nodiscard]] constexpr bool getIsActive() const;

		[[nodiscard]] constexpr auto getId() const -> uint32_t;

		template<typename T> requires isComponent<T>
		[[nodiscard]] constexpr const T *getComponent() const;

		template<typename T> requires isComponent<T>
		[[nodiscard]] constexpr T *getComponentMutable();

		template<typename T> requires isComponent<T>
		[[nodiscard]] constexpr bool hasComponent() const;

		constexpr Entity &setIsActive( bool active );

		constexpr Entity &setId( uint32_t id );

		template<typename T> requires isComponent<T>
		Entity &addComponent();

		template<typename T> requires isComponent<T>
		Entity &addComponent( const T &component );

		template<typename T> requires isComponent<T>
		Entity &removeComponent();

	private:

		constexpr static size_t notFoundIndex{ std::numeric_limits<uint8_t>::max() + 1};

		bool m_isActive{};
		uint32_t m_id{};
		std::vector<Component *> m_vComponents;
	};


	template<typename T> requires isComponent<T>
	constexpr size_t Entity::getComponentIndex() const
	{
		for( auto i = 0u; i < this->m_vComponents.size(); ++i )
		{
			if (dynamic_cast<T *>(this->m_vComponents[i])) return i;
		}
		return notFoundIndex;
	}


	template<typename T> requires isComponent<T>
	constexpr void Entity::throwIfHasComponent() const
	{
		if( this->hasComponent<T>() )
		{
			Logger::fatal( "Entity already exists!" );
			throw std::logic_error( "Entity::addComponent<T>() : Component  already exists" );
		}
	}


	constexpr Entity::Entity( const uint32_t id, const bool isActive, const uint8_t size )
		: m_isActive{ isActive }, m_id{ id }
	{
		m_vComponents.reserve( size );
	}


	constexpr Entity::Entity( const Entity &rhs )
		: m_isActive{ rhs.m_isActive }
		, m_id{ rhs.m_id }
		, m_vComponents{ rhs.m_vComponents }
	{
		for ( auto component : rhs.m_vComponents)
			this->m_vComponents.emplace_back( component );
	}


	inline Entity::~Entity()
	{
		for( Component *component : m_vComponents )
		{
			delete component;
		}
	}


	constexpr bool Entity::getIsActive() const
	{
		return m_isActive;
	}


	constexpr uint32_t Entity::getId() const
	{
		return m_id;
	}


	template<typename T> requires isComponent<T>
	constexpr const T *Entity::getComponent() const
	{
		//Опять принцип dry пошел нахуй
		//TODO: Погуглить можно ли как-то кастовать одно в другое
		const auto index{ this->getComponentIndex<T>() };

		if( index != notFoundIndex )
		{
			const T *component{ static_cast<const T *>(m_vComponents[index]) };
			return component;
		}
		return nullptr;
	}


	template<typename T> requires isComponent<T>
	constexpr T *Entity::getComponentMutable()
	{
		const auto index{ this->getComponentIndex<T>() };

		if( index != notFoundIndex )
		{
			T *component{ static_cast<T *>(m_vComponents[index]) };
			return component;
		}
		return nullptr;
	}


	template<typename T> requires isComponent<T>
	constexpr bool Entity::hasComponent() const
	{
		return this->getComponentIndex<T>() != notFoundIndex;
	}


	constexpr Entity &Entity::setIsActive( const bool active )
	{
		this->m_isActive = active;
		return *this;
	}


	constexpr Entity &Entity::setId( const uint32_t id )
	{
		this->m_id = id;
		return *this;
	}


	template<typename T> requires isComponent<T>
	Entity &Entity::addComponent()
	{
		throwIfHasComponent<T>();

		this->m_vComponents.push_back( new T );

		return *this;
	}


	template<typename T> requires isComponent<T>
	Entity &Entity::addComponent( const T &component )
	{
		throwIfHasComponent<T>();

		this->m_vComponents.push_back( new T( component ) );

		return *this;
	}


	template<typename T> requires isComponent<T>
	Entity &Entity::removeComponent()
	{
		const auto index{ getComponentIndex<T>() };
		if( index  != notFoundIndex )
		{
			delete this->m_vComponents[index];
			m_vComponents.erase( m_vComponents.begin() + index );
		}

		return *this;
	}
}
