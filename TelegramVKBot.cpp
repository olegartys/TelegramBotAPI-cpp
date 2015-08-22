//
// Created by olegartys on 18.08.15.
//

#include "TelegramVKBot.h"
#include "api_helper.h"
#include <curl/curl.h>
#include <map>

using namespace TelegramBotAPI::types;
using namespace std;


static size_t WriteMemoryCallback(void* content, size_t size, size_t nmemb, void* resultData) {

    char* t_Content = (char*)content;
    string* t_Result = (string*)resultData;

    *t_Result = t_Content;

    return size * nmemb;
}


static string sendQuery(const string& url, const pair<string, InputFile>* data =nullptr) {

    string jsonString{};

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&jsonString);

        // Adding POST data to a request body
        if (data != nullptr) {
            struct curl_httppost* post = nullptr;
            struct curl_httppost* last = nullptr;


            curl_formadd(&post, &last,
                         CURLFORM_COPYNAME, data->first.c_str(),
                         CURLFORM_FILE, data->second.file_name.c_str(),
                         CURLFORM_END);

            curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        }
        res = curl_easy_perform(curl);
        std::cout << jsonString << endl;
        curl_easy_cleanup(curl);
    }

    return jsonString;
}

/**********************************************************************************************************************/
/** There are helper functions that just help parse server response and were created to prevent code copying, cause  **/
/** code them containing should be in constructor of every object to provide correct error handling.                 **/
/**********************************************************************************************************************/

static bool isResponseValid(json_object* jobj) {
    return json_object_object_get_ex(jobj, "ok", nullptr);
}

/**
 * Check whether "ok" field is true.
 */
static bool isRequestResultOK(json_object* jobj) {

    json_object* ok;
    json_object_object_get_ex(jobj, "ok", &ok);

    return json_object_get_boolean(ok);
}

/**
 * Handler for bad request. See isResponseValid function above.
 */
static void h_ResponseNotValid() {
    throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                          TelegramBotAPI::BadRequestError::UnknownErrorCode);
}

/**
 * Handler for situation if "ok" field is false. See isRequestResultOK function above.
 */
static void h_RequestOkIsFalse(json_object* jobj) {

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
/**********************************************************************************************************************/


User TelegramVKBot::getMe() const {

    const string queryFuncName = "getMe"; // Name of function to send to Telegram API

    // Send query to telegram API and get the response
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName);
    const string jsonResponseString = sendQuery(queryString);

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                // Constructing object from "result" of the telegram response
                return User(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }
}


vector<Update> TelegramVKBot::getUpdates() const {

    const string queryFuncName = "getUpdates";

    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName);
    const string jsonResponseString = sendQuery(queryString);

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                int resultArrayLen = json_object_array_length(result);
                vector<Update> resultVector(resultArrayLen);
                for (int i = 0; i < resultArrayLen; ++i) {
                    json_object* jval = json_object_array_get_idx(result, i);
                    resultVector[i] = move(Update(json_object_to_json_string(jval)));
                }

                return resultVector;
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }
}


Message TelegramVKBot::sendMessage(const int32_t chat_id, const std::string& text,
                                           const bool* disable_web_page_preview,
                                           const int32_t* reply_to_message_id,
                                           const string* serialized_reply_markup) const {

    const string queryFuncName = "sendMessage";

    string queryParams = "chat_id=" + to_string(chat_id) + "&" + "text=" + text;
    if (disable_web_page_preview != nullptr)
        queryParams += "&disable_web_page_preview=" + to_string(*disable_web_page_preview);
    if (reply_to_message_id != nullptr)
        queryParams += "&reply_to_message_id=" + to_string(*reply_to_message_id);
    if (serialized_reply_markup != nullptr)
        queryParams += "&reply_markup=" + *serialized_reply_markup;
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString);

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }

}


Message TelegramVKBot::forwardMessage(const int32_t chat_id, const int32_t from_chat_id,
                                      const int32_t message_id) const {

    const string queryFuncName = "forwardMessage";

    const string queryParams = "chat_id=" + to_string(chat_id) + "&from_chat_id=" + to_string(from_chat_id) + "&message_id=" + to_string(message_id);
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString);

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }

}


Message TelegramVKBot::sendPhoto(const int32_t chat_id, const InputFile& photo,
                                 const string* caption,
                                 const int32_t* reply_to_message_id,
                                 const std::string* serialized_reply_markup) const {

    const string queryFuncName = "sendPhoto";

    string queryParams = "chat_id=" + to_string(chat_id);
    if (caption != nullptr)
        queryParams += "&caption=" + *caption;
    if (reply_to_message_id != nullptr)
        queryParams += "&reply_to_message_id=" + to_string(*reply_to_message_id);
    if (serialized_reply_markup != nullptr)
        queryParams += "&serialized_reply_markup=" + *serialized_reply_markup;
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString, new pair<string, InputFile>("photo", photo));

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }
}

Message TelegramVKBot::sendAudio(const int32_t chat_id, const TelegramBotAPI::types::InputFile &audio,
                                 const int32_t *duration, const string *performer, const string *title,
                                 const int32_t *reply_to_message_id, const string *serialized_reply_markup) const {
    const string queryFuncName = "sendAudio";

    string queryParams = "chat_id=" + to_string(chat_id);
    if (duration != nullptr)
        queryParams += "&duration=" + to_string(*duration);
    if (performer != nullptr)
        queryParams += "&performer=" + *performer;
    if (title != nullptr)
        queryParams += "&title=" + *title;
    if (reply_to_message_id != nullptr)
        queryParams += "&reply_to_message_id=" + to_string(*reply_to_message_id);
    if (serialized_reply_markup != nullptr)
        queryParams += "&serialized_reply_markup=" + *serialized_reply_markup;
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString, new pair<string, InputFile>("audio", audio));
    std::cout << "Here\n";

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }
}


Message TelegramVKBot::sendDocument(const int32_t chat_id, const TelegramBotAPI::types::InputFile &document,
                                    const int32_t *reply_to_message_id, const string *serialized_reply_markup) const {

    const string queryFuncName = "sendDocument";

    string queryParams = "chat_id=" + to_string(chat_id);
    if (reply_to_message_id != nullptr)
        queryParams += "&reply_to_message_id=" + to_string(*reply_to_message_id);
    if (serialized_reply_markup != nullptr)
        queryParams += "&serialized_reply_markup=" + *serialized_reply_markup;
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString, new pair<string, InputFile>("document", document));
    std::cout << "Here\n";

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }
}


Message TelegramVKBot::sendSticker(const int32_t chat_id, const TelegramBotAPI::types::InputFile &sticker,
                                   const int32_t *reply_to_message_id, const string *serialized_reply_markup) const {

    const string queryFuncName = "sendSticker";

    string queryParams = "chat_id=" + to_string(chat_id);
    if (reply_to_message_id != nullptr)
        queryParams += "&reply_to_message_id=" + to_string(*reply_to_message_id);
    if (serialized_reply_markup != nullptr)
        queryParams += "&serialized_reply_markup=" + *serialized_reply_markup;
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString, new pair<string, InputFile>("sticker", sticker));
    std::cout << "Here\n";

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }
}


Message TelegramVKBot::sendVideo(const int32_t chat_id, const TelegramBotAPI::types::InputFile &video,
                                 const int32_t *duration, const string *caption, const int32_t *reply_to_message_id,
                                 const string *serialized_reply_markup) const {

    const string queryFuncName = "sendVideo";

    string queryParams = "chat_id=" + to_string(chat_id);
    if (duration != nullptr)
        queryParams += "&duration=" + to_string(*duration);
    if (caption != nullptr)
        queryParams += "&caption=" + *caption;
    if (reply_to_message_id != nullptr)
        queryParams += "&reply_to_message_id=" + to_string(*reply_to_message_id);
    if (serialized_reply_markup != nullptr)
        queryParams += "&serialized_reply_markup=" + *serialized_reply_markup;
    const string queryString = string(baseURL+this->m_AuthToken+"/"+queryFuncName+"?"+queryParams);
    const string jsonResponseString = sendQuery(queryString, new pair<string, InputFile>("video", video));

    json_object* jobj = json_tokener_parse(jsonResponseString.c_str());
    // Check response for correctness
    if (isResponseValid(jobj)) {
        // Check response result
        if (isRequestResultOK(jobj)) {
            json_object* result;

            if (!json_object_object_get_ex(jobj, "result", &result)) {
                throw TelegramBotAPI::BadRequestError(TelegramBotAPI::BadRequestError::UnknownErrorMsg,
                                                      TelegramBotAPI::BadRequestError::UnknownErrorCode);
            } else {
                return Message(json_object_to_json_string(result));
            }
        } else {
            h_RequestOkIsFalse(jobj);
        }
    } else {
        h_ResponseNotValid();
    }

}




//std::string TelegramVKBot::sendQuery(const std::string& funcName) const {
//    const string jsonString{};
//
//    CURL *curl = curl_easy_init();
//    if(curl) {
//        CURLcode res;
//        curl_easy_setopt(curl, CURLOPT_URL, string(baseURL+this->m_AuthToken+"/"+funcName).c_str());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&jsonString);
//        res = curl_easy_perform(curl);
//        curl_easy_cleanup(curl);
//    }
//
//    return jsonString;
//}
//
//std::string TelegramVKBot::sendMessage(const std::string &data) const {
//    const string jsonString{};
//
//    CURL *curl = curl_easy_init();
//    if(curl) {
//        CURLcode res;
//        curl_easy_setopt(curl, CURLOPT_URL, string(baseURL+this->m_AuthToken+"/"+"sendMessage").c_str());
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&jsonString);
//        res = curl_easy_perform(curl);
//        curl_easy_cleanup(curl);
//    }
//
//    return jsonString;
//}
//
//
//std::string TelegramVKBot::getUpdates() const {
//    const string jsonString{};
//
//    CURL *curl = curl_easy_init();
//    if(curl) {
//        CURLcode res;
//        curl_easy_setopt(curl, CURLOPT_URL, string(baseURL+this->m_AuthToken+"/"+"getUpdates").c_str());
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&jsonString);
//        res = curl_easy_perform(curl);
//        curl_easy_cleanup(curl);
//    }
//
//    return jsonString;
//}
