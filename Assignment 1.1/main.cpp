//
// Created by consent_ on 07/05/25.
//

#include "circlewithtext.h"


#include <string>
#include <random>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

//Наконец этого урода превратил во что-то адекватное
void screenBorderCollisionHandler(
	float circlePos,
	float circleRadius,
	float& velocity,
	unsigned int screenBorder
)
{
	if (circlePos - circleRadius <= 0.f) {
		velocity *= -1;
	} else if (circlePos + circleRadius >= screenBorder) {
		velocity *= -1;
	}
}

void screenBorderCollisionHandler(
	circleWithText& circleWithText,
	const sf::Vector2u& screenSize
)
{
	//Почему я сразу до этого не догадался и код менее громоздким кажется
	//Да и геттеры по двести раз не вызываются
	const sf::Vector2f circleCenter{circleWithText.circle.getGlobalBounds().getCenter()};
	const float circleRadius = circleWithText.circle.getRadius();

	if (circleCenter.x - circleRadius == 0) {
		circleWithText.velocity.x *= -1;
	} else if (circleCenter.x + circleRadius ==  screenSize.x) {
		circleWithText.velocity.x *= -1;
	}

	if (circleCenter.y - circleRadius == 0) {
		circleWithText.velocity.x *= -1;
	} else if (circleCenter.y + circleRadius ==  screenSize.y) {
		circleWithText.velocity.x *= -1;
	}
}

int main()
{

	constexpr sf::Vector2u screenSize{1280, 720};
	constexpr std::string windowTitle{"Podnimayemsya s Kolen"};
	sf::RenderWindow window(sf::VideoMode(screenSize), windowTitle);
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(1.5f);
	ImGui::GetIO().FontGlobalScale(1.5f);

	std::array ImGuiCgolor{0.0f, 1.0f, 0.0f, 1.0f};

	sf::Font font{"../../../Comp4300/stuff/font.ttf"};

	circleWithText shape{font, "Aboba"};

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event -> is<sf::Event::Closed>())
				window.close();
		}

		screenBorderCollisionHandler(
			shape.circle.getGlobalBounds().getCenter().x,
			shape.circle.getRadius(),
			shape.velocity.x,
			screenSize.x
		);

		screenBorderCollisionHandler(
			shape.circle.getGlobalBounds().getCenter().y,
			shape.circle.getRadius(),
			shape.velocity.y,
			screenSize.y
		);

		ImGui::SFML::Update(window, deltaClock.restart());


		ImGui::Begin("Settings");
		if (ImGui::BeginTabBar("Shape Settings")) {

			if (ImGui::BeginTabItem("Shape")) {
				ImGui::Checkbox("Draw circle", &shape.isCircleDrawn);
				ImGui::SameLine();
				ImGui::Checkbox("Draw text", &shape.isTextDrawn);

				//shape.circle.setRadius(ImGui::SliderFloat("Radius"))
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();

		shape.circle.move(velocity);
	}
}