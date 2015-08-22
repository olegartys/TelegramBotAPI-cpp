#include <iostream>
#include "TelegramBotAPI/TelegramBotAPI_Types.h"
#include "TelegramVKBot.h"
#include "api_helper.h"
#include <curl/curl.h>

using namespace std;

const string BOT_TOKEN = "84458481:AAH46wJB2LtdSTBmQtlgbGj8zcOClg8Y85o";
const int32_t olegartys_id = 138168286;

int main()
{
    TelegramVKBot bot(BOT_TOKEN);

    try {

        vector<TelegramBotAPI::types::Update> v = bot.getUpdates();
        for(auto& i: v) {
            cout << i.message.chat.user.first_name << " : " << i.message.chat.user.id << endl;
        }
        int32_t chat_id = v[0].message.chat.user.id;

        //bot.sendMessage(olegartys_id, "212");
        TelegramBotAPI::types::Message m = bot.sendAudio(olegartys_id, TelegramBotAPI::types::InputFile("/home/olegartys/Music/Holy Shemp - Back Out On The Road.mp3"));

    } catch (TelegramBotAPI::BadRequestError& err) {
        cerr << err.what() << endl;
    }

    return 0;
}