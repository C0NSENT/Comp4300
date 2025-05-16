//
// Created by consent_ on 07/05/25.
//

#ifndef CIRCLEWITHTEXT_H
#define CIRCLEWITHTEXT_H

#include <SFML/Graphics.hpp>

#include <string>
#include <array>


class CircleWithText {

	template<typename VectorType, typename DivisorType>
	static sf::Vector2<VectorType> vectorDivider(const sf::Vector2<VectorType>& v, DivisorType divisor);

	// Конвертация цветов между форматами ImGui и SFML
	static sf::Color ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor);
	static std::array<float, 3> SFMLColorToImGui(const sf::Color& color);

	static void processAxisCollision(const float CenterPos, const float Radius, float& velocity,  float axis );

	void centeringText();

public:
	CircleWithText(
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
	void setPointCount(const std::size_t& pointCount);
	void setVelocity(const sf::Vector2f& velocity);
	void setVelocity(const std::array<float, 2>& velocity);

	[[nodiscard]]std::array<float, 3> getImGuiFillColor() const;
	[[nodiscard]]std::array<float, 2> getImGuiVelocity() const;
	[[nodiscard]]sf::Vector2f getPosition() const;
	[[nodiscard]]float getRadius() const;
	[[nodiscard]]std::size_t getPointCount() const;
	[[nodiscard]]sf::Vector2f getVelocity() const;

	void move();
	void draw(sf::RenderWindow& window) const;
	void processScreenCollision(const sf::Vector2u& windowSize);

	sf::CircleShape circle;
	sf::Text text;

	bool isCircleDrawn;
	bool isTextDrawn;

private:

	sf::Vector2f velocity;
	sf::Vector2f textCenter;
};


#endif //CIRCLEWITHTEXT_H
