//
// Created by consent_ on 07/05/25.
//

#include "CircleWithText.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include <misc/cpp/imgui_stdlib.h> //Враппер для плюсов, чтобы с сишным калом не возиться

#include<iostream>
#include <random>
#include <list>
#include <algorithm>

//TODO: синглттон логгер

template<typename T>
void outputSfVector(const std::string& label, const sf::Vector2<T> & vector)
{
	std::cout << label << ": " << vector.x << ", " << vector.y << std::endl;
}

void outputSfVector(const std::string& label, const sf::FloatRect& vector)
{
	std::cout << label << ": " << vector.position.x << ", " << vector.position.y << std::endl;
}

void textDebug(const sf::Text& text)
{
	outputSfVector("getPosition", text.getPosition());
	outputSfVector("getGlobalBounds", text.getGlobalBounds());
	outputSfVector("getLocalBounds", text.getLocalBounds());
	outputSfVector("getCenter", text.getGlobalBounds().getCenter());
	outputSfVector("getLocalCenter", text.getLocalBounds().getCenter());
}

int main()
{
	constexpr sf::Vector2u screenSize{1280, 720};
	const std::string windowTitle{"Podnimayemsya s Kolen"};
	sf::RenderWindow window(sf::VideoMode(screenSize), windowTitle);
	window.setFramerateLimit(120);
	static_cast<void>(ImGui::SFML::Init(window));

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;


	const sf::Font font{"../../../Comp4300/stuff/font.ttf"};

	std::list<CircleWithText> ShapesList;

	CircleWithText shape{font, "Aboba"};
	shape.setPosition({screenSize.x /2.f, screenSize.y / 2.f});
	shape.setCircleFillColor(sf::Color{128, 32, 94});

	float radius{};
	int points{};
	std::array<float, 3> ImGuiColor{};
	sf::Vector2f velocity;
	std::string textContent;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event -> is<sf::Event::Closed>())
				window.close();
		}

		shape.processScreenCollision(screenSize);

		ImGui::SFML::Update(window, deltaClock.restart());

		radius = shape.getRadius();
		points = static_cast<int>(shape.getPointCount());
		ImGuiColor = shape.getImGuiFillColor();
		velocity = shape.getVelocity();
		textContent = shape.text.getString();

		ImGui::Begin("Settings");
		if (ImGui::BeginTabBar("Shape Settings"))
		{
			if (ImGui::BeginTabItem("Shape"))
			{
				ImGui::Checkbox("Draw circle", &shape.isCircleDrawn);
				ImGui::SameLine();
				ImGui::Checkbox("Draw text", &shape.isTextDrawn);
				ImGui::SliderFloat("Radius", &radius, 0.0f, 200.0f);
				ImGui::SliderInt("Points", &points, 3, 64);
				//std::cout << ImGuiColor[0] << " " << ImGuiColor[1] <<  " " << ImGuiColor[2] << std::endl;
				ImGui::ColorEdit3("Display Color", ImGuiColor.data());
				//TODO: Сделать враппер над velocity чтобы скорость отображалась без минуса
				//Да можно передавать классы и стуктуры
				ImGui::SliderFloat2("Velocity", &velocity.x, -10.f, 10.f);
				ImGui::InputText("Text", &textContent);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();

		shape.setRadius(radius);
		shape.setPointCount(points);
		shape.move();
		shape.setCircleFillColor(ImGuiColor);
		shape.setVelocity(velocity);
		shape.text.setString(textContent);

		window.clear();

		shape.draw(window);

		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}