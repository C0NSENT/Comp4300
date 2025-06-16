//
// Created by consent_ on 21/05/25.
//

#include "EntityManager.hpp"

#include <algorithm>
#include <stdexcept>

namespace lrh
{
	const Entity &EntityManager::findEntity( const int16_t id ) const
	{
		const Id key{ id };

		if (m_entities.contains(key))
			return m_entities.at(key);

		if (m_entitiesToAdd.contains(key))
			return m_entitiesToAdd.at(key);

		throw std::out_of_range("There is no such entity");
	}

	Entity & EntityManager::findEntityMutable( const int16_t id )
	{
		const Id key{ id };

		if (m_entities.contains(key))
			return m_entities.at(key);

		if (m_entitiesToAdd.contains(key))
			return m_entitiesToAdd.at(key);

		throw std::out_of_range("There is no such entity");
	}


	size_t EntityManager::size() const
	{
		return m_entities.size() + m_entitiesToAdd.size();
	}


	EntityManager &EntityManager::update()
	{
		eraseAllInactiveEntities();

		m_entities.insert(m_entitiesToAdd.begin(), m_entitiesToAdd.end());

		return *this;
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


	bool EntityManager::hasEntity( const int16_t id ) const
	{
		const Id key{ id };

		return m_entities.contains( key ) or m_entitiesToAdd.contains( key );
	}


	auto EntityManager::getAllEntities() const -> std::pair<const EntityMap &, const EntityMap &>
	{
		const EntityMap& refEntities{ m_entities };
		const EntityMap& refEntitiesToAdd{ m_entitiesToAdd };

		return std::pair{ refEntities, refEntitiesToAdd };
	}


	Entity EntityManager::getEntity( const int16_t id ) const
	{
		return findEntity( id );
	}


	Entity &EntityManager::getEntityMutable( const int16_t id )
	{
		return findEntityMutable( id );
	}

}

