/**
 * @date 11/06/25
 * 
 * @author consent_
 */

#include "IdManager.hpp"

namespace lrh
{
	constexpr Id::Id() : m_id(IdManager::instance().id()) {}


	constexpr int16_t IdManager::id()
	{
		for (auto id{ 0 }; id < SIZE; ++id)
		{
			if ( bool &occupied{ m_ids[id] }; not occupied)
			{
				occupied = true;
				return id;
			}
		}
		return INVALID;
	}


	constexpr void IdManager::freeId( const int16_t id )
	{
		m_ids[id] = false;
	}


	Id::~Id()
	{
		IdManager::instance().freeId(this->m_id);
	}


	constexpr IdManager &IdManager::instance()
	{
		static IdManager self;
		return self;
	}
}



