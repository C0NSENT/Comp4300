//
// Created by consent_ on 21/05/25.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.tpp"

namespace lrh::cmp
{
	struct Component
	{
		virtual ~Component() = default;
	};


	struct Transform final : public Component
	{
		constexpr Transform() = default;
		constexpr Transform( const Vector2f &position, const Vector2f &velocity, const float angle )
			: pos{ position }, velocity{ velocity }, angle{ angle } {}
		constexpr Transform( const Transform & ) = default;

		/*constexpr ~Transform()
		{
			std::cout << "~CTransform()" << std::endl;
		};*/

		Vector2f pos{};
		Vector2f velocity{};
		float angle{};

	};


	struct PolygonShape final : public Component
	{
		constexpr PolygonShape() = default;


		constexpr PolygonShape(
			const float radius,
			const size_t points,
			const sf::Color &fill,
			const sf::Color &outline,
			const float thickness
		)
			: polygonShape{ radius, points }
		{
			polygonShape.setFillColor( fill );
			polygonShape.setOutlineColor( outline );
			polygonShape.setOutlineThickness( thickness );
			polygonShape.setOrigin( { radius, radius } );
		}


		constexpr PolygonShape( const PolygonShape & ) = default;

		sf::CircleShape polygonShape{};
	};


	struct Collision final : public Component
	{
		constexpr Collision() = default;
		constexpr explicit Collision( const float radius ) : radius{ radius } {}
		constexpr Collision( const Collision & ) = default;

		float radius{};
	};


	struct Score final : public Component
	{
		constexpr Score() = default;


		constexpr explicit Score( const uint32_t score ) : score{ score } {}

		uint32_t score{};
	};


	struct Lifespan final : public Component
	{
		constexpr Lifespan() = default;


		constexpr explicit Lifespan( const uint16_t time )
			: remaining{ time }, total{ time }
		{
		}


		constexpr Lifespan( const Lifespan & ) = default;

		///Возможно придется переделывать чтобы
		///нормально работало со временем sfml
		uint16_t remaining{};
		uint16_t total{};
	};


	struct Input final : public Component
	{
		constexpr Input() = default;


		constexpr Input(
			const bool up,
			const bool left,
			const bool right,
			const bool down
		)
			: up{ up }
			, left{ left }
			, right{ right }
			, down{ down }
		{
		}

		constexpr Input( const Input & ) = default;

		bool up{}, left{}, right{}, down{}, shoot{};
	};
}

