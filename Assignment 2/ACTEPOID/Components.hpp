//
// Created by consent_ on 21/05/25.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.tpp"

namespace lrh
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


	struct CPolygonShape final : public Component
	{
		constexpr CPolygonShape() = default;


		constexpr CPolygonShape(
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


		constexpr CPolygonShape( const CPolygonShape & ) = default;

		sf::CircleShape polygonShape{};
	};


	struct CCollision final : public Component
	{
		constexpr CCollision() = default;
		constexpr explicit CCollision( const float radius ) : radius{ radius } {}
		constexpr CCollision( const CCollision & ) = default;

		float radius{};
	};


	struct CScore final : public Component
	{
		constexpr CScore() = default;


		constexpr explicit CScore( const uint32_t score ) : score{ score } {}

		uint32_t score{};
	};


	struct CLifespan final : public Component
	{
		constexpr CLifespan() = default;


		constexpr explicit CLifespan( const uint16_t time )
			: remaining{ time }, total{ time }
		{
		}


		constexpr CLifespan( const CLifespan & ) = default;

		///Возможно придется переделывать чтобы
		///нормально работало со временем sfml
		uint16_t remaining{};
		uint16_t total{};
	};


	struct CInput final : public Component
	{
		constexpr CInput() = default;


		constexpr CInput(
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

		constexpr CInput( const CInput & ) = default;

		bool up{}, left{}, right{}, down{}, shoot{};
	};
}
