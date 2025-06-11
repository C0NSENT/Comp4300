/**
 * @date 11/06/25
 * 
 * @author consent_
 *
 * @brief Менеджер айдишников
 *
 * @details Синглтон менеджер, который представляет из себя std::array из bool.
 *	Айдишник, который он выдает это индекс булевой переменной в массиве.
 */

#pragma once

#include <array>
#include <cstdint>

namespace lrh
{
	class IdManager
	{
	public:

		[[nodiscard]] constexpr static IdManager &instance();

		[[nodiscard]] constexpr int16_t id();
		constexpr void freeId(int16_t id);

		constexpr static int16_t SIZE{ 16384 };
		constexpr static auto INVALID{ -1 };

	private:
		constexpr IdManager() = default;

		std::array<bool, SIZE> m_ids{}; //Блядь почему он сука бул в байтах хранит долбоеб
	};

	class Id
	{
	public:

		constexpr Id();
		~Id();

		auto operator<=>(const Id &) const = default;

	private:

		int16_t m_id{};
	};
}



