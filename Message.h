//
// Created by shene on 2/17/2023.
//

#ifndef PROGRAM3_MESSAGE_H
#define PROGRAM3_MESSAGE_H


#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>


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
    static int generateMsgNum(){return (rand() % 1500) + 1;}

public:
    Message();
    Message(const Message &);
    Message& operator=(const Message &);
    ~Message();
    bool setSender(const string &);
    bool setMsgType(const string &);

    bool setMsgContent(const string &);
    bool setMsgDate(const string &);
    bool setAllData(const map<int,string>&);
    bool getSender( string &) const ;
    bool getMsgType( string &) const;
    bool getMsgContent( string &) const;
    bool getMsgDate( string &) const;
    map<int, string> getAllData() const;
     int getMNum() {return msgNum;}



    friend ostream& operator<<(ostream &, Message &);
    void displayMsgData(){operator<<(cout, *this);}


};
#endif //PROGRAM3_MESSAGE_H
