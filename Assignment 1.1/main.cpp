//
// Created by consent_ on 07/05/25.
//

#include "CircleWithText.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include <misc/cpp/imgui_stdlib.h> //Враппер для плюсов, чтобы с сишным калом не возиться

#include<iostream>
#include <vector>

#include <random>
#include <memory>
//TODO: синглттон логгер

int randomInt(std::mt19937& generator, int min, int max) {
	std::uniform_int_distribution distribution(min, max);
	return distribution(generator);
}

float randomFloat(std::mt19937& generator, float min, float max) {
	std::uniform_real_distribution distribution(min, max);
	return distribution(generator);
}

void initRandomCircle(const sf::Font& font, const std::string& text, cwt::CircleWithText& circle, std::mt19937& generator, const sf::Vector2u& screenSize)
{
	circle.setCircleFillColor( sf::Color{
		static_cast<std::uint8_t>(randomInt(generator, 0, 255)),
		static_cast<std::uint8_t>(randomInt(generator, 0, 255)),
				static_cast<std::uint8_t>(randomInt(generator, 0, 255)),
}
	);
	circle.setRadius(randomFloat(generator, 10.f, 100.f));
	circle.setPointCount(randomInt(generator, 3, 64));
	circle.setPosition({randomFloat(generator, 0.f, screenSize.x), randomFloat(generator, 0.f, screenSize.y)});
	circle.setVelocity(sf::Vector2f{randomFloat(generator, -5.f, 5.f), randomFloat(generator, -5.f, 5.f)});
	circle.setString(text);
}

template<typename T>
void outputSfVector(const std::string& label, const sf::Vector2<T> & vector) {
	std::cout << label << ": " << vector.x << ", " << vector.y << std::endl;
}

void outputSfVector(const std::string& label, const sf::FloatRect& vector) {
	std::cout << label << ": " << vector.position.x
		<< ", " << vector.position.y << std::endl;
}


/*
void textDebug(const sf::Text& textString)
{
	outputSfVector("getPosition", textString.getPosition());
	outputSfVector("getGlobalBounds", textString.getGlobalBounds());
	outputSfVector("getLocalBounds", textString.getLocalBounds());
	outputSfVector("getCenter", textString.getGlobalBounds().getCenter());
	outputSfVector("getLocalCenter", textString.getLocalBounds().getCenter());
}
*/

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

	std::random_device seed;
	std::mt19937_64 generator(seed());
	
	const sf::Font font{"../../../Comp4300/stuff/font.ttf"};

	std::list<cwt::CircleWithText> lsCircles;
	lsCircles.push_back(cwt::CircleWithText(generator, font, std::string{"Aboba"}, screenSize));
	lsCircles.push_back(cwt::CircleWithText(generator, font, std::string{"Armen"}, screenSize));
	lsCircles.push_back(cwt::CircleWithText(generator, font, std::string{"Van"}, screenSize));

	//cwt::CircleWithText VladimirPutinMolodets{font, "Aboba"};
	/*VladimirPutinMolodets.setPosition({screenSize.x /2.f, screenSize.y / 2.f});
	VladimirPutinMolodets.setCircleFillColor(sf::Color{128, 32, 94});

	lsCircles.push_back(VladimirPutinMolodets);
	VladimirPutinMolodets.setString("Armen");
	lsCircles.push_back(VladimirPutinMolodets);
	VladimirPutinMolodets.setString("Van");
	lsCircles.push_back(VladimirPutinMolodets);*/

	//cwt::ImGuiLoopHandler loopHandler;

	int selectedIndex = 0;

	while (window.isOpen()) {
		std::cout << "===========================================" << std::endl;
		std::cout << "              NEW LOOP                     " << std::endl;
		std::cout << "===========================================" << std::endl;
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event -> is<sf::Event::Closed>())
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		std::vector<std::string> vShapeStrings;
		for (auto& circle : lsCircles) {
			vShapeStrings.push_back(circle.getString());
		}
		cwt::ImGuiLoopHandler loopHandler(selectedIndex, lsCircles);

		ImGui::Begin("Settings");
		if (ImGui::BeginTabBar("Shape Settings"))
		{
			if (ImGui::BeginTabItem("Shape"))
			{
				static int currentItem = 0;

				if (ImGui::BeginCombo("aboba", vShapeStrings.at(currentItem).c_str())) {
					for (int i = 0; i < vShapeStrings.size(); i++) {
						const bool isSelected{selectedIndex == i};
						if (ImGui::Selectable(vShapeStrings[i].c_str(), isSelected)) {
							selectedIndex = i;
						}
						if (isSelected) {
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				ImGui::Spacing();
				ImGui::Checkbox("Draw circle", &loopHandler.isCircleDrawn);
				ImGui::SameLine();
				ImGui::Checkbox("Draw textString", &loopHandler.isTextDrawn);
				ImGui::SliderFloat("Radius", &loopHandler.radius, 0.0f, 200.0f);
				ImGui::SliderInt("Points", &loopHandler.pointCount, 3, 64);
				//std::cout << ImGuiColor[0] << " " << ImGuiColor[1] <<  " " << ImGuiColor[2] << std::endl;
				ImGui::ColorEdit3("Display Color", loopHandler.ImGuiCircleFillColor.data());
				//TODO: Сделать враппер над velocity чтобы скорость отображалась без минуса
				//Да можно передавать классы и стуктуры,
				//Правда в доках написано что это не очень безопасно, но пох
				ImGui::SliderFloat2("Velocity", &loopHandler.velocity.x, -10.f, 10.f);
				ImGui::InputText("Text", &loopHandler.textString);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();

		loopHandler.UpdateCWT(selectedIndex, lsCircles);

		window.clear();

		for (auto& shape : lsCircles) {
			std::cout << "Shape: " << shape.getString() << std::endl;
			shape.processScreenCollision(screenSize);
			shape.move();
			shape.draw(window);
		}

		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}