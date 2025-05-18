//
// Created by consent_ on 07/05/25.
//

#include "NamedCircle.h"
#include "FileStreams.cpp""

#include "imgui.h"
#include "imgui-SFML.h"
#include <misc/cpp/imgui_stdlib.h> //Враппер для плюсов, чтобы с сишным калом не возиться

#include<iostream>
#include <vector>

#include <random>

//TODO: синглттон логгер

template<typename T>
void outputSfVector(const std::string& label, const sf::Vector2<T> & vector) {
	std::cout << label << ": " << vector.x << ", " << vector.y << std::endl;
}

void outputSfVector(const std::string& label, const sf::FloatRect& vector) {
	std::cout << label << ": " << vector.position.x
		<< ", " << vector.position.y << std::endl;
}

/*void processCirclesCollision(const std::list<nc::NamedCircle>& lsCircles)
{
	auto temp = lsCircles;
	auto itBegin = temp.begin();
	auto itEnd = temp.end();
	/*for (auto& circle : temp) {
		for (auto& otherCircle : temp) {
				if (circle.processOtherCircleCollision(otherCircle)) {

			}
		}
	}#1#
	while (itBegin != itEnd) {
		if (itBegin->processOtherCircleCollision(*itEnd)) {
			std::cout << "asfasdfasdfds" << std::endl;
			temp.erase(itBegin);
			temp.erase(itEnd);
			itBegin = temp.begin();
			itEnd = temp.end();
		}
		else {
			++itBegin;
			--itEnd;
		}
	}
}*/
void processCirclesCollision(std::list<nc::NamedCircle>& lsCircles)
{
	std::vector isProcessed(lsCircles.size(), false);
	//std::cout << "asfasdfasdfds" << std::endl;
	int it1Index = 0;
	for (auto & circle : lsCircles) {
		int it2Index = 0;
		for (auto & otherCircle : lsCircles) {
			if (not(isProcessed[it2Index] && isProcessed[it1Index])) {
				if (circle.circle.getGlobalBounds().findIntersection(otherCircle.circle.getGlobalBounds())) {
					circle.processOtherCircleCollision(otherCircle);
					isProcessed[it2Index] = true;
					isProcessed[it1Index] = true;
				}
			}
			++it2Index;
			++it1Index;
		}
	}
	//std::cout << "asfasdfasdfds" << std::endl;
}
int main()
{
	constexpr sf::Vector2u screenSize{1280, 720};
	constexpr auto windowTitle{"Podnimayemsya s Kolen"};
	sf::RenderWindow window(sf::VideoMode(screenSize), windowTitle);
	window.setFramerateLimit(120);
	static_cast<void>(ImGui::SFML::Init(window));

	sf::Clock deltaClock;

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	std::random_device seed;
	std::mt19937_64 gen(seed());

	NamesParser fNames("../../../Comp4300/Assignment 1.1/names.txt");

	const sf::Font font{"../../../Comp4300/stuff/font.ttf"};

	std::list<nc::NamedCircle> lsCircles;
	lsCircles.emplace_back(gen, font, fNames.getRandomName(gen), screenSize);
	lsCircles.emplace_back(gen, font, fNames.getRandomName(gen), screenSize);
	lsCircles.emplace_back(gen, font, fNames.getRandomName(gen), screenSize);

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
			vShapeStrings.push_back(circle.getName());
		}
		nc::ImGuiLoopHandler loopHandler(selectedIndex, lsCircles);

		ImGui::Begin("BALLS");
		if (ImGui::BeginTabBar("Shape Settings"))
		{
			if (ImGui::BeginTabItem("Circle"))
			{
				if (ImGui::BeginCombo("Circle List", vShapeStrings.at(selectedIndex).c_str())) {
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
				ImGui::Checkbox("Draw name", &loopHandler.isNameDrawn);
				ImGui::SliderFloat("Radius", &loopHandler.radius, 0.0f, 200.0f);
				ImGui::SliderInt("Points", &loopHandler.pointCount, 32, 64);
				//std::cout << ImGuiColor[0] << " " << ImGuiColor[1] <<  " " << ImGuiColor[2] << std::endl;
				ImGui::ColorEdit3("Display Color", loopHandler.ImGuiCircleFillColor.data());
				//TODO: Сделать враппер над velocity чтобы скорость отображалась без минуса
				//Да можно передавать классы и стуктуры,
				//Правда в доках написано что это не очень безопасно, но пох
				ImGui::SliderFloat2("Velocity", &loopHandler.velocity.x, -10.f, 10.f);
				ImGui::InputText("Name", &loopHandler.name);
				ImGui::NewLine();
				ImGui::Spacing();

				if (ImGui::Button("Add Circle"))
				{
					lsCircles.emplace_back(gen, font, fNames.getRandomName(gen), screenSize);
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();

		loopHandler.UpdateNC(selectedIndex, lsCircles, screenSize);

		window.clear();


		processCirclesCollision(lsCircles);

		for (auto& circle : lsCircles) {
			std::cout << "Shape: " << circle.getName() << std::endl;
			circle.processScreenCollision(screenSize);
			circle.move();
			circle.draw(window);
		}


		ImGui::SFML::Render(window);
		window.display();
	}
	return 0;
}