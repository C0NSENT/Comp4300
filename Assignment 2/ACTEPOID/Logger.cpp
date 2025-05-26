//
// Created by consent_ on 21/05/25.
//

#include "Logger.hpp"

#include <array>
#include <ctime>

lrh::Logger& lrh::Logger::instance()
{
    static Logger singleton(createFileName());
    return singleton;
}

void lrh::Logger::write(const lvl level, const std::string& message)
{
    //TODO: Добавить цветовую оформленность сообщений в зависимости от уровня
    constexpr static std::array arrLogType{
        "INFO", "WARNING", "ERROR","DEBUG", "FATAL"
    };

    switch (level) {
        case lvl::Info:

            break;
        case lvl::Warning:

            break;
        case lvl::Error:

            break;
    }

    ofs << message;
}

lrh::Logger::Logger(const std::string &fileName)
{
    ofs.open(fileName,  std::ios::app);

    if (not ofs.is_open()) {
        throw std::runtime_error("Could not open log file: " + fileName);
    }

}

lrh::Logger::~Logger() {
    //Закрываем файл и можно добавить
    //Закрывающее сообщение лог файла
    //TODO: Чекнуть как другие работяги закрывают лог файл
    ofs << "ВСЕ ДОЛЖНЫ ЗИГОВАТЬ";
}

std::string lrh::Logger::createFileName() {
    return {"log_.log"};
}

std::string lrh::Logger::currentDateTime() {
    /*const std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);*/

    return "test";
}

