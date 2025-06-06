//
// Created by consent_ on 21/05/25.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2.tpp"

namespace lrh
{


	struct Component {
		enum class Type : std::uint8_t {
			transform, shape, collision, score, lifeSpan, input
		};
	};

	struct CTransform : Component
	{
		Vector2f pos{0.0, 0.0};
		Vector2f velocity{0.0, 0.0};
		float angle{0};

		CTransform()=default;
		CTransform(const Vector2f &p, const Vector2f &v, float a)
			: pos(p), velocity(v), angle(a) {}
	};

	struct CShape : Component
	{
		sf::CircleShape circle;

		CShape(
			const float radius,
			const int points,
			const sf::Color& fill,
			const sf::Color& outline,
			const float thickness
		)
		: circle(radius, points)
		{
			circle.setFillColor(fill);
			circle.setOutlineColor(outline);
			circle.setOutlineThickness(thickness);
			circle.setOrigin({radius, radius});
		}
	};

	struct CCollision : Component{
		float radius{0};

		CCollision(const float r) : radius(r) {}
	};

	struct CScore {
		unsigned score{0};

		explicit CScore(const unsigned s) : score(s) {}
	};

	struct CLifespan : Component
	{
		unsigned remaining{0};
		unsigned total{0};

		explicit CLifespan(const unsigned t)
			: remaining(t), total(t) {}
	};

	struct CInput : Component
	{
		bool up{false};
		bool left{false};
		bool right{false};
		bool down{false};
		bool shoot{false};

		CInput() = default;
	};
}
