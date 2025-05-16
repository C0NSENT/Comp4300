//
// Created by consent_ on 07/05/25.
//

#include "CircleWithText.h"

#include <iostream>
#include <cmath>
#include <ranges>


template<typename VectorType, typename DivisorType>
sf::Vector2<VectorType> CircleWithText::vectorDivider(const sf::Vector2<VectorType> &v, DivisorType divisor)
{
	return std::move(sf::Vector2<VectorType> {v.x / divisor, v.y / divisor});
}

sf::Color CircleWithText::ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor)
{
	auto convert = [](const float ImGuiColorChannel) -> std::uint8_t
	{
		if (ImGuiColorChannel <= 1.0f && ImGuiColorChannel >= 0.0f)
			return static_cast<std::uint8_t>(std::round(ImGuiColorChannel * 255.f));

		throw std::invalid_argument("Invalid ImGuiColor");
	};

	return sf::Color{
		convert(ImGuiColor[0]),
		convert(ImGuiColor[1]),
		convert(ImGuiColor[2]),
	};
}

std::array<float, 3> CircleWithText::SFMLColorToImGui(const sf::Color& color)
{
	return std::array{
		static_cast<float>(color.r) / 255.f,
		static_cast<float>(color.g) / 255.f,
		static_cast<float>(color.b) / 255.f,
	};
}

void CircleWithText::centeringText()
{
	std::cout << "CircleWithText::centeringText()" << std::endl;
	this->textCenter = circle.getLocalBounds().getCenter() - text.getLocalBounds().getCenter();
	/*auto test =  vectorDivider(text.getGlobalBounds().position, 2.0f);
	std::cout << test.x << " " << test.y << std::endl;
	std::cout << text.getGlobalBounds().position.x << " " << text.getGlobalBounds().position.y << std::endl;*/

}


CircleWithText::CircleWithText(
	const sf::Font& font,
	const std::string& s_text,
	float radius,
	std::size_t pointCount,
	const sf::Vector2f& position,
	const sf::Vector2f& velocity
	)
	: circle{radius, pointCount}
	, text(font, s_text, 24)
	, velocity(velocity)
{
	std::cout << "CircleWithText::CircleWithText()" << std::endl;
	centeringText();
	this->setPosition(position);
	isCircleDrawn = isTextDrawn = true;

	//TODO: Сделать систему инвертирования цвета букв относительно самой фигуры

}

void CircleWithText::setCircleFillColor(const std::array<float, 3>& ImGuiColor)
{
	std::cout << "CircleWithText::setFillColor()" << std::endl;
	setCircleFillColor(ImGuiColorToSFMLColor(ImGuiColor));
}

void CircleWithText::setCircleFillColor(const sf::Color& color)
{
	this->circle.setFillColor(color);
}

void CircleWithText::setPosition(const sf::Vector2f &position)
{
	std::cout << "CircleWithText::setPosition()" << std::endl;
	circle.setPosition(position);
	text.setPosition(position + textCenter);
}

void CircleWithText::setRadius(float radius)
{
	try {
		std::cout << "CircleWithText::setRadius()" << std::endl;
		circle.setRadius(radius);
	} catch (const std::bad_alloc& e) {
		std::cerr << "Это гнида вызывает этот прикол " << e.what() << std::endl;
	}

	centeringText();
}

void CircleWithText::setVelocity(const sf::Vector2f &velocity)
{
	this->velocity = velocity;
}

void CircleWithText::setVelocity(const std::array<float, 2> &velocity)
{
	setVelocity(sf::Vector2f{velocity[0], velocity[1]});
}


std::array<float, 3> CircleWithText::getImGuiFillColor() const
{
	return SFMLColorToImGui(this->circle.getFillColor());
}

std::array<float, 2> CircleWithText::getImGuiVelocity() const
{
	return {velocity.x, velocity.y};
}

void CircleWithText::move()
{
	std::cout << "CircleWithText::move()" << std::endl;
	this->setPosition(this->circle.getPosition() + velocity);
}

/*void CircleWithText::move(const sf::Vector2f &velocity)
{
	std::cout << "CircleWithText::move(const sf::Vector2f&)" << std::endl;


	circle.move(velocity);
	text.setPosition(circle.getPosition() + textCenter);#1#
}*/

void CircleWithText::draw(sf::RenderWindow& window) const
{
	if (isCircleDrawn) {window.draw(circle);}
	if (isTextDrawn) {window.draw(text);}
}


