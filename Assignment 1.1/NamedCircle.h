//
// Created by consent_ on 07/05/25.
//

#ifndef NAMEDCIRCLE_H
#define NAMEDCIRCLE_H

#include <SFML/Graphics.hpp>

#include <string>
#include <array>
#include <list>
#include <random>

//TODO: Сделать перенос строки для текста в круге

namespace nc
{
	class NamedCircle {
		// Конвертация цветов между форматами ImGui и SFML
		constexpr static sf::Color ImGuiColorToSFMLColor(
			const std::array<float, 3>& ImGuiColor);
		constexpr static std::array<float, 3> SFMLColorToImGui(
			const sf::Color& color);
		constexpr static sf::Color invertColor(const sf::Color& color);

		constexpr static int randomInt(std::mt19937_64& gen, int min, int max);
		constexpr static float randomFloat(std::mt19937_64& gen,
			float min, float max);

		constexpr static void processAxisCollision(float centerPos,
			float radius, float& velocity,  float axis );
		constexpr void centeringText();

	public:

		///////////////////////////////////////////////////
		////	КОНСТУКТОРЫ
		//////////////////////////////////////////////////
		explicit NamedCircle(
			const sf::Font& font,
			const sf::String& name,
			float radius = 50,
			int pointCount = 32,
			const sf::Vector2f& position = {0.f, 0.f},
			const sf::Vector2f& velocity = {1.5f, 0.5f}
		);

		explicit NamedCircle(
			std::mt19937_64& gen,
			const sf::Font& font,
			const sf::String& name,
			const sf::Vector2u& screenSize
		);
		///////////////////////////////////////////////////
		////	СЕТТЕРЫ
		//////////////////////////////////////////////////

		void setCircleFillColor(const std::array<float, 3>& ImGuiColor);
		void setCircleFillColor(const sf::Color& color);
		void setColor(const sf::Color& color);
		void setColor(const std::array<float, 3>& ImGuiColor);
		void setPosition(const sf::Vector2f& position);
		void setRadius(float radius, const sf::Vector2u& screenSize);
		void setPointCount(const std::size_t& pointCount);
		void setVelocity(const sf::Vector2f& velocity);
		void setVelocity(const std::array<float, 2>& velocity);
		void setName(const std::string& name);

		///////////////////////////////////////////////////
		////	ГЕТТЕРЫ
		//////////////////////////////////////////////////

		//оказывается при объявлении функции constexpr она становится inline
		[[nodiscard]] constexpr float getRadius() const {
			return circle.getRadius();
		}
		[[nodiscard]] constexpr auto getPointCount() const -> std::size_t {
			return circle.getPointCount();
		}
		[[nodiscard]] constexpr auto getName() const -> std::string {
			return name.getString();
		}
		[[nodiscard]] constexpr auto getPosition() const -> sf::Vector2f{
			return circle.getPosition();
		}
		[[nodiscard]] constexpr auto getCircleCenter() const -> sf::Vector2f {
			return circle.getGlobalBounds().getCenter();
		}
		[[nodiscard]] constexpr auto getVelocity() const -> sf::Vector2f {
			return velocity;
		}
		[[nodiscard]] constexpr auto getImGuiVelocity() const ->  std::array<float, 2> {
			return {velocity.x, velocity.y};
		}
		[[nodiscard]] constexpr auto getImGuiFillColor() const -> std::array<float, 3> {
			return SFMLColorToImGui(this->circle.getFillColor());
		}

		bool operator==(const NamedCircle& other) const;

		///////////////////////////////////////////////////
		////    ДРУГИЕ МЕТОДЫ
		///////////////////////////////////////////////////

		void move();
		void draw(sf::RenderWindow& window) const;
		void processScreenCollision(const sf::Vector2u& screenSize);

		///////////////////////////////////////////////////
		////	СВОЙСТВА
		//////////////////////////////////////////////////

		sf::CircleShape circle;
		sf::Text name;

		sf::Vector2f velocity;
		sf::Vector2f textCenter;

		bool isCircleDrawn;
		bool isTextDrawn;
	};

	///////////////////////////////////////////////////
	////	ФУНКЦИИ ДЛЯ СТОРОННИХ КЛАССОВ
	//////////////////////////////////////////////////

	//оказывается шаблонные функции должны быть определены
	//в том же файле где были объвлены
	template<typename T>
	//я знал что так можно не знал как это сделать
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr void invertSignTo(bool isPositive, T &num);

	static NamedCircle getElement(unsigned selectedIndex,
		const std::list<NamedCircle>& lsCircles);
	static NamedCircle& getElementRef(unsigned selectedIndex,
		std::list<NamedCircle>& lsCircles);

	///////////////////////////////////////////////////
	////	ImGuiLoopHandler
	//////////////////////////////////////////////////

	struct ImGuiLoopHandler
	{
		///////////////////////////////////////////////////
		////	КОНСТУКТОРЫ
		//////////////////////////////////////////////////

		ImGuiLoopHandler() = delete;
		ImGuiLoopHandler(unsigned selectedIndex,
			const NamedCircle& circle);
		ImGuiLoopHandler(unsigned selectedIndex,
			const std::list<NamedCircle>& lsCircles);

		void UpdateNC(unsigned selectedIndex,
			NamedCircle &circle, const sf::Vector2u &screenSize) const;
		void UpdateNC(
			unsigned selectedIndex,
			std::list<NamedCircle>& lsCircles,
			const sf::Vector2u &screenSize
		) const;

		ImGuiLoopHandler& operator=(const NamedCircle& circle);

		///////////////////////////////////////////////////
		////	СВОЙСТВА
		//////////////////////////////////////////////////

		unsigned currentIndex;

		float radius;
		int pointCount;
		sf::Vector2f velocity;
		std::string name;
		std::array<float, 3> ImGuiCircleFillColor;
		bool isCircleDrawn;
		bool isNameDrawn;
	};

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr void invertSignTo(const bool isPositive, T &num) {
		if (isPositive) num = std::abs(num);
		else num = -std::abs(num);
	}
}

#endif
