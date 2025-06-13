//
// Created by consent_ on 21/05/25.
//

#include "EntityManager.hpp"

#include <algorithm>

namespace lrh
{
	Entity &EntityManager::findEverywhere( const int16_t id )
	{
		if (m_entities.contains(id))
			return m_entities.at(id);

		if (m_updateBuffer.contains(id))
			return m_updateBuffer.at(id);

		throw std::out_of_range("There is no such entity");
	}


	EntityManager & EntityManager::update()
	{

	}


	EntityManager &EntityManager::emplace( Entity &entity )
	{

		///Не забыть про перемещение таких сущностей иначе id потеряется
		m_updateBuffer.emplace( Id{}, entity );
		return (*this);
	}


	EntityManager & EntityManager::removeDeadEntities()
	{
	}


	EntityManager & EntityManager::removeEntity( const int16_t id )
	{

	}


	Entity EntityManager::getEntity( int16_t id ) const
	{

	}


	Entity & EntityManager::getEntityMutable( int16_t id )
	{
	}


	/*EntityManager::UpdateBuffer &EntityManager::UpdateBuffer::instance()
	{
		static EntityManager self{}; //SELF, тутуту тутуту

		return *this;
	}*/


	/*void EntityManager::UpdateBuffer::clear()
	{
		m_updateBuffer.clear();
	}


	EntityManager::UpdateBuffer::EntityMap &EntityManager::UpdateBuffer::getData()
	{
		return m_updateBuffer;
	}


	bool EntityManager::UpdateBuffer::hasEntity( const Id &id ) const
	{
		return m_updateBuffer.contains( id.id() );
	}


	EntityManager::UpdateBuffer &EntityManager::UpdateBuffer::addEntity(const Id &id, const Entity &entity )
	{
		const bool wasInserted{ m_updateBuffer.try_emplace( id.id(), entity ).second };

		if (not wasInserted)
			throw std::out_of_range("There is no such entity");

		return *this;
	}


	EntityManager::UpdateBuffer &EntityManager::UpdateBuffer::removeEntity( const Id &id )
	{
		m_updateBuffer.erase( id.id() );

		return *this;
	}


	Entity EntityManager::UpdateBuffer::getEntity( const Id &id ) const
	{
	}


	Entity &EntityManager::UpdateBuffer::getEntityMutable( const Id &id )
	{
		return m_updateBuffer[id.id()];
	}*/
}

