//
// Created by shene on 2/17/2023.
//

#include "Contact.h"



Contact::Contact():info(nullptr), messages(nullptr)
{
    info = new node();
}


Contact::Contact(const Contact &aCopy):info(nullptr),messages(nullptr)
{
    *this = aCopy;
}


Contact& Contact::operator=(const Contact & contact)
{
    if(this == &contact)
        return *this; // handle self assignment.


        if(info)
            delete info;
        info = new node();
        if(messages)
            delete messages;

        if(contact.messages)
        {
            messages = new vector<Message>;
            for(auto it = contact.messages->begin(); it != contact
            .messages->end(); it++)
            {
                for
            }
        }



    setName(contact.info->name);
    setType(contact.info->contact_type);
    setHandle(contact.info->contact_handle);




    return *this;
}

Contact::~Contact()
{
    if(info)
        delete info;
    info = nullptr;

    if(messages)
        delete messages;
    messages = nullptr;
}

ostream& operator<<(ostream &out, Contact &ct)
{
    if(!ct.info)
        return out;
    string name, type, handle;

    ct.getName(name);
    ct.getType(type);
    ct.getHandle(handle);



    out << name << "\ntContact Method: " << type
        << "\n\tContact info: " << handle << endl;
    return out;
}


bool Contact::addMessage(const Message * msg)
{
    if(!messages)
        messages = new vector<Message>;
    messages->push_back(*msg);

    return true;
}
bool Contact::setName(const string *c_name)
{
    if(!c_name)
        return false;
    if(!info->name)
        info->name = new string(*c_name);
    else
        *info->name = *c_name;
    return true;
}


bool Contact::setType(const string *c_type)
{
    if(!c_type)
        return false;

    if(!info->contact_type)
        info->contact_type = new string(*c_type);
    else
        *info->contact_type = *c_type;


    return true;
}


bool Contact::setHandle(const string *c_handle)
{
    if(!c_handle)
        return false;
    if(!info->contact_handle)
        info->contact_handle = new string(*c_handle);
    return true;
}


void Contact::getName(string &c_name)
{
    if(!info->name)
        return;
    c_name = *info->name;

}


void Contact::getType(string & c_type)
{
    if(!info->contact_type)
        return;
    c_type = *(info->contact_type);
}


void Contact::getHandle(string & c_handle)
{
    if(!info->contact_handle)
        return;
    c_handle = *(info->contact_handle);
}