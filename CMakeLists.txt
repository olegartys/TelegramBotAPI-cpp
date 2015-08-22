cmake_minimum_required(VERSION 3.2)
project(TelegramBotTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("/usr/include/curl")

set(SOURCE_FILES main.cpp)
add_executable(TelegramBotTest ${SOURCE_FILES} TelegramBotAPI/ITelegramBot.h TelegramVKBot.cpp TelegramVKBot.h api_helper.h TelegramBotAPI/TelegramBotAPI_Types.cpp TelegramBotAPI/TelegramBotAPI_Types.h TelegramBotAPI/BadRequestError.cpp TelegramBotAPI/BadRequestError.h)

target_link_libraries (TelegramBotTest curl)
target_link_libraries (TelegramBotTest json-c)
