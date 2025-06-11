/**
 * @date 11/06/25
 * 
 * @author consent_
 */

///Не, ну нахуй

#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>

template <typename T>
class ChunkedVector 
{

public:
	constexpr ChunkedVector( size_t chunkCount = 2, size_t chunkSize =  32);

	[[nodiscard]] T operator[](size_t index);
	[[nodiscard]] constexpr size_t getSize() const;

	constexpr size_t getChunkCount() const;

private:
	size_t chunk_size{};
	std::unordered_map<uint64_t, std::vector<T>> chunks;
};
