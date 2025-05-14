//
// Created by consent_ on 07/05/25.
//

#include "circlewithtext.h"

#include <iostream>
#include <cmath>
#include <ranges>

template<typename VectorType, typename DivisorType>
sf::Vector2<VectorType> circleWithText::vectorDivider(const sf::Vector2<VectorType> &v, DivisorType divisor)
{
	return std::move(sf::Vector2<VectorType> {v.x / divisor, v.y / divisor});
}

sf::Color circleWithText::ImGuiColorToSFMLColor(const std::array<float, 4> &ArrImGuiColor)
{
	auto convert = []( float ImGuiColorChannel) -> std::uint8_t
	{
		if (ImGuiColorChannel <= 1.0f && ImGuiColorChannel >= 0.0f) {
			return std::round(ImGuiColorChannel);
		} else
			throw std::invalid_argument("Invalid ImGuiColor");
	};

	for (float num : ArrImGuiColor) {
		convert(num);
	}

	return sf::Color(
		ArrImGuiColor[0],
		ArrImGuiColor[1],
		ArrImGuiColor[2],
		ArrImGuiColor[3]
	);
}

void circleWithText::centeringText()
{
	std::cout << "circleWithText::centeringText()" << std::endl;
	this->textCenter = circle.getLocalBounds().getCenter() - text.getLocalBounds().getCenter();
	/*auto test =  vectorDivider(text.getGlobalBounds().position, 2.0f);
	std::cout << test.x << " " << test.y << std::endl;
	std::cout << text.getGlobalBounds().position.x << " " << text.getGlobalBounds().position.y << std::endl;*/

}


circleWithText::circleWithText(
	const sf::Font& font,
	const std::string& s_text,
	float radius,
	std::size_t pointCount,
	const sf::Vector2f& position,
	const sf::Vector2f& velocity
	)
	: circle{radius, pointCount}
	, text(font, s_text, 24)
	, velocity(std::move(velocity))
{
	std::cout << "circleWithText::circleWithText()" << std::endl;
	centeringText();
	this->setPosition(position);
	isCircleDrawn = isTextDrawn = true;

	//TODO: Сделать систему инвертирования цвета букв относительно самой фигуры
	//Временно
	circle.setFillColor(sf::Color::Red);
}

void circleWithText::setFillColor(const std::array<float, 4> &ImGuiColor)
{
	std::cout << "circleWithText::setFillColor()" << std::endl;
	circle.setFillColor(ImGuiColorToSFMLColor(ImGuiColor));
}

void circleWithText::setPosition(const sf::Vector2f &position)
{
	std::cout << "circleWithText::setPosition()" << std::endl;
	circle.setPosition(position);
	text.setPosition(position + textCenter);
}

void circleWithText::setRadius(float radius)
{
	try {
		std::cout << "circleWithText::setRadius()" << std::endl;
		circle.setRadius(radius);
	} catch (const std::bad_alloc& e) {
		std::cerr << "Это гнида вызывает этот прикол " << e.what() << std::endl;
	}

	centeringText();
}

void circleWithText::move()
{
	std::cout << "circleWithText::move()" << std::endl;
	this->setPosition(this->circle.getPosition() + velocity);
}

/*void circleWithText::move(const sf::Vector2f &velocity)
{
	std::cout << "circleWithText::move(const sf::Vector2f&)" << std::endl;


	/*circle.move(velocity);
	text.setPosition(circle.getPosition() + textCenter);#1#
}*/



