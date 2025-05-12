//
// Created by consent_ on 07/05/25.
//

#include "circlewithtext.h"

#include <iostream>
#include <string>
#include <array>

#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
	constexpr sf::Vector2u screenSize{1280, 720};
	constexpr std::string windowTitle{"Podnimayemsya s Kolen"};
	sf::RenderWindow window(sf::VideoMode(screenSize), windowTitle);
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(1.5f);
	ImGui::GetIO().FontGlobalScale = {1.5f};

	float c
}