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

#include <cstdint>
#include <utility> ///<- Нужно для хэширования
#include <vector>
#include <deque>

namespace lrh
{
	class Id
	{
		class IdManager;

	public:

		static constexpr int16_t SIZE{ 16384 };
		static constexpr int16_t INVALID{ -1 };

		Id();
		explicit Id(int16_t id ) noexcept;
		Id( const Id &id) noexcept;
		Id(Id &&rhs) noexcept = default;
		~Id();


		[[nodiscard]] int16_t id() const noexcept;

		auto operator<=>(const Id &) const noexcept = default;

		Id &operator=(const Id &rhs);
		Id &operator=(Id &&) noexcept = default;

	private:

		int16_t m_id;
	};


	class Id::IdManager
	{
	public:

		[[nodiscard]] static IdManager &instance();

		//[[nodiscard]] int16_t id();
		[[nodiscard]] int16_t getNewId();
		void addCopy( int16_t id ) noexcept;
		void freeId(int16_t id) noexcept;

		[[nodiscard]] auto usedIdFlags() const noexcept -> const std::deque<uint8_t>&;

		IdManager(const IdManager &) = delete;
		IdManager &operator=(const IdManager &) = delete;

	private:

		IdManager() noexcept = default;

		//int16_t m_lastUsedId{};
		//std::vector<bool> m_usedIdFlags{};
		std::deque<uint8_t> m_idCopyCount;
	};
}


template<>
struct std::hash<lrh::Id>
{
	size_t operator()(const lrh::Id &id) const noexcept;
};




