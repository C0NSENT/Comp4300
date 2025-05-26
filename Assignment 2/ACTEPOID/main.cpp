//
// Created by consent_ on 20/05/25.
//

#include "Vector2.tpp"
#include <Logger.hpp>
#include <iostream>
#include <unistd.h>

void Vector2Test()
{
	lrh::Vector2f oleg{3, 3};
	lrh::Vector2f mongol{1, 2};
	lrh::Vector2 copy{oleg};
	lrh::Vector2 foo{oleg + copy};
	oleg += 229;
	mongol = mongol + 3;
	-oleg;
	oleg.distance(mongol);
	std::cout << oleg.x << " " << oleg.y << std::endl;
	std::cout << mongol.x << " " << mongol.y << std::endl;
	std::cout <<  copy.x << " " << copy.y << std::endl;
	std::cout <<  foo.x << " " << foo.y << std::endl;
}

void loggerTest() {
	lrh::Logger::instance().write("aboba", lrh::Level::Info);
	lrh::Logger::instance().write("Ахуй", lrh::Level::Info);
	lrh::Logger::instance().write("<UNK>", lrh::Level::Fatal);
	lrh::Logger::instance().write("<UNK>", lrh::Level::Error);
	lrh::Logger::instance().write("<UNK>", lrh::Level::Debug);
}



int main()
{
	//std::fstream("test.log", std::ios::trunc);
	// loggerTest();
	// sleep(2);
	//loggerTest();

	//TODO: Почему-то не выводит в реалтайме
	while (true) {
		lrh::Logger::instance().write("aboba");
		sleep(1);
	}
	Vector2Test();

}