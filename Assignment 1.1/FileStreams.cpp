//
// Created by consent_ on 18/05/25.
//

#include <fstream>
#include <random>

#ifndef FILESTREAMS
#define FILESTREAMS

class NamesParser
{
public:
	NamesParser() = delete;
	explicit NamesParser(const std::string& path)
		: _fNames(path)
	{
		if (!_fNames.is_open()) {
			throw std::runtime_error("Failed to open file: " + path);
		}
	}

	NamesParser(const NamesParser&) = delete;
	NamesParser& operator=(const NamesParser&) = delete;

	~NamesParser() {
		_fNames.close();
	}

	std::string getRandomName(std::mt19937_64& gen)
	{
		std::string name;
		_fNames.seekg(std::ios::beg); // Перемещает указатель в начало файла
		std::uniform_int_distribution distrib(0, 217);
		for (int i = 0; i < distrib(gen); ++i) {
			_fNames.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропускает строку
		}
		_fNames >> name;
		return name;
	}


private:
	std::ifstream _fNames;
};


#endif //FILESTREAMS