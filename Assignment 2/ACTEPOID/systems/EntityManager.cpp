//
// Created by consent_ on 21/05/25.
//

#include "EntityManager.hpp"

namespace lrh
{
	EntityManager::UpdateBuffer & lrh::EntityManager::UpdateBuffer::instance()
	{
		static EntityManager self{};

		return *this;
	}


	void EntityManager::UpdateBuffer::clear()
	{
		m_updateBuffer.clear();
	}


	EntityManager::UpdateBuffer::EntityMap & lrh::EntityManager::UpdateBuffer::getData()
	{
		return m_updateBuffer;
	}


	bool EntityManager::UpdateBuffer::hasEntity( const Id &id ) const
	{
		return m_updateBuffer.contains( id.id() );
	}


	EntityManager::UpdateBuffer &EntityManager::UpdateBuffer::addEntity(const Id &id, const Entity &entity )
	{
		m_updateBuffer.insert_or_assign(id.id(), entity);

		return *this;
	}


	EntityManager::UpdateBuffer &EntityManager::UpdateBuffer::removeEntity( const Id &id )
	{
		m_updateBuffer.erase( id.id() );

		return *this;
	}


	Entity &EntityManager::UpdateBuffer::getEntityMutable( const Id &id )
	{
		return m_updateBuffer[id.id()];
	}
}

