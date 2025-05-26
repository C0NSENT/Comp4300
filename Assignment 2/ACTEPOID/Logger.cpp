//
// Created by consent_ on 21/05/25.
//

#include "Logger.hpp"

#include <sstream>

#include <array>
#include <ctime>


namespace lrh
{
    std::ostream& operator<<(std::ostream &ss, const Level level)
    {
        constexpr static std::array arrStrLvl {
            "INFO", "WARNING", "ERROR","DEBUG", "FATAL"
        };

        ss << arrStrLvl[static_cast<int>(level)];

        return ss;
    }

    Logger& Logger::instance()
    {
        static Logger singleton(createFileName());
        return singleton;
    }

    void Logger::write(
        const std::string &message,
        const Level level,
        const std::source_location& location
    )
    {
        std::stringstream log;

        log << '[' << currentDateTime() << "] "
            << "[" << level << "]\t"
            << '\"' << location.file_name() << '\"'
            << "(" << location.line() << ":"
            << location.column() << ")\t"
            << location.function_name() << '\t'
            << message << '\n';

        ofs << log.str();
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
        const static std::time_t currentTime = std::time(nullptr);
        const std::tm* structTime = std::localtime(&currentTime);

        constexpr static std::size_t bufferSize{20};
        static char buffer[bufferSize];
        //TODO: Не
        constexpr static auto timeFormat{"%Y-%m-%d %H:%M:%S"};
        std::strftime(buffer, bufferSize, timeFormat, structTime);

        return buffer;
    }
}