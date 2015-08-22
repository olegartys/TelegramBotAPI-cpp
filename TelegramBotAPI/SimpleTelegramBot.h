//
// Created by olegartys on 18.08.15.
//

#ifndef TELEGRAMBOTTEST_TELEGRAMVKBOT_H
#define TELEGRAMBOTTEST_TELEGRAMVKBOT_H

#include <vector>
#include <string>

#include "ITelegramBot.h"
#include "ApiHelper.h"

/**
 * INFO: This class is simple implementation of ITelegramBot interface.
 * It has all basic methods to communicate with telegram bot API.
 *
 * IMPORTANT: If you want to implement your own telegram bot the easiest way is to ingerit this class and add new
 * functionality without thinking about implementation of basic communicate methods.
 * For exaplins what each method does see comments in ITelegramBot.h
 */
class SimpleTelegramBot : public TelegramBotAPI::ITelegramBot {
public:

    SimpleTelegramBot(const std::string& authToken) :
            m_AuthToken(authToken) { }

    virtual std::string getAuthToken() const final { return m_AuthToken; }

    ~SimpleTelegramBot() =default;

    TelegramBotAPI::types::User getMe() const override;

    std::vector<TelegramBotAPI::types::Update> getUpdates(const int32_t* offset =nullptr,
                                                          const int32_t* limit =nullptr,
                                                          const int32_t* timeout =nullptr) const override;

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

    TelegramBotAPI::types::Message sendVoice(const int32_t chat_id, const TelegramBotAPI::types::InputFile& audio,
                                             const int32_t* duration =nullptr,
                                             const int32_t* reply_to_message_id =nullptr,
                                             const std::string* serialized_reply_markup =nullptr) const override;

    TelegramBotAPI::types::Message sendLocation(const int32_t chat_id, const float latitude, const float longitude,
                                                const int32_t* reply_to_message_id =nullptr,
                                                const std::string* serialized_reply_markup =nullptr) const override;

    void sendChatAction(const int32_t chat_id, const ActionType action) const override;

    TelegramBotAPI::types::UserProfilePhotos getUserProfilePhotos(const int32_t user_id,
                                                                  const int32_t* offset =nullptr,
                                                                  const int32_t* limit =nullptr) const override;

protected:
    std::string m_AuthToken;
};

#endif //TELEGRAMBOTTEST_TELEGRAMVKBOT_H
