#include <iostream>
#include "TelegramBotAPI_Types.h"
#include "TelegramVKBot.h"

using namespace std;

const string BOT_TOKEN = "84458481:AAH46wJB2LtdSTBmQtlgbGj8zcOClg8Y85o";

int main()
{
    TelegramVKBot bot(BOT_TOKEN);
    TelegramBotAPI::types::User userInfo = bot.getMe();

    cout << userInfo.first_name;

    return 0;
}