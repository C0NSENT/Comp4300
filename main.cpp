//
// Created by consent_ on 23-Mar-25.
//

#include <iostream>
#include <memory>
#include <fstream>
#include <regex>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

void InitScreenSize(std::ifstream& fs, sf::Vector2u& screenSize)
{
	fs>> screenSize.x >> screenSize.y;
}



int main()
{
	std::ifstream fConfig("config.txt");

	if (!fConfig.is_open()) {
		std::cerr << "Error opening config file" << std::endl;
		return 1;
	}


	sf::Vector2u screenSize;

	InitScreenSize(fConfig, screenSize);

	fConfig.close();

	sf::RenderWindow window(sf::VideoMode(screenSize), "MEH Engine");
	window.setFramerateLimit(60);

	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	float c[3] = {0.0f, 1.0f, 1.0f};

	float circleRadius = 100;
	int circleSegments = 32;
	float circlespeedX = 1.0f;
	float circlespeedY = 0.5f;
	bool drawCircle = true;
	bool drawText = true;

	sf::CircleShape circle(circleRadius, circleSegments);
	circle.setPosition({10.0f, 10.0f});

	sf::Font font;

	if (!font.openFromFile(R"(D:\Open this folder only if you are listening Skinny Puppy rn\C++\MEH Engine\stuff\font.ttf)")) {
		std::cerr << "Failed to load font" << std::endl;
		return -1;
	}

	sf::Text text(font);
	text.setString("Text");
	text.setCharacterSize(24);

	//text.setPosition({0, wHeight - static_cast<float> (text.getCharacterSize())});

	char displayString[255] = "Text";

	while (window.isOpen()) {

		while (const std::optional event = window.pollEvent()) {

			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
				circlespeedX *= -1.0f;
			}
		}

		std::vector <sf::Vector2u> points {{1920, 1080}, {1366, 768}};

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

		circle.setPosition({circle.getPosition().x + circlespeedX, circle.getPosition().y + circlespeedY});
		text.setPosition({circle.getLocalBounds().getCenter().x , circle.getLocalBounds().getCenter().y});

		std::cout << "\nCicle Radius: " << circleRadius
					<< "\ngetRadius(): " << circle.getRadius();

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