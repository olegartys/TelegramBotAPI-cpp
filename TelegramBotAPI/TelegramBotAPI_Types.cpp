//
// Created by olegartys on 19.08.15.
//

// FIXME: should i use free to delete jobj and result?


#include "TelegramBotAPI_Types.h"

using namespace TelegramBotAPI::types;
using namespace std;


User::User(const string& jsonString) {
    // Going through "result" field and getting target values
    json_object_object_foreach(json_tokener_parse(jsonString.c_str()), key, val) {
        if      (!strcmp(key, "first_name")) first_name = json_object_get_string(val);
        else if (!strcmp(key, "last_name"))  last_name  = json_object_get_string(val);
        else if (!strcmp(key, "username"))   username   = json_object_get_string(val);
        else if (!strcmp(key, "id"))         id         = json_object_get_int(val);
    }
}


GroupChat::GroupChat(const string&jsonString) {
    json_object_object_foreach(json_tokener_parse(jsonString.c_str()), key, val) {
        if      (!strcmp(key, "id"))         id      = json_object_get_int(val);
        else if (!strcmp(key, "title"))      title   = json_object_get_string(val);
    }
}


Message::Message(const std::string &jsonString) {
    json_object* result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "message_id"))            message_id            = json_object_get_int(val);
        else if (!strcmp(key, "from"))                  from                  = User(json_object_to_json_string(val));
        else if (!strcmp(key, "date"))                  date                  = json_object_get_int(val);
        else if (!strcmp(key, "chat")) {
            json_object* t;

            // if "chat" field is GroupChat type, than it will have "title" field, else it is User type.
            json_bool isGroupChat = json_object_object_get_ex(result, "title", &t);

            // If it is GroupChat parse group_char object, else user object.
            if (isGroupChat)                            chat.group_chat       = GroupChat(json_object_to_json_string(val));
            else                                        chat.user             = User(json_object_to_json_string(val));
        }
        else if (!strcmp(key, "forward_from"))          forward_from          = User(json_object_to_json_string(val));
        else if (!strcmp(key, "forward_date"))          forward_date          = json_object_get_int(val);
        else if (!strcmp(key, "reply_to_message"))      reply_to_message      = new Message(json_object_to_json_string(val));
        else if (!strcmp(key, "text"))                  text                  = json_object_get_string(val);
        else if (!strcmp(key, "audio"))                 audio                 = Audio(json_object_get_string(val));
        else if (!strcmp(key, "document"))              document              = Document(json_object_get_string(val));
        else if (!strcmp(key, "photo")) {
            int arrayLen = json_object_array_length(val);
            for (int i = 0; i < arrayLen; ++i)
                                                        photo.emplace_back(PhotoSize(json_object_to_json_string(json_object_array_get_idx(val, i))));
        }
        else if (!strcmp(key, "sticker"))               sticker               = Sticker(json_object_get_string(val));
        else if (!strcmp(key, "video"))                 video                 = Video(json_object_get_string(val));
        else if (!strcmp(key, "voice"))                 voice                 = Voice(json_object_get_string(val));
        else if (!strcmp(key, "caption"))               caption               = json_object_get_string(val);
        else if (!strcmp(key, "contact"))               contact               = Contact(json_object_to_json_string(val));
        else if (!strcmp(key, "location"))              location              = Location(json_object_to_json_string(val));
        else if (!strcmp(key, "new_char_participant"))  new_char_participant  = User(json_object_to_json_string(val));
        else if (!strcmp(key, "left_chat_participant")) left_chat_participant = User(json_object_to_json_string(val));
        else if (!strcmp(key, "new_chat_title"))        new_chat_title        = json_object_get_string(val);
        else if (!strcmp(key, "new_chat_photo")) {
            int arrayLen = json_object_array_length(val);
            for (int i = 0; i < arrayLen; ++i)
                                                        new_chat_photo[i]     = move(PhotoSize(json_object_to_json_string(json_object_array_get_idx(val, i))));
        }
        else if (!strcmp(key, "delete_chat_photo"))     delete_chat_photo     = json_object_get_boolean(val);
        else if (!strcmp(key, "group_chat_created"))    group_chat_created    = json_object_get_boolean(val);
    }
}


Update::Update(const string& jsonString) {
    json_object* result = json_tokener_parse(jsonString.c_str());
    // Going through "result" field and getting target values
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "update_id"))  update_id = json_object_get_int(val);
        else if (!strcmp(key, "message"))    message   = Message(json_object_to_json_string(val));
    }
}


Audio::Audio(const string& jsonString) {
    json_object* result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "file_id"))   file_id   = json_object_get_string(val);
        else if (!strcmp(key, "duration"))  duration  = json_object_get_int(val);
        else if (!strcmp(key, "performer")) performer = json_object_get_int(val);
        else if (!strcmp(key, "title"))     title     = json_object_get_string(val);
        else if (!strcmp(key, "mime_type")) mime_type = json_object_get_string(val);
        else if (!strcmp(key, "file_size")) file_size = json_object_get_int(val);
    }
}

Document::Document(const std::string &jsonString) {
    json_object* result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "file_id"))   file_id   = json_object_get_int(val);
        else if (!strcmp(key, "thumb"))     thumb     = PhotoSize(json_object_to_json_string(val));
        else if (!strcmp(key, "file_name")) file_name = json_object_get_string(val);
        else if (!strcmp(key, "mime_type")) mime_type = json_object_get_string(val);
        else if (!strcmp(key, "file_size")) file_size = json_object_get_int(val);
    }
}

Sticker::Sticker(const std::string &jsonString) {
    json_object *result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if (!strcmp(key, "file_id"))        file_id   = json_object_get_int(val);
        else if (!strcmp(key, "width"))     width     = json_object_get_int(val);
        else if (!strcmp(key, "height"))    height    = json_object_get_int(val);
        else if (!strcmp(key, "thumb"))     thumb     = PhotoSize(json_object_to_json_string(val));
        else if (!strcmp(key, "file_size")) file_size = json_object_get_int(val);
    }
}

Video::Video(const std::string &jsonString) {
    json_object *result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "file_id"))   file_id   = json_object_get_int(val);
        else if (!strcmp(key, "width"))     width     = json_object_get_int(val);
        else if (!strcmp(key, "height"))    height    = json_object_get_int(val);
        else if (!strcmp(key, "duration"))  duration  = json_object_get_int(val);
        else if (!strcmp(key, "thumb"))     thumb     = PhotoSize(json_object_to_json_string(val));
        else if (!strcmp(key, "mime_type")) mime_type = json_object_get_string(val);
        else if (!strcmp(key, "file_size")) file_size = json_object_get_int(val);
    }
}

Voice::Voice(const std::string &jsonString) {
    json_object *result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "file_id"))   file_id   = json_object_get_int(val);
        else if (!strcmp(key, "duration"))  duration  = json_object_get_int(val);
        else if (!strcmp(key, "mime_type")) mime_type = json_object_get_string(val);
        else if (!strcmp(key, "file_size")) file_size = json_object_get_int(val);
    }
}

Contact::Contact(const std::string &jsonString) {
    json_object *result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "phone_number")) phone_number = json_object_get_string(val);
        else if (!strcmp(key, "first_name"))   first_name   = json_object_get_string(val);
        else if (!strcmp(key, "last_name"))    last_name    = json_object_get_string(val);
        else if (!strcmp(key, "user_id"))      user_id      = json_object_get_int(val);
    }
}

Location::Location(const std::string &jsonString) {
    json_object *result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "longitude")) longitude = json_object_get_double(val);
        else if (!strcmp(key, "latitude"))  latitude  = json_object_get_double(val);
    }
}

PhotoSize::PhotoSize(const std::string &jsonString) noexcept {
    json_object *result = json_tokener_parse(jsonString.c_str());
    json_object_object_foreach(result, key, val) {
        if      (!strcmp(key, "file_id"))   file_id   = json_object_get_string(val);
        else if (!strcmp(key, "width"))     width     = json_object_get_int(val);
        else if (!strcmp(key, "height"))    height    = json_object_get_int(val);
        else if (!strcmp(key, "file_size")) file_size = json_object_get_int(val);
    }
}

ReplyKeyboardMarkup::ReplyKeyboardMarkup(const vector<vector<string> >& keyboard,
                                         const bool resize_keyboard,
                                         const bool one_time_keyboard,
                                         const bool selective) {

    json_object* jobj = json_object_new_object();
    json_object* jMainArray = json_object_new_array();

    for (auto& i: keyboard) {
        json_object* jArray = json_object_new_array();
        for (const string& s: i) {
            json_object* jString = json_object_new_string(s.c_str());
            json_object_array_add(jArray, jString);
        }
        json_object_array_add(jMainArray, jArray);
    }

    json_object_object_add(jobj, "keyboard", jMainArray);
    json_object_object_add(jobj, "resize_keyboard", json_object_new_boolean(resize_keyboard));
    json_object_object_add(jobj, "one_time_keyboard", json_object_new_boolean(one_time_keyboard));
    json_object_object_add(jobj, "selective", json_object_new_boolean(selective));


    serializedString = json_object_to_json_string(jobj);

}

ReplyKeyboardHide::ReplyKeyboardHide(const bool selective) {

    json_object* jobj = json_object_new_object();
    json_object_object_add(jobj, "selective", json_object_new_boolean(selective));
    json_object_object_add(jobj, "hide_keyboard", json_object_new_boolean(hide_keyboard));

    serializedString = json_object_to_json_string(jobj);

}

ForceReply::ForceReply(const bool selective) {

    json_object* jobj = json_object_new_object();
    json_object_object_add(jobj, "selective", json_object_new_boolean(selective));
    json_object_object_add(jobj, "force_reply", json_object_new_boolean(force_reply));

    serializedString = json_object_to_json_string(jobj);
}
