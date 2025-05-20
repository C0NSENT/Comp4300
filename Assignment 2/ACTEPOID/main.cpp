//
// Created by consent_ on 20/05/25.
//

#include "Vector2.tpp"

#include <iostream>

int main()
{
	lrh::Vector2f oleg{3, 3};
	lrh::Vector2 mongol{1, 2};
	lrh::Vector2 copy{oleg};
	lrh::Vector2 foo{oleg + copy};
	oleg += 229;
	mongol = mongol + 3;
	-oleg;
	std::cout << oleg.x << " " << oleg.y << std::endl;
	std::cout << mongol.x << " " << mongol.y << std::endl;
	std::cout <<  copy.x << " " << copy.y << std::endl;
	std::cout <<  foo.x << " " << foo.y << std::endl;
}