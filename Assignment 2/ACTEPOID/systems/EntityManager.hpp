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
		class UpdateBuffer;

	public:
		constexpr  EntityManager() = default;

		constexpr EntityManager &update();
		constexpr EntityManager &addEntity(const Entity &entity);
		constexpr EntityManager &removeDeadEntities();
		constexpr EntityManager &removeEntity(int32_t id);

		[[nodiscard]] constexpr Entity getEntity(int32_t id) const;
		[[nodiscard]] constexpr Entity &getEntityMutable(int32_t id);

		EntityManager(const EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&&) = delete;

	private:

		std::unordered_map<Id, Entity> m_entities;
	};

	class EntityManager::UpdateBuffer
	{
		using EntityMap = std::unordered_map<int16_t, Entity>;
	public:

		UpdateBuffer &instance();
		void clear();

		[[nodiscard]] EntityMap &getData();


		bool hasEntity(const Id& id) const;
		UpdateBuffer &addEntity( const Id& id, const Entity &entity );
		UpdateBuffer &removeEntity( const Id &id );

		[[nodiscard]] Entity &getEntityMutable( const Id &id );



	private:

		UpdateBuffer() = default;

		EntityMap m_updateBuffer{};
	};
}