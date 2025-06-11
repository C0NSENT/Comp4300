//
// Created by consent_ on 21/05/25.
//

#pragma once

#include "Entity.tpp"

#include <unordered_map>


//TODO: Победить этот ебучий хеш-тейбл и реализовать нормальный класс айди

namespace lrh
{
	class Id
	{
		public:


	};

	class EntityManager
	{
	public:

		static EntityManager &Instance();

		constexpr EntityManager &update();
		constexpr EntityManager &addEntity(const Entity &&entity);
		constexpr EntityManager &removeDeadEntities();
		constexpr EntityManager &removeEntity(int32_t id);

		[[nodiscard]] constexpr Entity getEntity(int32_t id) const;
		[[nodiscard]] constexpr Entity &getEntityMutable(int32_t id);

		EntityManager(const EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&&) = delete;

	private:

		constexpr  EntityManager() = default;


		constexpr static int32_t INVALID{ -1 };



		std::vector<int32_t> m_availableIds{};

		int32_t m_currentId{};

		size_t m_pendingEntitiesCount{};
		std::vector<std::pair<int32_t, Entity>> m_pendingEntities{};

		std::unordered_map<int32_t, Entity> m_entities;
	};
}