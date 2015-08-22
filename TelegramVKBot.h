//
// Created by olegartys on 18.08.15.
//

#ifndef TELEGRAMBOTTEST_TELEGRAMVKBOT_H
#define TELEGRAMBOTTEST_TELEGRAMVKBOT_H

#include <vector>
#include "TelegramBotAPI/ITelegramBot.h"
#include "api_helper.h"

class TelegramVKBot : public TelegramBotAPI::ITelegramBot {
public:
    TelegramVKBot(const std::string& authToken) :
            m_AuthToken(authToken) { }

    TelegramBotAPI::types::User getMe() const override;

    std::vector<TelegramBotAPI::types::Update> getUpdates() const override;

    TelegramBotAPI::types::Message sendMessage(const int32_t chat_id, const std::string& text,
                                               const bool* disable_web_page_preview =nullptr,
                                               const int32_t* reply_to_message_id =nullptr,
                                               const string* serialized_reply_markup =nullptr) const override;

    TelegramBotAPI::types::Message forwardMessage(const int32_t chat_id,
                                                  const int32_t from_chat_id,
                                                  const int32_t message_id) const override;

    TelegramBotAPI::types::Message sendPhoto(const int32_t chat_id, const TelegramBotAPI::types::InputFile& photo,
                                             const string* caption =nullptr,
                                             const int32_t* reply_to_message_id =nullptr,
                                             const std::string* serialized_reply_markup =nullptr) const override;

    TelegramBotAPI::types::Message sendAudio(const int32_t chat_id, const TelegramBotAPI::types::InputFile& audio,
                                             const int32_t* duration =nullptr,
                                             const std::string* performer =nullptr,
                                             const std::string* title =nullptr,
                                             const int32_t* reply_to_message_id =nullptr,
                                             const std::string* serialized_reply_markup =nullptr) const override;

    TelegramBotAPI::types::Message sendDocument(const int32_t chat_id, const TelegramBotAPI::types::InputFile& document,
                                                const int32_t* reply_to_message_id =nullptr,
                                                const std::string* serialized_reply_markup =nullptr) const override;

    TelegramBotAPI::types::Message sendSticker(const int32_t chat_id, const TelegramBotAPI::types::InputFile& sticker,
                                               const int32_t* reply_to_message_id =nullptr,
                                               const std::string* serialized_reply_markup =nullptr) const override;

    TelegramBotAPI::types::Message sendVideo(const int32_t chat_id, const TelegramBotAPI::types::InputFile& video,
                                             const int32_t* duration =nullptr,
                                             const string* caption =nullptr,
                                             const int32_t* reply_to_message_id =nullptr,
                                             const std::string* serialized_reply_markup =nullptr) const override;

//    std::string sendMessage(const std::string& data) const override;
   // std::string sendQuery(const std::string& funcName) const;
//


    ~TelegramVKBot() =default;

protected:
    std::string m_AuthToken;
};

#endif //TELEGRAMBOTTEST_TELEGRAMVKBOT_H
