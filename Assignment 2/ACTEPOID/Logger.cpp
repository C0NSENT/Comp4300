//
// Created by consent_ on 21/05/25.
//

#include "Logger.hpp"

#include <sstream>

#include <array>
#include <ctime>
#include <filesystem>
#include <ranges>
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

    void Logger::write(
        const std::string &message,
        const Level lvl,
        const sl& loc
    )
    {
        static auto format{"%Y %m %d | %H:%M:%S"};

        std::stringstream log;

        log << lvl << "\t: "
            << '[' << getCurrentDateTime(format) << " | "
            << formatFileName(loc.file_name()) << "\t| "
            << loc.function_name() << " | "
            << loc.line() << "] : "
            << message << '\n';

        ofs << log.str();
        ofs.flush();
    }

    Logger& Logger::getInstance()
    {
        static Logger singleton(createFileName());
        return singleton;
    }

    int Logger::getCurrentLogID()
    {
        namespace fs = std::filesystem;

        constexpr static auto logNameFormat{"%Y_%m_%d_"};
        const static fs::path path(logsDir);

        for (const auto& entry : fs::directory_iterator(logsDir))
        {
            const std::string fileName{entry.path().filename()};
            if (fileName.starts_with(getCurrentDateTime(logNameFormat)))
            {
                const std::size_t idPos = fileName.find_last_of('_') + 1;
                const std::string strID = fileName.substr(idPos);

                return std::stoi(strID)+1;
            }
        }
        return 0;
    }

    void Logger::info(const std::string &message, const sl &loc)
    {
        getInstance().write(message, Level::Info, loc);
    }

    void Logger::debug(const std::string &message, const sl &loc)
    {
        getInstance().write(message, Level::Debug, loc);
    }

    void Logger::warning(const std::string &message, const sl &loc)
    {
        getInstance().write(message, Level::Warning, loc);
    }

    void Logger::error(const std::string &message, const sl &loc)
    {
        getInstance().write(message, Level::Error, loc);
    }

    void Logger::fatal(const std::string &message, const sl &loc)
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
        std::filesystem::create_directory(logsDir);
        static std::stringstream fileName;
        fileName << /*logsDir <<*/ getCurrentDateTime("%Y_%m_%d_") << logIDtoStr(getCurrentLogID()) << ".log";
        std::cout << fileName.str().c_str() << std::endl;

        static const char* name(fileName.str().c_str());
        return name;
    }

    const char *Logger::getCurrentDateTime(const char* format)
    {
        const std::time_t currentTime{std::time(nullptr)};
        const std::tm* structTime{std::localtime(&currentTime)};

        constexpr static std::size_t bufferSize{25};
        static char buffer[bufferSize];

        //constexpr static auto timeFormat{"%Y %m %d | %H:%M:%S"};
        std::strftime(buffer, bufferSize, format, structTime);

        return buffer;
    }

    std::string Logger::logIDtoStr(const int id)
    {
        std::string strID{std::to_string(id)};
        const auto zeros = static_cast<int>(3 - strID.length());

        strID.insert(strID.begin(), zeros, '0');

        return strID;
    }

    const char* Logger::formatFileName(const std::string &fileName)
    {
        //Ебать я  умный
        const std::size_t pos = fileName.find_last_of('/');
        return &fileName[pos + 1];
    }
}
