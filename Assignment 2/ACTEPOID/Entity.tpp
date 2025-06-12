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
#include <type_traits>
#include <vector>

namespace lrh
{
	template<typename T>
	concept isComponent = std::is_base_of_v<cmp::Component, T>
												and not std::is_same_v<T, cmp::Component>;


	class Entity
	{

		template<typename T> requires isComponent<T>
		constexpr  int16_t getComponentIndex() const;

	public:

		template<typename T> requires isComponent<T>
		constexpr void throwIfHasComponent() const;

		explicit Entity(bool isActive = true, int16_t size = 4 );
		Entity( const Entity& rhs );
		~Entity();

		[[nodiscard]] constexpr bool getIsActive() const;

		template<typename T> requires isComponent<T>
		[[nodiscard]] constexpr const T *getComponent() const;

		template<typename T> requires isComponent<T>
		[[nodiscard]] constexpr T *getComponentMutable();

		template<typename T> requires isComponent<T>
		[[nodiscard]] constexpr bool hasComponent() const;

		constexpr Entity &setIsActive( bool active );

		template<typename T> requires isComponent<T>
		Entity &addComponent();

		template<typename T> requires isComponent<T>
		Entity &addComponent( const T &component );

		template<typename T> requires isComponent<T>
		Entity &addComponent( T &&component );

		template<typename T> requires isComponent<T>
		Entity &removeComponent();

	private:
		static constexpr int16_t MAX_SIZE{ 256 };
		static constexpr int16_t NOT_FOUND_INDEX{ -1 };

		bool m_isActive{};
		std::vector<cmp::Component *> m_vComponents{};
	};


	template<typename T> requires isComponent<T>
	constexpr int16_t Entity::getComponentIndex() const
	{
		for( auto i = 0u; i < this->m_vComponents.size(); ++i )
		{
			if (dynamic_cast<T *>(this->m_vComponents[i])) return i;
		}
		return NOT_FOUND_INDEX;
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


	inline Entity::Entity(const bool isActive, const int16_t size )
		: m_isActive{ isActive }
	{
		if ( size < 0 )
			throw std::logic_error( "Entity::Entity() : size < 0" );

		if( size > MAX_SIZE )
			throw std::logic_error( "Entity::Entity() : size > MAX_SIZE" );

		m_vComponents.reserve( size );
	}


	inline Entity::Entity( const Entity &rhs )
		: m_isActive{ rhs.m_isActive }
	{
		m_vComponents.reserve( rhs.m_vComponents.size() );

		for (const auto* component : rhs.m_vComponents)
			if (component)
				m_vComponents.push_back( new auto(*component));
	}


	inline Entity::~Entity()
	{
		for( const cmp::Component *component : m_vComponents )
		{
			delete component;
		}
	}


	constexpr bool Entity::getIsActive() const
	{
		return m_isActive;
	}


	template<typename T> requires isComponent<T>
	constexpr const T *Entity::getComponent() const
	{
		//Опять принцип dry пошел нахуй
		//TODO: Погуглить можно ли как-то кастовать одно в другое
		const auto index{ this->getComponentIndex<T>() };

		if( index != NOT_FOUND_INDEX )
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

		if( index != NOT_FOUND_INDEX )
		{
			T *component{ static_cast<T *>(m_vComponents[index]) };
			return component;
		}
		return nullptr;
	}


	template<typename T> requires isComponent<T>
	constexpr bool Entity::hasComponent() const
	{
		return this->getComponentIndex<T>() != NOT_FOUND_INDEX;
	}


	constexpr Entity &Entity::setIsActive( const bool active )
	{
		this->m_isActive = active;
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
		if( index  != NOT_FOUND_INDEX )
		{
			delete this->m_vComponents[index];
			m_vComponents.erase( m_vComponents.begin() + index );
		}

		return *this;
	}
}
