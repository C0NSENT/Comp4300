//
// Created by consent_ on 21/05/25.
//

#pragma once

#include "Entity.tpp"
#include "IdManager.hpp"

#include <unordered_map>

namespace lrh
{
	class EntityManager
	{
		using EntityMap = std::unordered_map<Id, Entity>;

		const Entity &findEntity( int16_t id ) const;
		Entity &findEntityMutable( int16_t id );

	public:

		EntityManager() = default;

		size_t size() const;

		EntityManager &update();
		EntityManager &eraseAllInactiveEntities();
		EntityManager &addEntity( Entity &&entity );

		bool hasEntity( int16_t id ) const;

		///Используй structured binding чтобы взаимодействовать с данными
		auto getAllEntities() const -> std::pair<const EntityMap&, const EntityMap&>;

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