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
		std::cerr << "Error reading screen size" << std::endl;
		std::cout <<"Using default size: \n";
	} else
		std::cout << "Using config defined resolution: \n";

	fs >> screenSize.x >> screenSize.y;

	std::cout << screenSize.x << "x" << screenSize.y << std::endl;

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

struct CircleProperties
{
	float radius;
	int points;
	bool is_drawn;

	sf::Vector2f velocity;

	explicit CircleProperties(
		const float radius = 100,
		const int points = 32,
		bool is_drawn = true,
		const sf::Vector2f& velocity = {1.0f, 0.5f}
		)
			: radius(radius)
			, points(points)
			, is_drawn(true)
			, velocity(std::move(velocity)){}
};

void screenBorderCollision(const sf::CircleShape& circle,
	CircleProperties& properties,
	const sf::Vector2u& screenSize)
{
	if (circle.getGlobalBounds().getCenter().x - circle.getRadius() == 0) {
		properties.velocity.x = -properties.velocity.x;
		std::cerr << "БОРТ\n";
	} else if (circle.getGlobalBounds().getCenter().x + circle.getRadius() == screenSize.x) {
		properties.velocity.x = -properties.velocity.x;
		std::cerr << "БОРТ\n";
	}

	if (circle.getGlobalBounds().getCenter().y - circle.getRadius() == 0) {
		properties.velocity.y = -properties.velocity.y;
		std::cerr << "БОРТ\n";
	} else if (circle.getGlobalBounds().getCenter().y + circle.getRadius() == screenSize.y) {
		properties.velocity.y = -properties.velocity.y;
		std::cerr << "БОРТ\n";
	}
}

int main()
{
	std::ifstream fConfig("../Comp4300/stuff/config.txt");

	sf::Vector2u screenSize{getScreenResolution(fConfig)};
	fConfig.close();

	sf::RenderWindow window(sf::VideoMode(screenSize), "Mother, do you think they'll try to break my balls?");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	float c[3] = {0.0f, 1.0f, 1.0f};

	bool drawText = true;

	CircleProperties properties;

	sf::CircleShape circle(properties.radius, properties.points);
	circle.setPosition({screenSize.x / 2.f - properties.radius, screenSize.y / 2.f - properties.radius });

	const sf::Font font("../../../Comp4300/stuff/font.ttf");

	sf::Text text(font);
	text.setString("Text");
	text.setCharacterSize(24);
	sf::Vector2f textCenter = text.getGlobalBounds().getCenter();


	std::cout << circle.getGeometricCenter().x << " " << circle.getGeometricCenter().y << std::endl;

	char displayString[255] = "Text";

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {

			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
				window.close();
		}

		screenBorderCollision(circle, properties, screenSize);

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("MEH Engine");
		if (ImGui::BeginTabBar("MEH Engine")) {
			if (ImGui::BeginTabItem("Shapes")) {
				ImGui::Checkbox("Draw circle", &properties.is_drawn);

				ImGui::SameLine();
				ImGui::Checkbox("Draw text", &drawText);
				ImGui::SliderFloat("Radius", &properties.radius, 0.0f, 300.0f);
				ImGui::SliderInt("Points", &properties.points, 3, 64);
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

		circle.setPointCount(properties.points);
		circle.setRadius(properties.radius);

		circle.setFillColor(sf::Color(c[0] *255.0f, c[1] *255.0f, c[2] *255.0f));


		circle.move(properties.velocity);

		text.setPosition(circle.getGlobalBounds().getCenter() - textCenter);

		std::cout << "getCenter: " << text.getGlobalBounds().getCenter().x << " " << text.getGlobalBounds().getCenter().y << std::endl;

		window.clear();

		if (properties.is_drawn) {
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