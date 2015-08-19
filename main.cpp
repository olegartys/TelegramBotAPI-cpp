#include <iostream>
#include "TelegramBotAPI/TelegramBotAPI_Types.h"
#include "TelegramVKBot.h"

using namespace std;

const string BOT_TOKEN = "84458481:AAH46wJB2LtdSTBmQtlgbGj8zcOClg8Y85o";

int main()
{
    TelegramVKBot bot(BOT_TOKEN);
    try {
        TelegramBotAPI::types::User userInfo = bot.getMe();
        cout << userInfo.first_name << " " << userInfo.last_name << " " << userInfo.id << " " << userInfo.username << endl;
    } catch (TelegramBotAPI::BadRequestError& err) {
        cerr << err.what() << endl;
    }

    return 0;
}