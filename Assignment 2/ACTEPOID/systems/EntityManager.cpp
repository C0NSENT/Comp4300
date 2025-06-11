//
// Created by consent_ on 21/05/25.
//

#include "EntityManager.hpp"


lrh::EntityManager &lrh::EntityManager::Instance()
{
	static EntityManager self; //Steven Wilson reference?!
	return self;
}


lrh::EntityManager &lrh::EntityManager::update()
{
	/*m_pendingEntities.clear();
	m_pendingEntitiesСount = 0;*/
	this->removeDeadEntities();
	return *this;
}


lrh::EntityManager &lrh::EntityManager::addEntity( const Entity &entity )
{

	return *this;
}


lrh::EntityManager &lrh::EntityManager::removeDeadEntities()
{

}


lrh::EntityManager &lrh::EntityManager::removeEntity(const  int32_t id )
{
	m_availableIds.push_back( id );
	return *this;
}


lrh::Entity lrh::EntityManager::getEntity( int32_t id ) const
{
}


lrh::Entity &lrh::EntityManager::getEntityMutable( int32_t id )
{
}
