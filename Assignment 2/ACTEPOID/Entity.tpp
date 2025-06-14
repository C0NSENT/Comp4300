/**
* @date 08-06-2025
 * @author consent_
 *
 * @brief Контейнер, который хранит компоненты
 */

#pragma once

#include "Components.hpp"

#include <type_traits>
#include <vector>

#include "Logger.hpp"

namespace lrh
{
	template<typename C>
	concept isComponent = std::is_base_of_v<cmp::BaseComponent, C>
												and not std::is_same_v<C, cmp::BaseComponent>;


	class Entity
	{

		template<typename C> requires isComponent<C>
		int16_t getComponentIndex() const;

		template<typename C> requires isComponent<C>
		void throwIfHasComponent() const;

	public:

		explicit Entity(bool isActive = true, int16_t size = 4 );
		Entity( const Entity& rhs );
		Entity( Entity&& rhs) noexcept ;
		~Entity();

		template<typename C> requires isComponent<C>
		[[nodiscard]] const C *get() const;

		template<typename C> requires isComponent<C>
		[[nodiscard]] C *getMutable();

		template<typename C> requires isComponent<C>
		[[nodiscard]] bool has() const;

		template<typename C> requires isComponent<C>
		Entity &add();

		template<typename C> requires isComponent<C>
		Entity &add( const C &component );

		template<typename C> requires isComponent<C>
		Entity &add( C &&component );

		template<typename C> requires isComponent<C>
		Entity &removeComponent();

		bool isActive{};

	private:

		static constexpr int16_t MAX_SIZE{ 256 };
		static constexpr int16_t NOT_FOUND_INDEX{ -1 };

		std::vector<cmp::BaseComponent *> m_vComponents{};
	};


	template<typename C> requires isComponent<C>
	int16_t Entity::getComponentIndex() const
	{
		for( int16_t i = 0; i < this->m_vComponents.size(); ++i )
		{
			if (dynamic_cast<C *>(this->m_vComponents[i])) return i;
		}
		return NOT_FOUND_INDEX;
	}


	template<typename C> requires isComponent<C>
	void Entity::throwIfHasComponent() const
	{
		if( this->has<C>() )
		{
			Logger::fatal( "Entity already exists!" );
			throw std::logic_error( "Entity::addComponent<C>() : Component  already exists" );
		}
	}


	inline Entity::Entity(const bool isActive, const int16_t size )
		: isActive{ isActive }
	{
		if ( size < 0 )
			throw std::logic_error( "Entity::Entity() : size < 0" );

		if( size > MAX_SIZE )
			throw std::logic_error( "Entity::Entity() : size > MAX_SIZE" );

		m_vComponents.reserve( size );
	}


	inline Entity::Entity( const Entity &rhs )
		: isActive{ rhs.isActive }
	{
		m_vComponents.reserve( rhs.m_vComponents.size() );

		for (const auto* component : rhs.m_vComponents)
			if (component)
				m_vComponents.push_back(  component->clone() );
	}


	inline Entity::Entity( Entity &&rhs ) noexcept
		: isActive{ rhs.isActive}
		,m_vComponents{ std::move( rhs.m_vComponents ) }
	{
		rhs.isActive = false;
	}


	inline Entity::~Entity()
	{
		for( const cmp::BaseComponent *component : m_vComponents )
			delete component;
	}


	template<typename C> requires isComponent<C>
	const C *Entity::get() const
	{
		const auto index{ this->getComponentIndex<C>() };

		if( index != NOT_FOUND_INDEX )
		{
			const C *component{ static_cast<const C *>(m_vComponents[index]) };
			return component;
		}
		return nullptr;
	}


	template<typename C> requires isComponent<C>
	C *Entity::getMutable()
	{
		const auto index{ this->getComponentIndex<C>() };

		if( index != NOT_FOUND_INDEX )
		{
			C *component{ static_cast<C *>(m_vComponents[index]) };
			return component;
		}
		return nullptr;
	}


	template<typename C> requires isComponent<C>
	bool Entity::has() const
	{
		return this->getComponentIndex<C>() != NOT_FOUND_INDEX;
	}


	template<typename C> requires isComponent<C>
	Entity &Entity::add()
	{
		throwIfHasComponent<C>();

		this->m_vComponents.push_back( new C );

		return *this;
	}


	template<typename C> requires isComponent<C>
	Entity &Entity::add( const C &component )
	{
		throwIfHasComponent<C>();

		this->m_vComponents.push_back( new C( component ) );

		return *this;
	}


	template<typename C> requires isComponent<C>
	Entity &Entity::add( C &&component )
	{
		throwIfHasComponent<C>();

		this->m_vComponents.push_back( new C( std::forward<C>( component ) ) );

		return *this;
	}


	template<typename C> requires isComponent<C>
	Entity &Entity::removeComponent()
	{
		const auto index{ getComponentIndex<C>() };

		if( index  != NOT_FOUND_INDEX )
		{
			delete this->m_vComponents[index];
			m_vComponents.erase( m_vComponents.begin() + index );
		}

		return *this;
	}
}
