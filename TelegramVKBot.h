//
// Created by olegartys on 18.08.15.
//

#ifndef TELEGRAMBOTTEST_TELEGRAMVKBOT_H
#define TELEGRAMBOTTEST_TELEGRAMVKBOT_H

#include "ITelegramBot.h"

class TelegramVKBot : public TelegramBotAPI::ITelegramBot {
public:
    TelegramVKBot(const std::string& authToken) { m_AuthToken = authToken; }

    TelegramBotAPI::types::User getMe() const override;
//    std::string sendMessage(const std::string& data) const override;
//    std::string sendQuery(const std::string& funcName) const override;
//
//    std::string getUpdates() const override;


    ~TelegramVKBot() =default;
};


#endif //TELEGRAMBOTTEST_TELEGRAMVKBOT_H
