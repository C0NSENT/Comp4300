//
// Created by consent_ on 21/05/25.
//

#include "Logger.hpp"

#include <sstream>

#include <array>
#include <ctime>

#include <iostream>


namespace lrh
{
    std::ostream& operator<<(std::ostream &ss, const Logger::Level level)
    {
        constexpr static std::array arrStrLvl {
            "INFO", "WARNING", "ERROR","DEBUG", "FATAL"
        };

        ss << arrStrLvl[static_cast<int>(level)];

        return ss;
    }

    Logger& Logger::getInstance()
    {
        static Logger singleton(createFileName());
        return singleton;
    }

    void Logger::write(
        const std::string &message,
        const Level lvl,
        const std::source_location& loc
    )
    {
        std::stringstream log;

        log << lvl << "\t: "
            << '[' << currentDateTime() << " | "
            << formatFileName(loc.file_name()) << "\t| "
            << loc.function_name() << " | "
            << loc.line() << "] : "
            << message << '\n';

        ofs << log.str();
        ofs.flush();
        std::cout << "абоб" << std::endl;
    }

    void Logger::info(const std::string &message, const std::source_location &loc)
    {
        getInstance().write(message, Level::Info, loc);
    }

    void Logger::debug(const std::string &message, const std::source_location &loc)
    {
        getInstance().write(message, Level::Debug, loc);
    }

    void Logger::warning(const std::string &message, const std::source_location &loc)
    {
        getInstance().write(message, Level::Warning, loc);
    }

    void Logger::error(const std::string &message, const std::source_location &loc)
    {
        getInstance().write(message, Level::Error, loc);
    }

    void Logger::fatal(const std::string &message, const std::source_location &loc)
    {
        getInstance().write(message, Level::Fatal, loc);
    }

    Logger::Logger(const char* fileName)
    {
        ofs.open(fileName, std::ios::app);

        if (not ofs.is_open()) {
            throw std::runtime_error("Could not open log file: " + std::string{fileName});
        }
    }

    Logger::~Logger() {
        //Закрываем файл и можно добавить
        //Закрывающее сообщение лог файла
        //TODO: Чекнуть как другие работяги закрывают лог файл
        //ofs << "this is the end, my lonely friend, the end\n";
    }

    const char* Logger::createFileName() {
        return {"log_.log"};
    }

    const char* Logger::currentDateTime() {
        const std::time_t currentTime = std::time(nullptr);
        const std::tm* structTime = std::localtime(&currentTime);

        constexpr static std::size_t bufferSize{25};
        static char buffer[bufferSize];

        constexpr static auto timeFormat{"%Y %m %d | %H:%M:%S"};
        std::strftime(buffer, bufferSize, timeFormat, structTime);

        return buffer;
    }

    const char* Logger::formatFileName(const std::string &fileName)
    {
        //Ебать я  умный
        const std::size_t pos = fileName.find_last_of('/');
        return &fileName[pos + 1];
    }
}
