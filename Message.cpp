//
// Created by shene on 2/17/2023.
//
#include "Message.h"


// method def for message_data struct
void Message::message_data::createDate()
{
    if(date)
        delete date;
    date = new string(generateMonth());
    int day,year;
    day =   1 + (rand() % 30);
    year =  1 + (rand() % 2023);

    // keep the year within the desired range.
    if(year > 2022 || year < 2021)
        year = 2022;



    *date += to_string(day) + " ";
    *date += to_string(year);

}



string Message::message_data::generateMonth()
{
    int month = (rand() % 12) + 1;
    string monthName;

    switch(month){
        case 1:
            monthName =  "Jan ";
        case 2:
            monthName += "Feb ";
        case 3:
            monthName += "Mar ";
        case 4:
            monthName += "Apr ";
        case 5:
            monthName += "May ";
        case 6:
            monthName += "June ";
        case 7:
            monthName += "July ";
        case 8:
            monthName += "Aug ";
        case 9:
            monthName += "Sept ";
        case 10:
            monthName += "Oct ";
        case 11:
            monthName += "Nov ";
        case 12:
            monthName += "Dec ";
        default:
            monthName += "May ";
    }

    return monthName;
}


// default constructor
Message::Message():data(nullptr),isRead(false),msgNum(0)
{}


// copy constructor
Message::Message(const Message &aMsg):data(nullptr),isRead(false),msgNum(0)
{
    *this = aMsg;
}


// overloaded operator= for copy construction
Message& Message::operator=(const Message &msg)
{
    if(this == &msg)
        return *this;
    array<string, 4> msgDat = msg.getAllData();
    int idx = 0;

    typedef message_data * md;
    md temp = msg.data;

    if(data)
        destroy();

    if(!msg.data)
    {
        data = nullptr;
        isRead = msg.isRead;
        msgNum = msg.msgNum;
        return *this;
    }

    // test this
    if(temp->hasAllVals())
    {
        data = new message_data();
        data->sender = new string(msgDat[idx++]);
        data->msgType = new string(msgDat[idx++]);
        data->content = new string(msgDat[idx++]);
        data->date = new string(msgDat[idx++]);
    }
    else
    {
        data = new message_data();
        if(temp->hasSender())
            data->sender = new string(msgDat[idx++]);
        else
            data->sender = nullptr;
        if(temp->hasMsgType())
            data->msgType = new string(msgDat[idx++]);
        else
            data->msgType = nullptr;
        if(temp->hasContent())
            data->content = new string(msgDat[idx++]);
        else
            data->content = nullptr;
        if(temp->hasDate())
            data->date = new string(msgDat[idx++]);
        else
            data->date = nullptr;
    }


    isRead = msg.isRead;
    msgNum = msg.msgNum;

    return *this;

}


/*
 * return an array of all message data attributes
 * @return std::array<string,4> an array of strings
 */
const array<string, 4> Message::getAllData() const
{
    string vals[] = {getSender(), getMsgType(), getMsgContent(),getMsgDate()};
    array<string, 4> msgDat;
    int idx = 0;

    for(auto & x : msgDat)
    {
        x = vals[idx];
    }

    return msgDat;
}


// class destructor
Message::~Message()
{
    destroy();
    data = nullptr;
    isRead = false;
    msgNum = 000000;
}


/*
 * set the sender of this message object
 * @param from - a string representing the senders name
 */
void Message::setSender(const std::string &from)
{
    if(data->sender)
        delete data->sender;

    data->sender = new string(from);
}


/*
 * set the type of message this is i.e Text, Facebook, Reddit, Twitter.. etc
 * @param type - a string representing the message type.
 */
void Message::setMsgType(const std::string &type)
{
    if(data->msgType)
        delete data->msgType;
    data->msgType = new string(type);
}


/*
 * Set the message type based on the contacts preferred contact method.
 * IE - if the contacts preferred method is Facebook, then set this message
 * to be of type facebook.
 * @param aContact a reference to a contact object with a preferred contact.
 */
void Message::inheritMsgType(const Contact &aContact)
{
    if(!aContact->hasType())
        return;
    if(data->hasMsgType())
        delete data->msgType;
    data->msgType = new string(aContact.getPrefferedMethod());
}


/*
 * Set this messages content
 * @param message a string representing this messages content
 */
void Message::setMsgContent(const std::string &message)
{
    if(data->content)
        delete data->content;
    data->content = new string(message);
}


/*
 * Set this messages date
 * @param a string representing the date this message was sent in M/DD/YYYY
 */
void Message::setMsgDate(const std::string &new_date)
{
    if(data->hasDate())
        delete data->date;
    data->date = new string(new_date);
}


/*
 * Set all data attributes of the message_data pointer in the class
 * @param &values an std::array with the values we wish to set our
 * attributes too.
 */
void Message::setAllData(const array<string,4>& values)
{
    if(data)
        destroy();
    data = new message_data();

    for(auto x = 0; x < message_data::data_count; x++)
    {
        switch(x)
        {
            case 0:
                data->sender = new string(values[x]);
            case 1:
                data->msgType = new string(values[x]);
            case 2:
                data->content = new string(values[x]);
            case 3:
                data->date = new string(values[x]);
            default:
                continue;
        }
    }
}


// overloaded << operator to print all message data at stream extraction.
ostream& operator<<(ostream &out, Message &msg)
{
    if(!msg.data)
    {
        out << " No message! ";
        return out;
    }

    out << "Message " << msg.msgNum << "\n\tFrom: " << *msg.data->sender <<
        "\n\tSource: " << *msg.data->msgType << "\n\tMessage: \n\t"
        << *msg.data->content << endl;
    out << "****** END OF MESSAGE " << to_string(msg.msgNum) << " ******\n";

    return out;
}

