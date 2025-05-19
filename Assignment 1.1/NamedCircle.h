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
		constexpr static sf::Color ImGuiColorToSFMLColor(const std::array<float, 3>& ImGuiColor);
		constexpr static std::array<float, 3> SFMLColorToImGui(const sf::Color& color);
		constexpr static sf::Color invertColor(const sf::Color& color);

		constexpr static int randomInt(std::mt19937_64& gen, int min, int max);
		constexpr static float randomFloat(std::mt19937_64& gen, float min, float max);

		constexpr static void processAxisCollision(float centerPos, float radius, float& velocity,  float axis );
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

		[[nodiscard]] constexpr float getRadius() const;
		[[nodiscard]] constexpr std::size_t getPointCount() const;
		[[nodiscard]] constexpr std::string getName() const;
		[[nodiscard]] constexpr sf::Vector2f getPosition() const;
		[[nodiscard]] constexpr sf::Vector2f getVelocity() const;
		[[nodiscard]] constexpr std::array<float, 2> getImGuiVelocity() const;
		[[nodiscard]] constexpr std::array<float, 3> getImGuiFillColor() const;

		bool operator==(const NamedCircle& other) const;

		///////////////////////////////////////////////////
		////    ДРУГИЕ МЕТОДЫ
		///////////////////////////////////////////////////

		void move();
		void draw(sf::RenderWindow& window) const;
		void processScreenCollision(const sf::Vector2u& screenSize);
		//void processOtherCircleCollision(NamedCircle& otherCircle);

		///////////////////////////////////////////////////
		////	СВОЙСТВА
		//////////////////////////////////////////////////

		sf::CircleShape circle;
		sf::Text name;

		bool isCircleDrawn;
		bool isTextDrawn;

	private:

		sf::Vector2f velocity;
		sf::Vector2f textCenter;
	};

	///////////////////////////////////////////////////
	////	ФУНКЦИИ ДЛЯ СТОРОННИХ КЛАССОВ
	//////////////////////////////////////////////////

	// Можно если что удалить
	template<typename VectorType, typename DivisorType>
	static sf::Vector2<VectorType> vectorDivider(const sf::Vector2<VectorType>& v, DivisorType divisor);

	static NamedCircle getElement(unsigned selectedIndex, const std::list<NamedCircle>& lsCircles);
	static NamedCircle& getElementRef(unsigned selectedIndex, std::list<NamedCircle>& lsCircles);

	///////////////////////////////////////////////////
	////	ImGuiLoopHandler
	//////////////////////////////////////////////////

	struct ImGuiLoopHandler
	{
		///////////////////////////////////////////////////
		////	КОНСТУКТОРЫ
		//////////////////////////////////////////////////

		ImGuiLoopHandler() = delete;
		ImGuiLoopHandler(unsigned selectedIndex, const NamedCircle& circle);
		ImGuiLoopHandler(unsigned selectedIndex, const std::list<NamedCircle>& lsCircles);

		void UpdateNC(unsigned selectedIndex, NamedCircle &circle, const sf::Vector2u &screenSize) const;
		void UpdateNC(unsigned selectedIndex, std::list<NamedCircle>& lsCircles,
			const sf::Vector2u &screenSize) const;

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
}

#endif
