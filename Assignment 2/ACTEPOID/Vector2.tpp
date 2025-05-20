#pragma once

#include <tuple>
#include <type_traits>

///The Land Of Rape And Honey
namespace lrh
{
	template <typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	class Vector2
	{
	public:
		/////////////////////////////////////
		///    КОНСТУКТОРЫ
		////////////////////////////////////

		constexpr Vector2() = default;
		constexpr Vector2(const T& x, const T& y) : x(x), y(y) {}
		constexpr Vector2(const Vector2& other) : x(other.x), y(other.y) {}

		//////////////////////////////////////////////////////////////////////
		/// \brief Вычисляет расстояние
		///			между двумя векторами по  обеим осям
		///
		/////////////////////////////////////////////////////////////////////
		constexpr auto distance(const Vector2 &other) const -> Vector2;

		/////////////////////////////////////////////////////////////////////
		/// \brief Вычисляет гипотенузу по
		///			теореме Пифагора, но без
		///			квадратного корня
		///
		/////////////////////////////////////////////////////////////////////
		constexpr auto lengthSquared() const;

		/////////////////////////////////////
		///    ПЕРЕГРУЗКА ОПЕРАТОРОВ
		////////////////////////////////////

		constexpr auto operator-() -> Vector2;

		[[nodiscard]] constexpr auto operator+(const Vector2 &rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator-(const Vector2 &rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator*(const Vector2 &rhs) -> Vector2;
		[[nodiscard]] constexpr auto operator/(const Vector2 &rhs) -> Vector2;
		constexpr auto operator=(const Vector2 &rhs) -> Vector2 &;

		constexpr auto operator+=(const Vector2 &rhs) -> Vector2 &;
		constexpr auto operator-=(const Vector2 &rhs) -> Vector2 &;
		constexpr auto operator*=(const Vector2 &rhs) -> Vector2 &;
		constexpr auto operator/=(const Vector2 &rhs) -> Vector2 &;

		[[nodiscard]] constexpr bool operator==(const Vector2& rhs);
		[[nodiscard]] constexpr bool operator!=(const Vector2& rhs);

		[[nodiscard]] constexpr auto operator+(T val) -> Vector2;
		[[nodiscard]] constexpr auto operator-(T val) -> Vector2;
		[[nodiscard]] constexpr auto operator*(T val) -> Vector2;
		[[nodiscard]] constexpr auto operator/(T val) -> Vector2;

		constexpr auto operator+=(T val) -> Vector2 &;
		constexpr auto operator-=(T val) -> Vector2 &;
		constexpr auto operator*=(T val) -> Vector2 &;
		constexpr auto operator/=(T val) -> Vector2 &;

		T x{};
		T y{};
	};

	/////////////////////////////////////////////////////////////////////
	///	\brief Псевдонимы для часто используемых типов
	///
	/////////////////////////////////////////////////////////////////////
	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned>;

	////////////////////////////////////////////////////////////////

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::distance(const Vector2 &other) const -> Vector2
	{
		return {x - other.x, y - other.y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::lengthSquared() const
	{
		return {x * x + y * y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator-() -> Vector2
	{
		*this = {-x, -y};
		return {-x, -y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator+(const Vector2& rhs) -> Vector2
	{
		return {x + rhs.x, y + rhs.y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator-(const Vector2& rhs) -> Vector2
	{
		return {x - rhs.x, y - rhs.y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator*(const Vector2& rhs) -> Vector2
	{
		return {x * rhs.x, y * rhs.y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr Vector2<T> Vector2<T>::operator/(const Vector2& rhs)
	{
		return {x / rhs.x, y / rhs.y};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator=(const Vector2& rhs) -> Vector2&
	{
		if (this != &rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator+=(const Vector2 &rhs) -> Vector2&
	{
		*this = *this + rhs;
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator-=(const Vector2 &rhs) -> Vector2&
	{
		*this = *this - rhs;
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator*=(const Vector2 &rhs) -> Vector2&
	{
		*this = *this * rhs;
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator/=(const Vector2 &rhs) -> Vector2&
	{
		*this = *this / rhs;
		return *this;
	}

	template<typename T> requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr bool Vector2<T>::operator==(const Vector2 &rhs) {
		return x == rhs.x && y == rhs.y;
	}

	template<typename T> requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr bool Vector2<T>::operator!=(const Vector2 &rhs) {
		return !(*this == rhs);
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator+(const T val) -> Vector2
	{
		return {x + val, y + val};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator-(T val) -> Vector2
	{
		return {x - val, y - val};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator*(T val) -> Vector2
	{
		return {x * val, y * val};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator/(T val) -> Vector2
	{
		return {x / val, y / val};
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator+=(T val) -> Vector2 &
	{
		*this = *this + val;
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator-=(T val) -> Vector2 &
	{
		*this = *this - val;
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator*=(T val) -> Vector2 &
	{
		*this = *this * val;
		return *this;
	}

	template<typename T>
	requires (std::is_arithmetic_v<T> && !std::is_same_v<T, bool>)
	constexpr auto Vector2<T>::operator/=(T val) -> Vector2 &
	{
		*this = *this / val;
		return *this;
	}
}
