//
// Created by olegartys on 19.08.15.
//

#ifndef TELEGRAMAPI_TYPES
#define TELEGRAMAPI_TYPES

#include <sys/types.h>
#include <string>
#include <json-c/json.h>
#include <iostream>
#include <cstring>
#include <vector>
#include "BadRequestError.h"

using std::string;
using std::vector;

namespace TelegramBotAPI {

    // Describes types that are using in telegram BOT api. All data telegram transfer in JSON,
    // so all the constructors of struct's in that namespace parses JSON.
    namespace types {

        struct User {

            User() =default;
            User(const string& jsonString);

            int32_t id;
            string first_name;
            string last_name;
            string username;
        };

        struct GroupChat {

            GroupChat() =default;
            GroupChat(const string& jsonString);

            int32_t id;
            string title;
        };


        struct PhotoSize {

            PhotoSize() =default;
            PhotoSize(const string& jsonString);

            string file_id;
            int32_t width;
            int32_t height;
            int32_t file_size;

        };

        struct Audio {

            Audio() =default;
            Audio(const string& jsonString);

            string file_id;
            int32_t duration;
            string performer;
            string title;
            string mime_type;
            int32_t file_size;

        };

        struct Document {

            Document() =default;
            Document(const string& jsonString);

            string file_id;
            PhotoSize thumb;
            string file_name;
            string mime_type;
            int32_t file_size;

        };

        struct Sticker {

            Sticker() =default;
            Sticker(const string& jsonString);

            string file_id;
            int32_t width;
            int32_t height;
            PhotoSize thumb;
            int32_t file_size;

        };

        struct Video {

            Video() =default;
            Video(const string& jsonString);

            string file_id;
            int32_t width;
            int32_t height;
            int32_t duration;

            PhotoSize thumb;
            string mime_type;
            int32_t file_size;

        };

        struct Voice {

            Voice() =default;
            Voice(const string& jsonString);

            string file_id;
            int32_t duration;
            string mime_type;
            int32_t file_size;
        };

        struct Contact {

            Contact() =default;
            Contact(const string& jsonString);

            string phone_number;
            string first_name;
            string last_name;
            int32_t user_id;

        };

        struct Location {

            Location() =default;
            Location(const string& jsonString);

            double longitude;
            double latitude;
        };

        struct Message {

            Message() =default;
            Message(const string& jsonString);
            //~Message() { if (reply_to_message != nullptr) delete reply_to_message; };

            int32_t                message_id;
            User                   from;
            int32_t                date;

            // FIXME: why i can't use union here?
            // Conversation the message belongs to — user in case
            // of a private message, GroupChat in case of a group
            struct {
                User user;
                GroupChat group_chat;
            } chat;

            User                   forward_from;
            int32_t                forward_date;
            Message*               reply_to_message{};
            string                 text;
            Audio                  audio;
            Document               document;
            vector<PhotoSize>      photo;
            Sticker                sticker;
            Video                  video;
            Voice                  voice;
            string                 caption;
            Contact                contact;
            Location               location;
            User                   new_char_participant;
            User                   left_chat_participant;
            string                 new_chat_title;
            vector<PhotoSize>      new_chat_photo;
            bool                   delete_chat_photo;
            bool                   group_chat_created;

        };

        struct Update {

            Update() =default;
            Update(const string& jsonString);

            int32_t update_id;
            Message message{};
        };

        struct InputFile {

            InputFile(const string& fileName) :
                file_name(fileName) { }

            string file_name;
            
        };

        struct UserProfilePhotos {

            UserProfilePhotos(const string& jsonString);

            int32_t total_count;
            vector<vector<PhotoSize>> photos;

        };

        struct ReplyKeyboardMarkup {

            ReplyKeyboardMarkup(const vector<vector<string> >& keyboard,
                                const bool resize_keyboard =false,
                                const bool one_time_keyboard =false,
                                const bool selective =false);

            vector<vector<string> > keyboard;
            bool resize_keyboard;
            bool one_time_keyboard;
            bool selective;

            string serializedString;

        };

        struct ReplyKeyboardHide {

            ReplyKeyboardHide(const bool selective =false);

            const bool hide_keyboard = true;
            bool selective;

            string serializedString;

        };

        struct ForceReply {

            ForceReply(const bool selective =false);

            const bool force_reply = true;
            bool selective;

            string serializedString;

        };
    }

}

#endif