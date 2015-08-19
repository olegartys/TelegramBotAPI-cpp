//
// Created by olegartys on 19.08.15.
//

#ifndef TELEGRAMBOTTEST_BADREQUESTERROR_H
#define TELEGRAMBOTTEST_BADREQUESTERROR_H


#include <stdexcept>

namespace TelegramBotAPI {

    /**
     * This class implements bad request exception type.
     * m_Description is a description of error that is sent by telegram, m_ErrCode - it's code.
     */
    class BadRequestError : public std::runtime_error {

        std::string m_Description;
        int32_t m_ErrCode;

    public:
        
        static const std::string UnknownErrorMsg;
        static const int32_t UnknownErrorCode;


        explicit BadRequestError(const std::string& description, const int32_t errCode) :
            std::runtime_error(description), m_Description(description), m_ErrCode(errCode) { }

        const char* what() const throw() { return m_Description.c_str(); }
        const int32_t getErrCode() const { return m_ErrCode; }
    };

}

#endif //TELEGRAMBOTTEST_BADREQUESTERROR_H
