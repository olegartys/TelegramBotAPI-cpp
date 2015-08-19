//
// Created by olegartys on 18.08.15.
//

#ifndef TELEGRAMBOTTEST_ITELEGRAMBOT_H
#define TELEGRAMBOTTEST_ITELEGRAMBOT_H

#include <string>
#include "TelegramBotAPI_Types.h"

namespace TelegramBotAPI {

    class ITelegramBot {
    public:

        virtual TelegramBotAPI::types::User getMe() const =0;
//        virtual std::string sendMessage(const std::string& data) const =0;
//        virtual std::string sendQuery(const std::string& funcName) const =0;

        virtual ~ITelegramBot() =default;

    protected:
        std::string m_AuthToken;
    };

}



#endif //TELEGRAMBOTTEST_ITELEGRAMBOT_H
