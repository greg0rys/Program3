//
// Created by shene on 2/26/2023.
//

#include "Phone.h"

Phone::Phone():userName(nullptr),hasMessages(false),
               msgs(nullptr),contactList(nullptr),messageList(nullptr)
{}


Phone::Phone( vector<Contact> & ct, vector<Message> & mess,
              const string &uName,msgTree * messages, bool hasMess):
             userName(new string(uName)),hasMessages(hasMess),
             msgs(new msgTree(*messages)),
             contactList(new Phone::contact_v(ct)),
             messageList(new Phone::message_v(mess))
{


}


Phone::Phone(const Phone & copy):userName(nullptr),
                                 hasMessages(false),msgs(nullptr),
                                 contactList(nullptr), messageList(nullptr)
{
    *this = copy;
}


Phone& Phone::operator=(const Phone & copy)
{
    if(this == &copy)
        return *this;

    if(hasInfo())
        _destruct();

    if(copy.userName)
        userName = new string(*copy.userName);
    else
        userName = nullptr;


    hasMessages = copy.hasMessages;

    if(copy.msgs)
        msgs = new msgTree(*copy.msgs);
    else
        msgs = nullptr;

    if(copy.contactList)
        contactList = new vector<Contact>(*copy.contactList);
    else
        contactList = nullptr;

    if(copy.messageList)
        messageList = new vector<Message>(*copy.messageList);
    else
        messageList = nullptr;

    return *this;
}


Phone::~Phone()
{
    if(hasInfo())
        _destruct();
}


void Phone::_destruct()
{
    if(userName)
        delete userName;



    if(msgs)
        delete msgs;

    if(contactList)
        delete contactList;
    if(messageList)
        delete messageList;

    userName = nullptr;
    msgs = nullptr;
    contactList = nullptr;
    messageList = nullptr;
}


Phone& Phone::operator+(const Contact & cont)
{
    if(!contactList)
        contactList = new vector<Contact>;

    contactList->push_back(cont);
    return *this;
}


Phone& Phone::operator+(const Message & mess)
{

    if(!msgs)
        msgs = new msgTree();

    Contact ct;
    ct.setName(&mess.getSender());
    msgs->getContact(ct);
    if(ct.getName() == "no matches")
    {
        ct.setName((const string *) "Unknown");
        ct.setHandle((const string *) "Unknown");
        ct.setType((const string *) "Unknown");
    }
    msgs->insert(ct, const_cast<Message &>(mess));


    return *this;
}



Phone& Phone::operator-=(Contact & contName)
{
    if(!contactList)
        return *this;

    int matches = 0;
    string cName = contName.getName();
    for(auto  it = contactList->begin(); it < contactList->end(); it++)
    {
        if(it->getName() == cName)
        {
            msgs->removeByContact(contName, matches);
            contactList->erase(it);

        }
    }

    if(matches > 0)
        cout << "Removed " << matches << " contact(s) named " << cName << endl;
    else
        cout << "No contacts named " << cName << " were found! " << endl;
    return *this;
}




Phone& Phone::operator-=(Message & mess)
{
    if(!messageList)
        return *this;

    bool found = false;
    int messNum = mess.getMNum();

    for(auto it = messageList->begin(); it < messageList->end(); it++)
    {
        if(it->getMNum() == messNum)
        {
            found = true;
            cout << msgs->getCount() << endl;
            msgs->removeMsgNum(messNum);
            cout << msgs->getCount() << endl;
        }

    }

    if(found)
        cout << "Removed message number " << messNum << endl;
    else
        cout << "No messages had the number " << messNum << endl;
    return *this;
}


void Phone::displayContacts()
{
    if(!hasCTList())
    {
        cout << "You have no contacts! " << endl;
        return;
    }

    for(auto &x : *contactList)
    {
        cout << x << endl;
    }
}
