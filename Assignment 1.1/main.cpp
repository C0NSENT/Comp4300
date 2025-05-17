//
// Created by consent_ on 07/05/25.
//

#include "CircleWithText.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include <misc/cpp/imgui_stdlib.h> //Враппер для плюсов, чтобы с сишным калом не возиться

#include<iostream>

#include <list>
#include <iterator>
#include <vector>

#include <algorithm>
#include <random>
//TODO: синглттон логгер

std::vector<std::string> getShapesString(const std::list<cwt::CircleWithText>& lShapes)
{
	std::vector<std::string> shapesString;
	for (const auto& shape : lShapes) {
		shapesString.push_back(shape.getString());
	}
	return shapesString;
}


cwt::CircleWithText findElement(const std::list<cwt::CircleWithText>& list, unsigned index)
{
	if (list.size() > index) {
		auto it = list.begin();
		std::advance(it, index);
		return *it;
	}

	std::cerr << "List is out of range:" << list.size() << "<" << index << std::endl ;
	throw std::out_of_range("List out of range") ;

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
	
	const sf::Font font{"../../../Comp4300/stuff/font.ttf"};

	std::list<cwt::CircleWithText> lsShapes;


	cwt::CircleWithText shape{font, "Aboba"};
	shape.setPosition({screenSize.x /2.f, screenSize.y / 2.f});
	shape.setCircleFillColor(sf::Color{128, 32, 94});

	lsShapes.push_back(shape);
	lsShapes.push_back(shape);
	lsShapes.push_back(shape);

	cwt::ImGuiLoopHandler loopHandler;
	std::vector vShapeStrings{getShapesString(lsShapes)};
	//std::list<cwt::CircleWithText>::iterator it;

	int selectedIndex = 0;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event -> is<sf::Event::Closed>())
				window.close();
		}

		shape.processScreenCollision(screenSize);

		ImGui::SFML::Update(window, deltaClock.restart());


		loopHandler = findElement(lsShapes, selectedIndex);

		ImGui::Begin("Settings");
		if (ImGui::BeginTabBar("Shape Settings"))
		{
			if (ImGui::BeginTabItem("Shape"))
			{
				static int currentItem = 0;

				if (ImGui::BeginCombo("aboba", vShapeStrings.at(currentItem).c_str())) {
					for (int i = 0; i < vShapeStrings.size(); i++) {
						const bool isSelected = (selectedIndex == i);
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
				ImGui::Checkbox("Draw circle", &shape.isCircleDrawn);
				ImGui::SameLine();
				ImGui::Checkbox("Draw textString", &shape.isTextDrawn);
				ImGui::SliderFloat("Radius", &loopHandler.radius, 0.0f, 200.0f);
				ImGui::SliderInt("Points", &loopHandler.pointCount, 3, 64);
				//std::cout << ImGuiColor[0] << " " << ImGuiColor[1] <<  " " << ImGuiColor[2] << std::endl;
				ImGui::ColorEdit3("Display Color", loopHandler.ImGuiColor.data());
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

		loopHandler.UpdateCWT(shape);

		window.clear();

		shape.draw(window);

		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}