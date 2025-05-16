//
// Created by consent_ on 16/05/25.
//


#include <iostream>
#include <vector>

int main()
{
	int a{1};
	int& b = a;
	std::cout << sizeof(std::cout) << std::endl;

	std::cout << sizeof(true) << std::endl;
	std::cout << sizeof(char) << std::endl;
	std::cout << sizeof(int) << std::endl;
	std::cout << sizeof(int*) << std::endl;
	std::cout << sizeof(std::size_t) << std::endl;
	std::cout << sizeof(b) << std::endl;
	std::cout << sizeof("abc") << std::endl;
	std::cout << sizeof(float) << std::endl;
	std::cout << sizeof(std::vector<int*>{});
}