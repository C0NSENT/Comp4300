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
	concept isComponent = std::is_base_of_v<cmp::BaseComponent, T>
												and not std::is_same_v<T, cmp::BaseComponent>;


	class Entity
	{
		template<typename T> requires isComponent<T>
		int16_t getComponentIndex() const;

		template<typename T> requires isComponent<T>
		void throwIfHasComponent() const;

	public:

		Entity(bool isActive = true, int16_t size = 4 );
		Entity( const Entity& rhs );
		Entity( Entity&& rhs);
		~Entity();

		[[nodiscard]] bool getIsActive() const;

		template<typename T> requires isComponent<T>
		[[nodiscard]] const T *getComponent() const;

		template<typename T> requires isComponent<T>
		[[nodiscard]] T *getComponentMutable();

		template<typename T> requires isComponent<T>
		[[nodiscard]] bool hasComponent() const;

		Entity &setIsActive( bool active );

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
		std::vector<cmp::BaseComponent *> m_vComponents{};
	};


	template<typename T> requires isComponent<T>
	int16_t Entity::getComponentIndex() const
	{
		for( auto i = 0u; i < this->m_vComponents.size(); ++i )
		{
			if (dynamic_cast<T *>(this->m_vComponents[i])) return i;
		}
		return NOT_FOUND_INDEX;
	}


	template<typename T> requires isComponent<T>
	void Entity::throwIfHasComponent() const
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
				m_vComponents.push_back(  component->clone() );
	}


	inline Entity::Entity( Entity &&rhs )
		: m_isActive{ rhs.m_isActive}
		,m_vComponents{ std::move( rhs.m_vComponents ) }
	{
		rhs.m_isActive = false;
	}


	inline Entity::~Entity()
	{
		for( const cmp::BaseComponent *component : m_vComponents )
		{
			delete component;
		}
	}


	inline bool Entity::getIsActive() const
	{
		return m_isActive;
	}


	template<typename T> requires isComponent<T>
	const T *Entity::getComponent() const
	{
		const auto index{ this->getComponentIndex<T>() };

		if( index != NOT_FOUND_INDEX )
		{
			const T *component{ static_cast<const T *>(m_vComponents[index]) };
			return component;
		}
		return nullptr;
	}


	template<typename T> requires isComponent<T>
	T *Entity::getComponentMutable()
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
	bool Entity::hasComponent() const
	{
		return this->getComponentIndex<T>() != NOT_FOUND_INDEX;
	}


	inline Entity &Entity::setIsActive( const bool active )
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
	Entity &Entity::addComponent( T &&component )
	{
		throwIfHasComponent<T>();

		this->m_vComponents.push_back( new T( std::forward<T>( component ) ) );

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
