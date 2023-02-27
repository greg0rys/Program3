//
// Created by shene on 2/26/2023.
//

#ifndef PROGRAM3_PHONE_H
#define PROGRAM3_PHONE_H
#include "msgTree.h"
#include <vector>

using namespace std;

class Phone
{

private:

    typedef vector<Contact>  contact_v;
    typedef vector<Message>  message_v;
    string * userName;
    bool hasMessages;
    msgTree * msgs;
    contact_v * contactList;
    message_v * messageList;
    inline bool hasInfo(){return userName || msgs || contactList
                                          || messageList;}
    inline bool hasName(){return userName;}
    inline bool hasMessage(){return hasMessages;}
    inline bool hasTree(){return msgs;}
    inline bool hasCTList(){return contactList;}
    inline bool hasMList(){return messageList;}

    void _destruct();

public:
    Phone();
    Phone(vector<Contact> &, vector<Message> &, const string &, msgTree *,
          bool = false);
    Phone(const Phone &);
    Phone& operator=(const Phone &);
    ~Phone();
    Phone& operator+(const Message &);
    Phone& operator+(const Contact &);
    Phone& operator-=(Contact &);
    Phone& operator-=(Message &);

    void displayContacts();
    void displayMessages();
    void displayMessageList();




};
#endif //PROGRAM3_PHONE_H

//inline class helpers
