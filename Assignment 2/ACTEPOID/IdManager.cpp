/**
 * @date 11/06/25
 * 
 * @author consent_
 */

#include "IdManager.hpp"

#include <stdexcept>

namespace lrh
{
	Id::Id() : m_isTemp{ false }, m_id{ IdManager::instance().id() }
	{
		if (this->m_id == INVALID)
			throw std::logic_error("IdManager::Id() cannot be created, all IDs is in use");
	}


	Id::~Id()
	{
		if (not m_isTemp)
			IdManager::instance().freeId(this->m_id);
	}


	int16_t Id::id() const noexcept
	{
		return this->m_id;
	}


	bool Id::isTemporary() const noexcept
	{
		return this->m_isTemp;
	}


	auto Id::usedIdFlags() noexcept -> const std::vector<bool> &
	{
		return IdManager::instance().usedIdFlags();
	}


	Id &Id::operator=( Id &rhs )
	{
		if (this->m_id != rhs.m_id)
		{
			this->m_id = rhs.m_id;
			this->m_isTemp = rhs.m_isTemp;

			rhs.m_isTemp = true;
		}

		return *this;
	}


	Id::Id( const int16_t id ) noexcept
		: m_isTemp{ true }, m_id{ id } {}


	Id::Id( Id &id ) noexcept
		: m_isTemp{ id.m_isTemp }, m_id{ id.m_id }
	{
		id.m_isTemp = true;
	}

	Id::IdManager &Id::IdManager::instance()
	{
		static IdManager self;
		return self;
	}


	int16_t Id::IdManager::id()
	{
		auto findVacantId  = [&] (const int16_t begin, const int16_t end) -> int16_t
		{
			for (auto id = begin; id != end; ++id)
			{
				auto isInUse{ m_usedIdFlags[id] };

				if (not isInUse )
				{
					isInUse.flip();
					m_lastUsedId = id;
					return id;
				}
			}
			return INVALID;
		};


		if (++m_lastUsedId != SIZE)
		{
			const auto id{ findVacantId(m_lastUsedId, SIZE) };

			if ( id != INVALID ) return id;
		}

		return findVacantId( 0,m_lastUsedId );
	}

	void Id::IdManager::freeId( const int16_t id )
	{
		m_usedIdFlags[id] = false;
	}


	auto Id::IdManager::usedIdFlags() const noexcept -> const std::vector<bool> &
	{
		return m_usedIdFlags;
	}


	Id::IdManager::IdManager()
		: m_lastUsedId{ INVALID } , m_usedIdFlags(SIZE, false)
	{
	}
}


std::size_t std::hash<lrh::Id>::operator()( const lrh::Id&id ) const noexcept
{
	return std::hash<int16_t>{}( id.id() );
}
