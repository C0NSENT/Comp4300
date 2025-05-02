//
// Created by consent_ on 23-Mar-25.
//

#include <iostream>
#include <fstream>
#include <regex>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"


//В тхт файле бачит разрешения экрана, если не находит использует стандартное
constexpr sf::Vector2u getScreenResolution(std::ifstream& fs)
{
	sf::Vector2u screenSize{1280, 720};
	if (!fs) {
		std::cerr << "Error reading screen size\n";
		std::cout <<"Using default size: " << std::endl;
	}
	fs >> screenSize.x >> screenSize.y;

	std::cout << "Using config defined resolution: "
		<< screenSize.x << "x" << screenSize.y << std::endl;

	return screenSize;
}

/*
constexpr sf::Font initFont(const std::string& fontName)
{
	sf::Font font;

	if (!font.openFromFile(fontName)) {
		throw std::runtime_error("Failed to load font");
	}

	std::cout << "Loaded font: " << fontName << std::endl;

	return font;
}*/

int main()
{
	std::ifstream fConfig("config.txt");

	if (!fConfig.is_open()) {
		std::cerr << "Error opening config file" << std::endl;
		return 1;
	}

	sf::Vector2u screenSize{getScreenResolution(fConfig)};
	fConfig.close();

	sf::RenderWindow window(sf::VideoMode(screenSize), "Werden Engine");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	float c[3] = {0.0f, 1.0f, 1.0f};

	float circleRadius = 100;
	int circleSegments = 32;

	sf::Vector2f circleSpeed{1.0f, 0.5f};
	bool drawCircle = true;
	bool drawText = true;

	sf::CircleShape circle(circleRadius, circleSegments);
	circle.setPosition({screenSize.x / 2.f, screenSize.y / 2.f});

	const sf::Font font("../../Comp4300/stuff/font.ttf");

	sf::Text text(font);
	text.setString("Text");
	text.setCharacterSize(24);

	char displayString[255] = "Text";

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {

			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
				window.close();
		}

		std::cout << circle.getPosition().x << ", " << circle.getPosition().y << std::endl;


		if (circle.getGlobalBounds().position.x <= 0) {
			circleSpeed.x = -circleSpeed.x;
			std::cerr << "БОРТ";
		} else if (circle.getGlobalBounds().position.x + circleRadius * 2 >= screenSize.x) {
			circleSpeed.x = -circleSpeed.x;
			std::cerr << "БОРТ";
		}

		if (circle.getGlobalBounds().position.y <= 0) {
			circleSpeed.y = -circleSpeed.y;
			std::cerr << "БОРТ";
		} else if (circle.getGlobalBounds().position.y + circleRadius * 2 >= screenSize.y) {
			circleSpeed.y = -circleSpeed.y;
			std::cerr << "БОРТ";
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("MEH Engine");

		if (ImGui::BeginTabBar("MEH Engine")) {
			if (ImGui::BeginTabItem("Shapes")) {
				ImGui::Checkbox("Draw circle", &drawCircle);

				ImGui::SameLine();
				ImGui::Checkbox("Draw text", &drawText);
				ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
				ImGui::SliderInt("Sides", &circleSegments, 3, 64);
				ImGui::ColorEdit3("Display Color", c);
				ImGui::NewLine();
				ImGui::InputText("Text", displayString, 255);if (ImGui::Button("Set Text")) {
					text.setString(displayString);
				}
				ImGui::SameLine();

				if (ImGui::Button("Reset Circle")) {
					circle.setPosition({0.0f, 0.0f});
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Other")) {
				ImGui::CollapsingHeader("Shapes");

				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}

		ImGui::End();

		circle.setPointCount(circleSegments);
		circle.setRadius(circleRadius);

		circle.setFillColor(sf::Color(c[0] *255.0f, c[1] *255.0f, c[2] *255.0f));

		circle.move(circleSpeed);
		//text.setPosition({circle.getGlobalBounds().getCenter() - text.getGlobalBounds().size});
		//std::cout << "getOrigin:" << circle.getOrigin().x << " " << circle.getOrigin().y << std::endl;

		window.clear();

		if (drawCircle) {
			window.draw(circle);
		}
		if (drawText) {
			window.draw(text);
		}
		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}