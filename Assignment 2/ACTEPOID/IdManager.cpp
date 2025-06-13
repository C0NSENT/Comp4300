/**
 * @date 11/06/25
 * 
 * @author consent_
 */

#include "IdManager.hpp"

namespace lrh
{
	Id::Id() : m_isTemp{ false }, m_id{ IdManager::instance().id() } {}


	Id::~Id()
	{
		if (not m_isTemp)
			IdManager::instance().freeId(this->m_id);
	}


	int16_t Id::id() const
	{
		return this->m_id;
	}


	constexpr Id::Id( int16_t temporaryId )
		: m_isTemp{ true }, m_id{ temporaryId } {}


	constexpr int16_t Id::maxId()
	{
		return IdManager::SIZE;
	}


	constexpr int16_t Id::invalidId()
	{
		return IdManager::INVALID;
	}

	Id::IdManager &Id::IdManager::instance()
	{
		static IdManager self;
		return self;
	}


	int16_t Id::IdManager::id()
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


	void Id::IdManager::freeId( const int16_t id )
	{
		m_ids[id] = false;
	}
}


std::size_t std::hash<lrh::Id>::operator()( const lrh::Id &id ) const noexcept
{
	return std::hash<int16_t>{}( id.id());
}
