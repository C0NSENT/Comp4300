//
// Created by consent_ on 07/05/25.
//

#ifndef CIRCLEWITHTEXT_H
#define CIRCLEWITHTEXT_H

#include <SFML/Graphics.hpp>

#include <string>
#include <array>
#include <random>

class circleWithText {

	void centeringText();
	static sf::Color ImGuiColorToSFMLColor(const std::array<float, 4>& ImGuiColor);

public:
	circleWithText(float radius = 50, std::size_t pointCount = 32,
		const sf::Font& font, const std::string& s_text);

	void setColor(const std::array<float, 3>& ImGuiColor);

	void setPosition(const sf::Vector2f& position);

	sf::CircleShape circle;
	sf::Text text;

	sf::Vector2f velocity;
	sf::Vector2f textCenter;

	bool isCircleDrawn;
	bool isTextDrawn;
};


#endif //CIRCLEWITHTEXT_H
