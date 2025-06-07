//
// Created by consent_ on 21/05/25.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.tpp"

namespace lrh
{
	struct Component {
		virtual ~Component() = default;
	};

	struct CTransform final : public Component
	{
		Vector2f pos{0.f, 0.f};
		Vector2f velocity{0.f, 0.f};
		float angle{0};

		constexpr CTransform() = default;
		constexpr CTransform(const Vector2f &p, const Vector2f &v, const float a)
			: pos(p), velocity(v), angle(a) {}
		constexpr CTransform(const CTransform&) = default;
	};

	struct CPolygonShape final : public Component
	{
		sf::CircleShape polygonShape;

		constexpr CPolygonShape() = default;
		constexpr CPolygonShape(
			const float radius,
			const int points,
			const sf::Color& fill,
			const sf::Color& outline,
			const float thickness
		)
		: polygonShape(radius, points)
		{
			polygonShape.setFillColor(fill);
			polygonShape.setOutlineColor(outline);
			polygonShape.setOutlineThickness(thickness);
			polygonShape.setOrigin({radius, radius});
		}
		constexpr CPolygonShape(const CPolygonShape& ) = default;
	};

	struct CCollision final : public Component{
		float radius{0};

		constexpr CCollision() = default;
		constexpr explicit CCollision(const float r) : radius(r) {}
		constexpr CCollision(const CCollision&) = default;
	};

	struct CScore final : public Component
	{
		uint16_t score{0};

		constexpr CScore() = default;
		constexpr explicit CScore(const uint16_t s) : score(s) {}
	};

	struct CLifespan final : public Component
	{
		///Возможно придется переделывать чтобы
		///нормально работало со временем sfml
		uint16_t remaining{0};
		uint16_t total{0};

		constexpr CLifespan() = default;
		constexpr explicit CLifespan(const uint16_t t)
			: remaining(t), total(t) {}
		constexpr CLifespan(const CLifespan&) = default;
	};

	struct CInput final : public Component
	{
		bool up{false};
		bool left{false};
		bool right{false};
		bool down{false};
		bool shoot{false};

		constexpr CInput() = default;
		constexpr CInput(
			const bool up,
			const bool left,
			const bool right,
			const bool down
			)
			: up(up)
			, left(left)
			, right(right)
			, down(down)
		{
		}
		constexpr CInput(const CInput&) = default;
	};
}
