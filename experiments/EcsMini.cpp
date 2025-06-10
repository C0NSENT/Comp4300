/**
 * @date 10/06/25
 * 
 * @author consent_
 */

#include <vector>
#include <iostream>

struct Component
{
	virtual ~Component() {}
};

struct Derived1 : Component
{
	int i{};
};

struct Derived2 : Component
{
	float i{};
	float j{};
};

struct Derived3 : Component
{
	std::vector<float> vec{};
};

class Entity
{
	public:

	Entity()
	{
		vComponents.push_back( new Derived3 );
		vComponents.push_back( new Derived2 );
		vComponents.push_back( new Derived1 );
	}
	~Entity()
	{
		for ( Component* component : vComponents )
		{
			delete component;
		}
	}



	std::vector<Component *> vComponents;
};

int main() 
{
	Entity e;
	e.~Entity();
}
