//
// Created by consent_ on 21/05/25.
//

/////////////////////////////////////////////////////////////////////
///      СОВЕСТКИЙ ГЕНПЛАН
///TODO:
#pragma once

#include <fstream>
#include <sstream>
#include <string>




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
		enum class lvl : uint8_t
		{
			Info, Warning, Error, Debug, Fatal
		};

		friend std::ostream& operator<<(std::ostream& os, lvl lvl);

		[[nodiscard]] static Logger& instance();
		void write(lvl level, const std::string& message);

		/////////////////////////////////////////////////////////////////////
		///
		///		ЖЕРТВЫ СТАЛИНСКИХ РЕПРЕССИЙ
		///
		/////////////////////////////////////////////////////////////////////
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

	private:
		explicit Logger(const std::string& fileName);
		~Logger();

		static std::string createFileName();
		static std::string currentDateTime();
		static std::stringstream toStringStream;

		//Зачем я это добавил лол?

		//std::string fileName;
		std::ofstream ofs;
	};
}
