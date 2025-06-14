//
// Created by consent_ on 21/05/25.
//

#pragma once


#include "IdManager.hpp"
#include "Entity.tpp"

#include <unordered_map>

namespace lrh
{
	class EntityManager
	{
		using EntityMap = std::unordered_map<Id, Entity>;

		Entity findEverywhere( int16_t id ) const;
		Entity &findEveryWhereMutable( int16_t id );

	public:

		EntityManager() = default;

		EntityManager &update();
		EntityManager &emplace( Entity &&entity );
		EntityManager &eraseAllInactiveEntities();
		EntityManager &addEntity( Entity &&entity );
		EntityManager &removeEntity(int16_t id);

		[[nodiscard]] Entity getEntity(int16_t id) const;
		[[nodiscard]] Entity &getEntityMutable(int16_t id);

		EntityManager(const EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&&) = delete;

	private:

		EntityMap m_entitiesToAdd;
		EntityMap m_entities;
	};
}