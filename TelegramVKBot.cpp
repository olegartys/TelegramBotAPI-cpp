//
// Created by olegartys on 18.08.15.
//

#include "TelegramVKBot.h"
#include "api_helper.h"
#include "TelegramBotAPI/TelegramBotAPI_Types.h"
#include <curl/curl.h>

using namespace std;

static size_t WriteMemoryCallback(void* content, size_t size, size_t nmemb, void* resultData) {
    char* t_Content = (char*)content;
    string* t_Result = (string*)resultData;

    *t_Result = t_Content;

    return size * nmemb;
}

TelegramBotAPI::types::User TelegramVKBot::getMe() const {

    const string queryFuncName = "getMe";
    const string jsonString{};

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, string(baseURL+this->m_AuthToken+"/"+queryFuncName).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&jsonString);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return TelegramBotAPI::types::User(jsonString);
}

//
//
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
