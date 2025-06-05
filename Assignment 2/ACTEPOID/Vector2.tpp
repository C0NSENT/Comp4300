/**
 * @date 05-06-2025
 * @author consent_
 *
 * @brief Самописный аналог sf::Vector2
 */

#pragma once

#include <type_traits>
#include <cmath>
#include <source_location>

///The Land Of Rape And Honey
namespace lrh
{
	/// Концепт для проверки является ли число нулем
	/*template<typename T>
	concept isNotZero = requires (T num, T num2)
	{
		num!=0.f;
	};*/

	template <typename T> requires std::is_arithmetic_v<T>
	class Vector2

	{
	public:
		constexpr Vector2() = default;
		constexpr Vector2(const T& x, const T& y) : x(x), y(y) {}
		constexpr Vector2(const Vector2& other) : x(other.x), y(other.y) {}

		/**
		 * @brief Вычисляет расстояние между двумя вектора
		 * по обеим осям
		 */
		[[nodiscard]] constexpr auto distance(const Vector2& other) const -> Vector2;


		/**
		 *
		 * @brief Вычисляет квадрат длины вектора
		 *
		 * @details Вычисляет гипотенузу по теореме Пифагора,
		 * но без квадратного корня
		*/
		[[nodiscard]] constexpr T lengthSquared() const;


		/**
		 * @brief Вычисляет длину вектора
		 *
		 * @details Вычисляет гипотенузу по теореме Пифагора
		 */
		[[nodiscard]] constexpr T length() const requires std::is_floating_point_v<T>;

		/**
		 * @brief Нормализация вектора
		 *
		 * @details Возвращает вектор длиной 1, при сохранении направления
		 */
		[[nodiscard]] constexpr Vector2 normalized() const requires std::is_floating_point_v<T>;

		///@brief Инвертирует знак
		constexpr auto operator-() const  -> Vector2;

		[[nodiscard]] constexpr auto operator+(const Vector2& rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator-(const Vector2& rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator*(const Vector2& rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator/(const Vector2& rhs) -> Vector2;
		constexpr auto operator=(const Vector2& rhs) -> Vector2&;

		constexpr auto operator+=(const Vector2& rhs) -> Vector2&;
		constexpr auto operator-=(const Vector2& rhs) -> Vector2&;
		constexpr auto operator*=(const Vector2& rhs) -> Vector2&;
		constexpr auto operator/=(const Vector2& rhs) -> Vector2&;

		[[nodiscard]] constexpr bool operator==(const Vector2& rhs) const;
		[[nodiscard]] constexpr bool operator!=(const Vector2& rhs) const;

		[[nodiscard]] constexpr auto operator+(T val) -> Vector2;
		[[nodiscard]] constexpr auto operator-(T val) -> Vector2;
		[[nodiscard]] constexpr auto operator*(T val) -> Vector2;
		[[nodiscard]] constexpr auto operator/(T val) -> Vector2;

		constexpr auto operator+=(T val) -> Vector2&;
		constexpr auto operator-=(T val) -> Vector2&;
		constexpr auto operator*=(T val) -> Vector2&;
		constexpr auto operator/=(T val) -> Vector2&;

		T x{0};
		T y{0};
	};



	///Псевдонимы для часто используемых типов, прям как в SFML
	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned>;


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::distance(const Vector2& other) const -> Vector2
	{
		return {x - other.x, y - other.y};
	}


	template<typename T>
	requires std::is_arithmetic_v<T>
	constexpr T Vector2<T>::lengthSquared() const
	{
		return {x * x + y * y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr T Vector2<T>::length() const
	requires std::is_floating_point_v<T>
	{
		return std::sqrt(this->lengthSquared());
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr Vector2<T> Vector2<T>::normalized() const
	requires std::is_floating_point_v<T>
	{
		return *this / length();
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-() const -> Vector2
	{
		return {-x, -y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+(const Vector2& rhs) -> Vector2
	{
		return {x + rhs.x, y + rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-(const Vector2& rhs) -> Vector2
	{
		return {x - rhs.x, y - rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*(const Vector2& rhs) -> Vector2
	{
		return {x * rhs.x, y * rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr Vector2<T> Vector2<T>::operator/(const Vector2& rhs)
	{
		return {x / rhs.x, y / rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator=(const Vector2& rhs) -> Vector2&
	{
		if (this != &rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+=(const Vector2& rhs) -> Vector2&
	{
		*this = *this + rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-=(const Vector2& rhs) -> Vector2&
	{
		*this = *this - rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*=(const Vector2& rhs) -> Vector2&
	{
		*this = *this * rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/=(const Vector2& rhs) -> Vector2&
	{
		*this = *this / rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr bool Vector2<T>::operator==(const Vector2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr bool Vector2<T>::operator!=(const Vector2& rhs) const
	{
		return !(*this == rhs);
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+(const T val) -> Vector2
	{
		return {x + val, y + val};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-(T val) -> Vector2
	{
		return {x - val, y - val};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*(T val) -> Vector2
	{
		return {x * val, y * val};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/(T val) -> Vector2
	{
		return {x / val, y / val};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+=(T val) -> Vector2&
	{
		*this = *this + val;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-=(T val) -> Vector2&
	{
		*this = *this - val;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*=(T val) -> Vector2&
	{
		*this = *this * val;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/=(T val) -> Vector2&
	{
		*this = *this / val;
		return *this;
	}
}
