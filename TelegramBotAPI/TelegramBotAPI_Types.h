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

namespace TelegramBotAPI {

    // Describes types that are using in telegram BOT api. All data telegram transfer in a JSON,
    // so all the constructors of classes in that namespace parses JSON.
    namespace types {

        struct User {

            User(const std::string& jsonString) {
                // Create main json parse object
                json_object* jobj = json_tokener_parse(jsonString.c_str());

                // Get "result" field from json tree
                json_object* result;
                if (!json_object_object_get_ex(jobj, "result", &result)) {
                    // FIXME: should i user free to delete jobj and result?
                    throw std::exception();
                } else {
                    // Going through "result" field and getting target values
                    json_object_object_foreach(result, key, val) {
                        if      (!strcmp(key, "first_name")) first_name = json_object_get_string(val);
                        else if (!strcmp(key, "last_name"))  last_name = json_object_get_string(val);
                        else if (!strcmp(key, "username"))   username = json_object_get_string(val);
                        else if (!strcmp(key, "id"))         id = json_object_get_int(val);
                    }
                }
            }

            int32_t id;
            std::string first_name;
            std::string last_name;
            std::string username;
        };

        struct GroupChar {

        };

        struct Message {};

        struct PhotoSize {};

        struct Audio {};

        struct Document {};

        struct Sticker {};

        struct Video {};

        struct Voice {};

        struct Contact {};

        struct Location {};

        struct Update {};

        struct InputFile {};

        struct UserProfilePhotos {};

        struct ReplyKeyboardMarkup {};

        struct ReplyKeyboardHide {};

        struct ForceReply {};
    }

}

#endif