//
// Created by consent_ on 21/05/25.
//

/////////////////////////////////////////////////////////////////////
///      СОВЕСТКИЙ ГЕНПЛАН
///
///		TODO: Адекватное формирование названия лога
#pragma once

#include <fstream>
#include <string>

#include <source_location>

namespace lrh
{
	/////////////////////////////////////////////////////////////////////
	///
	/// \brief Синглтон для логирования игры
	///
	/////////////////////////////////////////////////////////////////////
	class Logger
	{
		using sl =  std::source_location;
		enum class Level : uint8_t
		{
			Info, Debug, Warning, Error,  Fatal
		};

		friend std::ostream& operator<<(std::ostream& ss, Level level);

	public:
		static void info(const std::string& message,
			const sl& loc = sl::current());
		static void debug(const std::string& message,
			const sl& loc = sl::current());
		static void warning(const std::string& message,
			const sl& loc = sl::current());
		static void error(const std::string& message,
			const sl& loc = sl::current());
		static void fatal(const std::string& message,
			const sl& loc = sl::current());

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

		static Logger& getInstance();

		void write(
			const std::string &message,
			Level lvl,
			const sl& loc = sl::current()
		);
		static int getCurrentLogID();

		static const char* createFileName();
		static const char *getCurrentDateTime(const char *format);

		static std::string logIDtoStr(int id);
		static const char *formatFileName(const std::string &fileName);

		constexpr static auto logsDir{"logs/"};

		std::ofstream ofs;
	};
}
