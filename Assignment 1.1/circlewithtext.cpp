//
// Created by consent_ on 07/05/25.
//

#include "circlewithtext.h"

#include <cstdint>
#include <ranges>



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

circleWithText::circleWithText(const float radius,
	const std::size_t pointCount,
	const sf::Font &font,
	const std::string &s_text
)
	: circle(radius, pointCount)
	, text(font, s_text, 24)
{
	isCircleDrawn = isTextDrawn = true;
	centeringText();
}

void circleWithText::setColor(const std::array<float, 3> &ImGuiColor)
{
}

void circleWithText::setPosition(const sf::Vector2f &position)
{
	circle.setPosition(position);
	centeringText();
}

void circleWithText::centeringText()
{
	this->textCenter = circle.getGlobalBounds().getCenter()
		- text.getGlobalBounds().getCenter();
}




