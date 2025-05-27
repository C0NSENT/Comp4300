#pragma once

#include <type_traits>
#include <cmath>
#include "Logger.hpp"

///The Land Of Rape And Honey
namespace lrh
{
	/////////////////////////////////////////////////////////////////////
	/// \brief Концепт для проверки типа на числовой.
	///	\details Добавил чтобы всю эту хуйбалу не писать по сто раз
	///
	/////////////////////////////////////////////////////////////////////
	template<typename T>
	concept is_numeric = std::is_arithmetic_v<T>
		and not std::is_same_v<T, bool>
		and not std::is_same_v<T, char>;

	/////////////////////////////////////////////////////////////////////
	/// \brief Самописный аналог sf::Vector2
	///
	/////////////////////////////////////////////////////////////////////

	template <typename T> requires is_numeric<T>
	class Vector2
	{
	public:
		/////////////////////////////////////////////////////////////////////
		///
		///        КОНСТУКТОРЫ
		///
		/////////////////////////////////////////////////////////////////////
		constexpr Vector2() = default;
		constexpr Vector2(const T& x, const T& y) : x(x), y(y) {}
		constexpr Vector2(const Vector2& other) : x(other.x), y(other.y) {}

		/////////////////////////////////////////////////////////////////////
		///
		///        МЕТОДЫ
		///
		/////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////
		/// \brief Вычисляет расстояние
		///			между двумя векторами по  обеим осям
		///
		/////////////////////////////////////////////////////////////////////
		constexpr auto distance(const Vector2& other) const -> Vector2;

		/////////////////////////////////////////////////////////////////////
		/// \brief Вычисляет квадрат длины вектора
		/// \details Вычисляет гипотенузу по
		///         теореме Пифагора, но без
		///			квадратного корня
		///
		/////////////////////////////////////////////////////////////////////
		constexpr T lengthSquared() const;

		/////////////////////////////////////////////////////////////////////
		/// \brief Вычисляет длину вектора
		/// \details Вычисляет гипотенузу по
		///         теореме Пифагора
		///
		/////////////////////////////////////////////////////////////////////
		constexpr T length() const;

		/////////////////////////////////////////////////////////////////////
		///
		///        ПЕРЕГРУЗКА ОПЕРАТОРОВ
		///
		/////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////
		/// \brief Инверсия знака числа
		///
		/////////////////////////////////////////////////////////////////////
		constexpr auto operator-() -> Vector2;

		[[nodiscard]] constexpr auto operator+(const Vector2& rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator-(const Vector2& rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator*(const Vector2& rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator/(const Vector2& rhs) -> Vector2;
		constexpr auto operator=(const Vector2& rhs) -> Vector2&;

		constexpr auto operator+=(const Vector2& rhs) -> Vector2&;
		constexpr auto operator-=(const Vector2& rhs) -> Vector2&;
		constexpr auto operator*=(const Vector2& rhs) -> Vector2&;
		constexpr auto operator/=(const Vector2& rhs) -> Vector2&;

		//Добавил const чтобы можно было сравнивать константные векторы
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

		/////////////////////////////////////////////////////////////////////
		///
		///        СВОЙСТВА
		///
		/////////////////////////////////////////////////////////////////////
		T x{0};
		T y{0};
	};

	/////////////////////////////////////////////////////////////////////
	///	\brief Псевдонимы для часто используемых типов
	///	\details Прям как в SFML
	///
	/////////////////////////////////////////////////////////////////////
	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned>;

	/////////////////////////////////////////////////////////////////////
	///
	///        РЕАЛИЗАЦИЯ
	///
	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::distance(const Vector2& other) const -> Vector2
	{
		return {x - other.x, y - other.y};
	}

	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr T Vector2<T>::lengthSquared() const
	{
		return {x * x + y * y};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr T Vector2<T>::length() const
	{
		return std::sqrt(this->lengthSquared());
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator-() -> Vector2
	{
		return {-x, -y};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator+(const Vector2& rhs) -> Vector2
	{
		return {x + rhs.x, y + rhs.y};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator-(const Vector2& rhs) -> Vector2
	{
		return {x - rhs.x, y - rhs.y};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator*(const Vector2& rhs) -> Vector2
	{
		return {x * rhs.x, y * rhs.y};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr Vector2<T> Vector2<T>::operator/(const Vector2& rhs)
	{
		return {x / rhs.x, y / rhs.y};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator=(const Vector2& rhs) -> Vector2&
	{
		if (this != &rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator+=(const Vector2& rhs) -> Vector2&
	{
		*this = *this + rhs;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator-=(const Vector2& rhs) -> Vector2&
	{
		*this = *this - rhs;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator*=(const Vector2& rhs) -> Vector2&
	{
		*this = *this * rhs;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator/=(const Vector2& rhs) -> Vector2&
	{
		*this = *this / rhs;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr bool Vector2<T>::operator==(const Vector2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr bool Vector2<T>::operator!=(const Vector2& rhs) const
	{
		return !(*this == rhs);
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator+(const T val) -> Vector2
	{
		return {x + val, y + val};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator-(T val) -> Vector2
	{
		return {x - val, y - val};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator*(T val) -> Vector2
	{
		return {x * val, y * val};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator/(T val) -> Vector2
	{
		return {x / val, y / val};
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator+=(T val) -> Vector2&
	{
		*this = *this + val;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator-=(T val) -> Vector2&
	{
		*this = *this - val;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator*=(T val) -> Vector2&
	{
		*this = *this * val;
		return *this;
	}


	/////////////////////////////////////////////////////////////////////
	template<typename T> requires is_numeric<T>
	constexpr auto Vector2<T>::operator/=(T val) -> Vector2&
	{
		*this = *this / val;
		return *this;
	}
}
