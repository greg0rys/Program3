//
// Created by shene on 2/17/2023.
//

#ifndef PROGRAM3_MESSAGE_H
#define PROGRAM3_MESSAGE_H

#include "Contact.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <array>
using namespace std;

class Message
{
private:
    // struct to hold all the pointers that are message data
    struct message_data
    {
        string * sender;
        string * msgType;
        string * content;
        string * date;
        const static int data_count = 4;


        message_data():sender(nullptr),msgType(nullptr),content(nullptr),
                                                        date(nullptr)
        {
            createDate();
        }


        ~message_data()
        {
            if(sender)
                delete sender;
            if(msgType)
                delete msgType;
            if(content)
                delete content;
            if(date)
                delete date;

            sender = msgType = content = date = nullptr;
        }

        void createDate();
        static string generateMonth();

        bool hasAllVals()
        {
            return sender && msgType && content && date;
        }
        bool hasSender() const{return sender;}
        bool hasMsgType() const{return msgType;}
        bool hasContent() const{return content;}
        bool hasDate(){return date;}
    };

    message_data * data; // pointer to message data struct
    bool isRead;         // Read status
    int msgNum;          // The number of this message in users inbox.

    void destroy(){if(data) delete data;}

public:
    Message();
    Message(const Message &);
    Message& operator=(const Message &);
    ~Message();
    void setSender(const string &);
    void setMsgType(const string &);
    // use string class += on the contact tag
    // the tag will be their preffered contact and also the message type
    void inheritMsgType(const Contact &);
    void setMsgContent(const string &);
    void setMsgDate(const string &);
    void setAllData(const array<string,4>&);
    string& getSender() const {return *data->sender;}
    string& getMsgType() const {return *data->date;}
    string& getMsgContent() const {return *data->content;}
    string& getMsgDate() const {return *data->date;}
    const array<string, 4> getAllData() const;



    friend ostream& operator<<(ostream &, Message &);
    void displayMsgData(){operator<<(cout, *this);}


};
#endif //PROGRAM3_MESSAGE_H
