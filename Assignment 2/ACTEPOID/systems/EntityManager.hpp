//
// Created by consent_ on 21/05/25.
//

#pragma once

#include "Entity.tpp"

#include<unordered_map>
namespace lrh
{
	class EntityManager
	{
		EntityManager();
	public:




	private:

		constexpr static auto INVALID{ -1 };

		std::unordered_map<int32_t, Entity> m_umEntities;
	};
}