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
#include <functional> ///<- Нужно для хэширования

namespace lrh
{
	class Id
	{
		class IdManager;

	public:

		Id();
		constexpr Id(int16_t id );
		~Id();

		int16_t id() const;
		static constexpr int16_t maxId();
		static constexpr int16_t invalidId();
		static const auto &usedIds();

		auto operator<=>(const Id &) const = default;

		Id(const Id &rhs);
		Id &operator=(const Id &) = delete;

	private:

		bool m_isTemp;
		int16_t m_id;
	};

	class Id::IdManager
	{
	public:

		static constexpr int16_t SIZE{ 16384 };
		static constexpr int16_t INVALID{ -1 };

	private:

		using UsedIdArray = std::array<bool, SIZE>;
	public:
		[[nodiscard]] static IdManager &instance();

		[[nodiscard]] int16_t id();
		void freeId(int16_t id);

		const UsedIdArray &usedIds() const;



	private:

		IdManager() = default;

		IdManager(const IdManager &) = delete;
		IdManager &operator=(const IdManager &) = delete;

		//TODO: Когда будет время сделать указатель на массив для оптимизации
		//bool *currentId { &m_ids[0] };

		UsedIdArray m_usedIds{}; //Блядь почему он сука бул в байтах хранит долбоеб
	};
}


template<>
struct std::hash<lrh::Id>
{
	size_t operator()(const lrh::Id &id) const noexcept;
};




