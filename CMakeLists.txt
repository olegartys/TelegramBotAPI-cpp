cmake_minimum_required(VERSION 3.2)
project(TelegramBotTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("/usr/include/curl")

set(SOURCE_FILES main.cpp)
add_executable(TelegramBotTest ${SOURCE_FILES} TelegramBotAPI/ITelegramBot.h TelegramBotAPI/SimpleTelegramBot.cpp TelegramBotAPI/SimpleTelegramBot.h TelegramBotAPI/ApiHelper.cpp TelegramBotAPI/ApiHelper.h TelegramBotAPI/TelegramBotAPI_Types.cpp TelegramBotAPI/TelegramBotAPI_Types.h TelegramBotAPI/BadRequestError.cpp TelegramBotAPI/BadRequestError.h TelegramBotAPI/TelegramBotAPI.h)

target_link_libraries (TelegramBotTest curl)
target_link_libraries (TelegramBotTest json-c)
