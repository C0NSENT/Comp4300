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
		Entity &findEverywhere(int16_t id);

	public:


		EntityManager() = default;

		EntityManager &update();
		EntityManager &emplace( Entity &entity );
		EntityManager &removeDeadEntities();
		EntityManager &removeEntity(int16_t id);

		[[nodiscard]] Entity getEntity(int16_t id) const;
		[[nodiscard]] Entity &getEntityMutable(int16_t id);

		EntityManager(const EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&&) = delete;

	private:

		std::unordered_map<Id, Entity> m_updateBuffer;
		std::unordered_map<Id, Entity> m_entities;
	};


	/*class EntityManager::UpdateBuffer
	{
		UpdateBuffer() = default;

		using EntityMap = std::unordered_map<int16_t, Entity>;
	public:

		void clear();

		[[nodiscard]] EntityMap &getData();


		bool hasEntity(const Id& id) const;
		UpdateBuffer &addEntity( const Id& id, const Entity &entity );
		UpdateBuffer &removeEntity( const Id &id );

		[[nodiscard]] Entity getEntity(const Id& id) const;
		[[nodiscard]] Entity &getEntityMutable( const Id &id );


	private:

		EntityMap m_updateBuffer{};
	};*/
}