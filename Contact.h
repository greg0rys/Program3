//
// we need to create a base class user, and derive a contact from it
// in the working application the user will have a contact list stored as a
// red-black tree using the contacts tag as the nodes key in the tree

// the contact will also benefit from inheriting from the user because it
// can inherit the values name etc from the user and then the contact
// can have the data member for the preferred contact type.
// Created by shene on 2/17/2023.
//

#ifndef PROGRAM3_CONTACT_H
#define PROGRAM3_CONTACT_H
#include <string>
#include <iostream>
#include <map>
#include "Message.h"

using namespace std;

class Contact
{
private:

    struct node
    {
        string *  name;
        string *  contact_type;
        string *  contact_handle;

        node():name(nullptr),contact_type(nullptr),contact_handle(nullptr)
        {}

        ~node()
        {
           if(name)
               delete name;
           if(contact_type)
               delete contact_type;
           if(contact_handle)
               delete contact_handle;

           name = contact_handle = contact_type = nullptr;
        }
    };

    node * info;
    map<int,Message> * messages;

public:
    Contact();
    Contact(const Contact &);
    Contact& operator=(const Contact &);
    ~Contact();
    friend ostream& operator<<(ostream &, Contact &);
    bool setName(const string *);
    bool setType(const string *);
    bool setHandle(const string *);
    bool addMessage(Message &);
    void getName(string &);
    void getType(string &);
    void getHandle(string &);
    size_t getMsgCount(){return messages->size();}

};

#endif //PROGRAM3_CONTACT_H
