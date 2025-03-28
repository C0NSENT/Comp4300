//
// Created by consent_ on 28-Mar-25.
//

#include <iostream>
#include <stdexcept>
#include <filesystem>

#include <SFML/Graphics.hpp>

int main()
{
	constexpr auto screenSize = sf::Vector2u(1280, 720);
	sf::RenderWindow window(sf::VideoMode(screenSize), "Text Centering");
	window.setFramerateLimit(60);

	std::cout<< std::filesystem::current_path().string() << std::endl;

	sf::Font font("../Comp4300/stuff/font.ttf");


}