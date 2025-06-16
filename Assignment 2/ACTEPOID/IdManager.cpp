/**
 * @date 11/06/25
 * 
 * @author consent_
 */

#include "IdManager.hpp"

#include <stdexcept>

namespace lrh
{
	Id::Id() : m_id{ IdManager::instance().getNewId() }
	{
		if (this->m_id == INVALID)
			throw std::logic_error("IdManager::Id() cannot be created, all IDs is in use");
	}


	Id::Id( const int16_t id ) noexcept
		: m_id{ id }
	{
		IdManager::instance().addCopy( id );
	}


	Id::Id( const Id &id ) noexcept
		: m_id{ id.m_id }
	{
		IdManager::instance().addCopy( id.m_id );
	}


	Id::~Id()
	{
			IdManager::instance().freeId(this->m_id);
	}


	int16_t Id::id() const noexcept
	{
		return this->m_id;
	}


	Id &Id::operator=( const Id &rhs )
	{
		if (this->m_id != rhs.m_id)
		{
			this->m_id = rhs.m_id;
			IdManager::instance().addCopy( m_id );
		}

		return *this;
	}


	Id::IdManager &Id::IdManager::instance()
	{
		static IdManager self;
		return self;
	}


	int16_t Id::IdManager::getNewId()
	{
		for ( auto id {0}; id != m_idCopyCount.size(); ++id )
		{
			if ( m_idCopyCount[id] == 0 )
			{
				m_idCopyCount[id] = 1;
				return id;
			}
		}

		if (m_idCopyCount.size() != SIZE)
		{
			m_idCopyCount.push_back(1);
			return m_idCopyCount.size()-1;
		}

		return INVALID;
	}


	void Id::IdManager::addCopy(const int16_t id) noexcept
	{
		m_idCopyCount[id]++;
	}


	void Id::IdManager::freeId( const int16_t id ) noexcept
	{
		m_idCopyCount[id]--;
	}


	auto Id::IdManager::usedIdFlags() const noexcept -> const std::deque<uint8_t> &
	{
		return m_idCopyCount;
	}
}


size_t std::hash<lrh::Id>::operator()( const lrh::Id &id ) const noexcept
{
	return std::hash<int16_t>{}( id.id() );
}
