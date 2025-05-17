//
// Created by consent_ on 07/05/25.
//

#ifndef CIRCLEWITHTEXT_H
#define CIRCLEWITHTEXT_H

#include <SFML/Graphics.hpp>

#include <string>
#include <array>

//TODO: Сделать перенос строки для текста в круге

namespace cwt
{
	class CircleWithText {
		template<typename VectorType, typename DivisorType>
		static sf::Vector2<VectorType> vectorDivider(const sf::Vector2<VectorType>& v, DivisorType divisor);

		// Конвертация цветов между форматами ImGui и SFML
		static sf::Color ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor);
		static std::array<float, 3> SFMLColorToImGui(const sf::Color& color);

		static void processAxisCollision(const float CenterPos, const float Radius, float& velocity,  float axis );

		void centeringText();

	public:

		///////////////////////////////////////////////////
		////	КОНСТУКТОР
		//////////////////////////////////////////////////
		CircleWithText(
			const sf::Font& font,
			const std::string& s_text,
			float radius = 50,
			std::size_t pointCount = 32,
			const sf::Vector2f& position = {0.f, 0.f},
			const sf::Vector2f& velocity = {1.5f, 0.5f}
			);

		///////////////////////////////////////////////////
		////	СЕТТЕРЫ
		//////////////////////////////////////////////////

		void setCircleFillColor(const std::array<float, 3>& ImGuiColor);
		void setCircleFillColor(const sf::Color& color);
		void setPosition(const sf::Vector2f& position);
		void setRadius(float radius);
		void setPointCount(const std::size_t& pointCount);
		void setVelocity(const sf::Vector2f& velocity);
		void setVelocity(const std::array<float, 2>& velocity);
		void setString(const std::string& text);

		///////////////////////////////////////////////////
		////	ГЕТТЕРЫ
		//////////////////////////////////////////////////

		[[nodiscard]]std::array<float, 3> getImGuiFillColor() const;
		[[nodiscard]]std::array<float, 2> getImGuiVelocity() const;
		[[nodiscard]]sf::Vector2f getPosition() const;
		[[nodiscard]]float getRadius() const;
		[[nodiscard]]std::size_t getPointCount() const;
		[[nodiscard]]sf::Vector2f getVelocity() const;
		[[nodiscard]]std::string getString() const;

		void move();
		void draw(sf::RenderWindow& window) const;
		void processScreenCollision(const sf::Vector2u& windowSize);

		///////////////////////////////////////////////////
		////	СВОЙСТВА
		//////////////////////////////////////////////////

		sf::CircleShape circle;
		sf::Text text;

		//TODO: НАРОД ТРЕБУЕТ БИТСЕТ
		bool isCircleDrawn;
		bool isTextDrawn;

	private:

		sf::Vector2f velocity;
		sf::Vector2f textCenter;
	};

	struct ImGuiLoopHandler
	{
		ImGuiLoopHandler() = default;
		ImGuiLoopHandler& operator=(const CircleWithText& circle);

		static void pushData(unsigned id, const CircleWithText &circle);
		void UpdateCWT(unsigned id, CircleWithText &circle) const;

		unsigned currentID;

		float radius;
		int pointCount;
		sf::Vector2f position;
		sf::Vector2f velocity;
		std::string textString;
		std::array<float, 3> ImGuiColor;


		//sf::Color textFillColor;
		//sf::Color textOutlineColor;
		//float textOutlineThickness;
	};
}

#endif
