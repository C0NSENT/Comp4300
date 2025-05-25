//
// Created by consent_ on 21/05/25.
//

#include "Logger.hpp"

#include <ctime>

lrh::Logger & lrh::Logger::instance() {
}

void lrh::Logger::write(Level level, const std::string &message) {
}

lrh::Logger::Logger(const std::string &fileName) {
}

lrh::Logger::~Logger() {
    //Закрываем файл и можно добавить
    //Закрывающее сообщение лог файла
    //TODO: Чекнуть как другие работяги закрывают лог файл
}

std::string lrh::Logger::createFileName(const std::string &currentDateTime) {
}

std::string lrh::Logger::currentDateTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);


}

