//
// Created by consent_ on 21/05/25.
//

/////////////////////////////////////////////////////////////////////
///      СОВЕСТКИЙ ГЕНПЛАН
///		TODO: Вывод даты и времени влог
///		TODO: Адекватное формирование названия лога
#pragma once

#include <fstream>
#include <string>

#include <source_location>


namespace lrh
{
	enum class Level : uint8_t
	{
		Info, Warning, Error, Debug, Fatal
	};

	std::ostream& operator<<(std::ostream& ss, Level level);


	/////////////////////////////////////////////////////////////////////
	///
	/// \brief Синглтон для логирования игры
	///
	/////////////////////////////////////////////////////////////////////
	class Logger
	{
	public:
		[[nodiscard]] static Logger& instance();
		void write(
			const std::string &message,
			Level level = Level::Info,
			const std::source_location& location = std::source_location::current()
		);

		/////////////////////////////////////////////////////////////////////
		///
		///		ЖЕРТВЫ СТАЛИНСКИХ РЕПРЕССИЙ
		///
		/////////////////////////////////////////////////////////////////////
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

	private:
		explicit Logger(const char* fileName);
		~Logger();

		static const char* createFileName();
		static const char* currentDateTime();


		std::ofstream ofs;
	};
}
