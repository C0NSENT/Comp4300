//
// Created by consent_ on 21/05/25.
//

#include "EntityManager.hpp"

#include <algorithm>
#include <stdexcept>

namespace lrh
{
	Entity EntityManager::findEverywhere( const int16_t id ) const
	{
		const Id temp{ id };

		if (m_entities.contains(temp))
			return m_entities.at(temp);

		if (m_entitiesToAdd.contains(temp))
			return m_entitiesToAdd.at(temp);

		throw std::out_of_range("There is no such entity");
	}

	Entity & EntityManager::findEveryWhereMutable( const int16_t id )
	{
		const Id temp{ id };

		if (m_entities.contains(temp))
			return m_entities.at(temp);

		if (m_entitiesToAdd.contains(temp))
			return m_entitiesToAdd.at(temp);

		throw std::out_of_range("There is no such entity");
	}



	EntityManager &EntityManager::update()
	{
		eraseAllInactiveEntities();

		m_entities.merge( m_entitiesToAdd );

		m_entitiesToAdd.clear();

		return *this;
	}


	EntityManager &EntityManager::emplace( Entity &&entity )
	{
		m_entitiesToAdd.emplace( Id{}, std::move( entity ) );
		return (*this);
	}


	EntityManager & EntityManager::eraseAllInactiveEntities()
	{
		auto eraseInactiveEntitiesInMap = []( EntityMap& entities)
		{
			for (auto it = entities.begin(); it != entities.end();)
			{
				if (not it->second.isActive) entities.erase(it);

				else ++it;
			}
		};

		eraseInactiveEntitiesInMap( m_entities );
		eraseInactiveEntitiesInMap( m_entitiesToAdd );

		return (*this);
	}


	EntityManager &EntityManager::addEntity( Entity &&entity )
	{
		m_entitiesToAdd.emplace( Id{}, std::move( entity ) );

		return *this;
	};


	EntityManager & EntityManager::removeEntity( const int16_t id )
	{
		const Id temp{ id };

		findEveryWhereMutable( id ).isActive = false;

		return *this;
	}


	Entity EntityManager::getEntity( const int16_t id ) const
	{
		return findEverywhere( id );
	}


	Entity &EntityManager::getEntityMutable( const int16_t id )
	{
		return findEveryWhereMutable( id );
	}

}

