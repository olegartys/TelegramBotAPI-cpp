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
#include "BadRequestError.h"

namespace TelegramBotAPI {

    // Describes types that are using in telegram BOT api. All data telegram transfer in a JSON,
    // so all the constructors of classes in that namespace parses JSON.
    namespace types {

        // FIXME: should i use free to delete jobj and result?
        struct User {

            User(const std::string& jsonString) {
                // Create main json parse object
                json_object* jobj = json_tokener_parse(jsonString.c_str());

                // Get "ok" field from json tree
                json_object* ok;
                if (!json_object_object_get_ex(jobj, "ok", &ok)) {
                    // If message from telegram doesn't conatin "ok" field
                    throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                          TelegramBotAPI::BadRequestError::UnknownErrorCode);
                } else {
                    // Getting meaning of "ok" field
                    json_bool res = json_object_get_boolean(ok);

                    // If it contains "true" than get data from "result"
                    if (res) {

                        json_object* result;

                        if (!json_object_object_get_ex(jobj, "result", &result)) {
                            throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                                  TelegramBotAPI::BadRequestError::UnknownErrorCode);
                        } else {
                            // Going through "result" field and getting target values
                            json_object_object_foreach(result, key, val) {
                                if      (!strcmp(key, "first_name")) first_name = json_object_get_string(val);
                                else if (!strcmp(key, "last_name"))  last_name = json_object_get_string(val);
                                else if (!strcmp(key, "username"))   username = json_object_get_string(val);
                                else if (!strcmp(key, "id"))         id = json_object_get_int(val);
                            }
                        }
                    // If "ok" field is false
                    } else {
                        json_object* error_code, *description;
                        json_bool t1 = json_object_object_get_ex(jobj, "error_code", &error_code);
                        json_bool t2 = json_object_object_get_ex(jobj, "description", &description);

                        if (t1 != 0 && t2 != 0) {
                            throw TelegramBotAPI::BadRequestError(json_object_get_string(description),
                                                                  json_object_get_int(error_code));
                        } else {
                            throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                            TelegramBotAPI::BadRequestError::UnknownErrorCode);
                        }
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