//
// Created by consent_ on 07/05/25.
//

#ifndef CIRCLEWITHTEXT_H
#define CIRCLEWITHTEXT_H

#include <SFML/Graphics.hpp>

#include <string>
#include <array>


class circleWithText {

	/*int randomIntNumber(int min, int max);
	float randomFloatNumber(float min, float max);*/

	template<typename VectorType, typename DivisorType>
	static sf::Vector2<VectorType> vectorDivider(const sf::Vector2<VectorType>& v, DivisorType divisor);
	//Сишный массив ебобанный ты козел нахуй
	static sf::Color ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor);
	static std::array<float, 3> SFMLColorToImGui(const sf::Color& color);

	void centeringText();

public:
	circleWithText(
		const sf::Font& font,
		const std::string& s_text,
		float radius = 50,
		std::size_t pointCount = 32,
		const sf::Vector2f& position = {0.f, 0.f},
		const sf::Vector2f& velocity = {1.5f, 0.5f}
		);

	void setCircleFillColor(const std::array<float, 3>& ImGuiColor);
	void setCircleFillColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& position);
	void setRadius(float radius);



	std::array<float, 3> getImGuiFillColor() const;

	void move();
	//void move(const sf::Vector2f& velocity);

	//void draw();



	sf::CircleShape circle;
	sf::Text text;
	sf::Vector2f velocity;
	sf::Vector2f textCenter;
	bool isCircleDrawn;
	bool isTextDrawn;
};


#endif //CIRCLEWITHTEXT_H
