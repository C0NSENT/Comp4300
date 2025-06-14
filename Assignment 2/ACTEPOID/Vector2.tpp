/**
 * @date 05-06-2025
 * @author consent_
 *
 * @brief Самописный аналог sf::Vector2
 */

#pragma once

#include <cmath>
#include <source_location>
#include <stdexcept>
#include <string>
#include <type_traits>

///The Land Of Rape And Honey
namespace lrh
{
	template <typename T> requires std::is_arithmetic_v<T>
	class Vector2
	{
		using sl = std::source_location;

		///Выбрасывает ошибки если деление на ноль
		static void throwIfDivisionByZero(T num, const sl& location = sl::current());
		static void throwIfDivisionByZero(const Vector2& v, const sl& location = sl::current());

	public:
		constexpr Vector2() noexcept = default;
		constexpr Vector2(const T& x, const T& y) noexcept : x{x}, y{y} {}
		constexpr Vector2(const Vector2& rhs) noexcept = default;
		constexpr Vector2(Vector2 &&rhs) noexcept : x{ std::move( rhs.x ) }, y{ std::move( rhs.y ) } {}

		/**
		 * @brief Вычисляет расстояние между двумя вектора
		 * по обеим осям
		 */
		[[nodiscard]] constexpr auto distance(const Vector2& rhs) const noexcept -> Vector2;


		/**
		 *
		 * @brief Вычисляет квадрат длины вектора
		 *
		 * @details Вычисляет гипотенузу по теореме Пифагора,
		 * но без квадратного корня
		*/
		[[nodiscard]] constexpr T lengthSquared() const noexcept;


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
		constexpr auto operator-() const noexcept -> Vector2;

		[[nodiscard]] constexpr auto operator+(const Vector2& rhs) const noexcept -> Vector2;
		[[nodiscard]] constexpr auto operator-(const Vector2& rhs) const noexcept -> Vector2;
		[[nodiscard]] constexpr auto operator*(const Vector2& rhs) const noexcept -> Vector2;
		[[nodiscard]] constexpr auto operator/(const Vector2& rhs) const -> Vector2;
		constexpr auto operator=(const Vector2& rhs) noexcept -> Vector2&;
		constexpr auto operator=(Vector2 &&rhs) noexcept -> Vector2&;

		constexpr auto operator+=(const Vector2& rhs) noexcept -> Vector2&;
		constexpr auto operator-=(const Vector2& rhs) noexcept -> Vector2&;
		constexpr auto operator*=(const Vector2& rhs) noexcept -> Vector2&;
		constexpr auto operator/=(const Vector2& rhs) -> Vector2&;

		[[nodiscard]] constexpr bool operator==(const Vector2& rhs) const noexcept;
		[[nodiscard]] constexpr bool operator!=(const Vector2& rhs) const noexcept;

		[[nodiscard]] constexpr auto operator+(T num) const noexcept -> Vector2;
		[[nodiscard]] constexpr auto operator-(T num) const noexcept -> Vector2;
		[[nodiscard]] constexpr auto operator*(T num) const noexcept -> Vector2;
		[[nodiscard]] constexpr auto operator/(T num) const -> Vector2;

		constexpr auto operator+=(T num) noexcept -> Vector2&;
		constexpr auto operator-=(T num) noexcept -> Vector2&;
		constexpr auto operator*=(T num) noexcept -> Vector2&;
		constexpr auto operator/=(T num) -> Vector2&;

		[[nodiscard]] constexpr bool operator==(T num) const noexcept;
		[[nodiscard]] constexpr bool operator!=(T num) const noexcept;

		T x{};
		T y{};
	};


	///Псевдонимы для часто используемых типов, прям как в SFML
	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned>;


	template<typename T> requires std::is_arithmetic_v<T>
	void Vector2<T>::throwIfDivisionByZero(const T num, const sl &location)
	{
		if (num == 0)
		{
			throw std::logic_error(
				std::string{location.function_name()} +
				": error - Division by zero"
			);
		}
	}

	template<typename T> requires std::is_arithmetic_v<T>
	void Vector2<T>::throwIfDivisionByZero(const Vector2 &v, const sl &location)
	{
		throwIfDivisionByZero(v.x, location);
		throwIfDivisionByZero(v.y, location);
	}

	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::distance(const Vector2& rhs) const noexcept -> Vector2
	{
		return {x - rhs.x, y - rhs.y};
	}


	template<typename T>
	requires std::is_arithmetic_v<T>
	constexpr T Vector2<T>::lengthSquared() const noexcept
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
		throwIfDivisionByZero(length());
		return *this / length();
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-() const noexcept -> Vector2
	{
		return {-x, -y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+(const Vector2& rhs) const noexcept -> Vector2
	{
		return {x + rhs.x, y + rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-(const Vector2& rhs) const noexcept -> Vector2
	{
		return {x - rhs.x, y - rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*(const Vector2& rhs) const noexcept -> Vector2
	{
		return {x * rhs.x, y * rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/(const Vector2& rhs) const -> Vector2
	{
		throwIfDivisionByZero(rhs);
		return {x / rhs.x, y / rhs.y};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator=(const Vector2& rhs) noexcept -> Vector2&
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator=( Vector2 &&rhs ) noexcept -> Vector2 &
	{
		if (this != &rhs)
		{
			x = std::move( rhs.x );
			y = std::move( rhs.y );
		}
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+=(const Vector2& rhs) noexcept -> Vector2&
	{
		*this = *this + rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-=(const Vector2& rhs) noexcept -> Vector2&
	{
		*this = *this - rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*=(const Vector2& rhs) noexcept -> Vector2&
	{
		*this = *this * rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/=(const Vector2& rhs) -> Vector2&
	{
		throwIfDivisionByZero(rhs);
		*this = *this / rhs;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr bool Vector2<T>::operator==(const Vector2& rhs) const noexcept
	{
		return x == rhs.x and y == rhs.y;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr bool Vector2<T>::operator!=(const Vector2& rhs) const noexcept
	{
		return not (*this == rhs);
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+(const T num) const noexcept -> Vector2
	{
		return {x + num, y + num};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-(const T num) const noexcept -> Vector2
	{
		return {x - num, y - num};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*(const T num) const noexcept -> Vector2
	{
		return {x * num, y * num};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/(const T num) const -> Vector2
	{
		throwIfDivisionByZero(num);
		return {x / num, y / num};
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator+=(const T num) noexcept -> Vector2&
	{
		*this = *this + num;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator-=(const T num) noexcept -> Vector2&
	{
		*this = *this - num;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator*=(const T num) noexcept -> Vector2&
	{
		*this = *this * num;
		return *this;
	}


	template<typename T> requires std::is_arithmetic_v<T>
	constexpr auto Vector2<T>::operator/=(const T num) -> Vector2&
	{
		throwIfDivisionByZero(num);
		*this = *this / num;
		return *this;
	}

	template<typename T> requires std::is_arithmetic_v<T>
	constexpr bool Vector2<T>::operator==(const T num) const noexcept
	{
		return this->x == num and this->y == num;
	}

	template<typename T> requires std::is_arithmetic_v<T>
	constexpr bool Vector2<T>::operator!=(const T num) const noexcept
	{
		return not (*this == num);
	}
}
