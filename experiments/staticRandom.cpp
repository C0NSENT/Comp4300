//
// Created by consent_ on 13/05/25.
//

#include <random>
#include <iostream>

auto foo()
{
	static std::random_device rd;
	std::mt19937 gen(rd());
	return gen;
}

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 255);
	for (auto i = 0; i < 10; ++i) {
		std::cout << distrib(gen) << '\n';
	}
}