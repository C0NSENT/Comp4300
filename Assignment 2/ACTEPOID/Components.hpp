//
// Created by consent_ on 21/05/25.
//

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Vector2.tpp"

namespace lrh::cmp
{
	struct BaseComponent
	{
		virtual ~BaseComponent() = default;
		virtual BaseComponent* clone() const=0;
	};


	struct Transform final : public BaseComponent
	{
		constexpr Transform() = default;
		constexpr Transform(const Transform&) = default;
		constexpr Transform(Transform&&) = default;

		BaseComponent* clone() const override { return new Transform(*this); }

		constexpr Transform( const Vector2f &position, const Vector2f &velocity, const float angle )
			: pos{ position }, velocity{ velocity }, angle{ angle } {}


		Vector2f pos{};
		Vector2f velocity{};
		float angle{};
	};


	struct PolygonShape final : public BaseComponent
	{
		constexpr PolygonShape() = default;
		constexpr PolygonShape(const PolygonShape&) = default;
		constexpr PolygonShape(PolygonShape&&) = default;

		BaseComponent* clone() const override { return new PolygonShape(*this); }

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


		sf::CircleShape polygonShape{};
	};


	struct Collision final : public BaseComponent
	{
		constexpr Collision() = default;
		constexpr Collision(const Collision&) = default;
		constexpr Collision(Collision&&) = default;

		BaseComponent* clone() const override { return new Collision(*this); }

		constexpr explicit Collision( const float radius ) : radius{ radius } {}

		float radius{};

	};


	struct Score final : public BaseComponent
	{
		constexpr Score() = default;
		constexpr Score(const Score&) = default;
		constexpr Score(Score&&) = default;

		BaseComponent* clone() const override { return new Score(*this); }

		constexpr explicit Score( const uint32_t score ) : score{ score } {}


		uint32_t score{};
	};


	struct Lifespan final : public BaseComponent
	{
		constexpr Lifespan() = default;
		constexpr Lifespan(const Lifespan&) = default;
		constexpr Lifespan(Lifespan&&) = default;

		BaseComponent* clone() const override { return new Lifespan(*this); }

		constexpr explicit Lifespan( const uint16_t time )
			: remaining{ time }, total{ time } {}


		///Возможно придется переделывать чтобы
		///нормально работало со временем sfml
		uint16_t remaining{};
		uint16_t total{};
	};


	struct Input final : public BaseComponent
	{
		constexpr Input() = default;
		constexpr Input(const Input&) = default;
		constexpr Input(Input&&) = default;

		BaseComponent* clone() const override { return new Input(*this); }

		constexpr Input(
			const bool up,
			const bool left,
			const bool right,
			const bool down,
			const bool shoot
		)
			: up{ up }
			, left{ left }
			, right{ right }
			, down{ down }
			, shoot{ shoot }
		{
		}


		bool up{}, left{}, right{}, down{}, shoot{};
	};
}

