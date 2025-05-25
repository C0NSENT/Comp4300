//
// Created by consent_ on 21/05/25.
//

#pragma once

#include <fstream>
#include <string>

#include <chrono>


namespace lrh
{
	/////////////////////////////////////////////////////////////////////
	///
	/// \brief Синглтон для логирования игры
	///
	/////////////////////////////////////////////////////////////////////
	class Logger
	{
	public:
		enum class Level : uint8_t {
			Info = 0, Warning, Error
		};

		static Logger& instance();

		void write(Level level, const std::string& message);

		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

	private:
		explicit Logger(const std::string& fileName);
		~Logger();
		static std::string createFileName(const std::string& currentDateTime = currentDateTime());
		static std::string currentDateTime();


		std::string fileName;
		std::ofstream fileStream;
	};
}
