/**
 * @date 11/06/25
 * 
 * @author consent_
 */

#include "IdManager.hpp"

namespace lrh
{
	constexpr Id::IdManager &Id::IdManager::instance()
	{
		static IdManager self;
		return self;
	}


	constexpr int16_t Id::IdManager::id()
	{
		for (int16_t id{ 0 }; id < SIZE; ++id)
		{
			if ( bool &occupied{ m_ids[id] }; not occupied )
			{
				occupied = true;
				return id;
			}
		}
		return INVALID;
	}


	constexpr void Id::IdManager::freeId( const int16_t id )
	{
		m_ids[id] = false;
	}


	constexpr Id::Id() : m_id{ IdManager::instance().id() } {}


	Id::~Id()
	{
		IdManager::instance().freeId(this->m_id);
	}


	int16_t Id::id() const
	{
		return this->m_id;
	}


	constexpr int16_t Id::maxId()
	{
		return IdManager::SIZE;
	}


	constexpr int16_t Id::invalidId()
	{
		return IdManager::INVALID;
	}
}


std::size_t std::hash<lrh::Id>::operator()( const lrh::Id &id ) const noexcept
{
	return std::hash<int16_t>{}( id.id());
}
