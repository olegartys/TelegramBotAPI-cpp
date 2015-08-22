//
// Created by olegartys on 18.08.15.
//

#ifndef TELEGRAMBOTTEST_ITELEGRAMBOT_H
#define TELEGRAMBOTTEST_ITELEGRAMBOT_H

#include <vector>
#include <string>
#include "TelegramBotAPI_Types.h"

namespace TelegramBotAPI {

    /**
     * Interface for a telegram bot functionality.
     * Implements all the available methods fro official telegram API.
     * Each method should send a query to telegram server with the query function name equvivalent to the name of
     * the method.
     */
    class ITelegramBot {
    public:

        /**
         * A simple method for testing your bot's auth token.
         * Requires no parameters.
         * Returns basic information about the bot in form of a User object.
         */
        virtual TelegramBotAPI::types::User getMe() const =0;

        /**
         * Use this method to receive incoming updates using long polling. An Array of Update objects is returned.
         */
        virtual std::vector<TelegramBotAPI::types::Update> getUpdates() const =0;

        /**
         * Use this method to send text messages. On success, the sent Message is returned.
         * Parameters that are passing by pointer are Optional (for more info see official Telegram bot API).
         * //FIXME: last parameter should have ReplyKeyboardMarkup, ReplyKeyboardHide or ForceReply type, but i can't overload functions
         * serialized_reply_markup is json serialized ReplyKeyboardMarkup, ReplyKeyboardHide or ForceReply
         */
        virtual TelegramBotAPI::types::Message sendMessage(const int32_t chat_id, const std::string& text,
                                                           const bool* disable_web_page_preview =nullptr,
                                                           const int32_t* reply_to_message_id =nullptr,
                                                           const std::string* serialized_reply_markup =nullptr) const =0;

//        virtual TelegramBotAPI::types::Message sendMessage(const int32_t chat_id, const std::string& text,
//                                                           const bool* disable_web_page_preview =nullptr,
//                                                           const int32_t* reply_to_message_id =nullptr,
//                                                           const TelegramBotAPI::types::ReplyKeyboardHide* reply_markup =nullptr) const =0;
//
//        virtual TelegramBotAPI::types::Message sendMessage(const int32_t chat_id, const std::string& text,
//                                                           const bool* disable_web_page_preview =nullptr,
//                                                           const int32_t* reply_to_message_id =nullptr,
//                                                           const TelegramBotAPI::types::ForceReply* reply_markup =nullptr) const =0;

        /**
         * Use this method to forward messages of any kind. On success, the sent Message is returned.
         */
        virtual TelegramBotAPI::types::Message forwardMessage(const int32_t chat_id,
                                                              const int32_t from_chat_id,
                                                              const int32_t message_id) const =0;

        /**
         * Use this method to send photos. On success, the sent Message is returned.
         */
        virtual TelegramBotAPI::types::Message sendPhoto(const int32_t chat_id, const TelegramBotAPI::types::InputFile& photo,
                                                         const string* caption =nullptr,
                                                         const int32_t* reply_to_message_id =nullptr,
                                                         const std::string* serialized_reply_markup =nullptr) const =0;

        /**
         * Use this method to send audio files, if you want Telegram clients to display them in the music player.
         */
        virtual TelegramBotAPI::types::Message sendAudio(const int32_t chat_id, const TelegramBotAPI::types::InputFile& audio,
                                                         const int32_t* duration =nullptr,
                                                         const std::string* performer =nullptr,
                                                         const std::string* title =nullptr,
                                                         const int32_t* reply_to_message_id =nullptr,
                                                         const std::string* serialized_reply_markup =nullptr) const =0;

        /**
         * Use this method to send general files.
         */
        virtual TelegramBotAPI::types::Message sendDocument(const int32_t chat_id, const TelegramBotAPI::types::InputFile& document,
                                                            const int32_t* reply_to_message_id =nullptr,
                                                            const std::string* serialized_reply_markup =nullptr) const =0;

        /**
         * Use this method to send .webp stickers.
         */
        virtual TelegramBotAPI::types::Message sendSticker(const int32_t chat_id, const TelegramBotAPI::types::InputFile& sticker,
                                                           const int32_t* reply_to_message_id =nullptr,
                                                           const std::string* serialized_reply_markup =nullptr) const =0;


        virtual TelegramBotAPI::types::Message sendVideo(const int32_t chat_id, const TelegramBotAPI::types::InputFile& video,
                                                         const int32_t* duration =nullptr,
                                                         const string* caption =nullptr,
                                                         const int32_t* reply_to_message_id =nullptr,
                                                         const std::string* serialized_reply_markup =nullptr) const =0;
//        virtual std::string sendQuery(const std::string& funcName) const =0;

        virtual ~ITelegramBot() =default;

    };

}



#endif //TELEGRAMBOTTEST_ITELEGRAMBOT_H
