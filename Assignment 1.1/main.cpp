//
// Created by consent_ on 07/05/25.
//

#include "NamedCircle.h"
#include "FileStreams.cpp"

#include "imgui.h"
#include "imgui-SFML.h"
#include <misc/cpp/imgui_stdlib.h> //Враппер для плюсов, чтобы с сишным калом не возиться

#include<iostream>
#include <vector>

#include <random>

//TODO: синглттон логгер
//TODO: Переделать добавление новых кругов, чтобы они друга на друга не накладывались
//TODO: Переписать весь в соответствие с ECS

template<typename T>
void outputSfVector(const std::string& label, const sf::Vector2<T> & vector) {
	std::cout << label << ": " << vector.x << ", " << vector.y << std::endl;
}

void outputSfVector(const std::string& label, const sf::FloatRect& vector) {
	std::cout << label << ": " << vector.position.x
		<< ", " << vector.position.y << std::endl;
}

//TODO: Переделать рандом, а то кал какой-то

bool areCirclesColliding(const nc::NamedCircle& circle1, const nc::NamedCircle& circle2);
void handleCirclesAxisCollision(float circle1Center,
	float circle2Center, float& circle1Velocity, float& circle2Velocity);
void processCirclesCollision(std::list<nc::NamedCircle>& lsCircles);

int main()
{
	constexpr sf::Vector2u screenSize{1280, 720};
	constexpr auto windowTitle{"Podnimayemsya s Kolen"};

	sf::RenderWindow window(sf::VideoMode(screenSize), windowTitle);
	window.setFramerateLimit(60);
	static_cast<void>(ImGui::SFML::Init(window));

	sf::Clock deltaClock{};

	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	std::random_device seed{};
	std::mt19937_64 gen{seed()};

	NamesParser fNames{"../../../Comp4300/Assignment 1.1/names.txt"};

	const sf::Font font{"../../../Comp4300/stuff/font.ttf"};

	std::list<nc::NamedCircle> lsCircles{};
	for (short i = 0; i < 3; i++)
		lsCircles.emplace_back(gen, font, fNames.getRandomName(gen), screenSize);

	int selectedIndex{0};

	while (window.isOpen()) {
		std::cout
			<< "===========================================\n"
			<< "              NEW LOOP                     \n"
			<< "===========================================" << std::endl;

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

		window.clear();

		loopHandler.UpdateNC(selectedIndex, lsCircles, screenSize);

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

bool areCirclesColliding(const nc::NamedCircle &circle1, const nc::NamedCircle &circle2)
{
	const sf::Vector2f circle1Center{circle1.getCircleCenter()};
	const sf::Vector2f circle2Center{circle2.getCircleCenter()};

	//Отрезки
	const sf::Vector2f Segments{ circle1Center.x - circle2Center.x,
		circle1Center.y - circle2Center.y };

	//Расстояние между двумя центрами кругов
	const float hypotenuse = std::hypot(Segments.x, Segments.y);

	return hypotenuse <= circle1.getRadius() + circle2.getRadius();
}

void handleCirclesAxisCollision(const float circle1Center,
	const float circle2Center, float& circle1Velocity, float& circle2Velocity)
{
	if (circle1Center < circle2Center) {
		nc::invertSignTo(false, circle1Velocity);
		nc::invertSignTo(true, circle2Velocity);
	}
	else {
		nc::invertSignTo(true, circle1Velocity);
		nc::invertSignTo(false, circle2Velocity);
	}
}

//ЭТО ПИЗДЕЦ
void processCirclesCollision(std::list<nc::NamedCircle> &lsCircles)
{
	for (auto it1 = lsCircles.begin(); it1 != lsCircles.end(); ++it1)
	{
		for (auto it2 = std::next(it1); it2 != lsCircles.end(); ++it2)
		{
			if (areCirclesColliding(*it1, *it2))
			{
				handleCirclesAxisCollision(
					it1->getCircleCenter().x,
					it2->getCircleCenter().x,
					it1->velocity.x,
					it2->velocity.x
				);

				handleCirclesAxisCollision(
					it1->getCircleCenter().y,
					it2->getCircleCenter().y,
					it1->velocity.y,
					it2->velocity.y
				);
			}
		}
	}
}
