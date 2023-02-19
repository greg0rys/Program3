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
            monthName = "Feb ";
        case 3:
            monthName = "Mar ";
        case 4:
            monthName = "Apr ";
        case 5:
            monthName = "May ";
        case 6:
            monthName = "June ";
        case 7:
            monthName = "July ";
        case 8:
            monthName = "Aug ";
        case 9:
            monthName = "Sept ";
        case 10:
            monthName = "Oct ";
        case 11:
            monthName = "Nov ";
        case 12:
            monthName = "Dec ";
        default:
            monthName = "May ";
    }

    return monthName;
}


// default constructor
Message::Message():data(new message_data()),
                   isRead(false),
                   msgNum(generateMsgNum())
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

    if(data)
        delete data;

    if(!msg.data)
    {
        data = nullptr;
        return *this;
    }

    map<int,string> msg_dt = msg.getAllData();
    data = new message_data();

    for(auto it = msg_dt.begin(); it != msg_dt.end(); it++)
    {
        int key = it->first;
        if(key == 0)
            data->sender = new string(it->second);
        if(key == 1)
            data->msgType = new string(it->second);
        if(key == 2)
            data->content = new string(it->second);
        if(key == 3)
            setMsgDate(it->second);
    }

    isRead = msg.isRead;
    msgNum = msg.msgNum;

    return *this;



}


/*
 * return an array of all message data attributes
 * @return std::map<string,4> an array of strings
 */
map<int, string> Message::getAllData() const
{
    map<int,string> msgDat;

    if(!data)
        return msgDat;
   string from,type,cont,date;
   getSender(from);
   getMsgType(type);
   getMsgContent(cont);
   getMsgDate(date);

   string temp[] = {from,type,cont,date};

    for(auto x = 0; x < 4; x++)
    {
        msgDat.insert(pair<int,string>(x,temp[x]));
    }

    return msgDat;
}


bool Message::getSender(string & from) const
{
    if(!data->sender)
    {
        from = "null sender";
        return false;
    }

    from = *(data->sender);
    return true;
}


bool Message::getMsgType(string & type) const
{
    if(!data->msgType)
    {
        type = "null type";
        return false;
    }

    type = *(data->msgType);
    return true;
}


bool Message::getMsgContent(string & content) const
{
    if(!data->content)
    {
        content = "null content";
        return false;
    }

    content = *(data->content);
    return true;

}


bool Message::getMsgDate(string & dt) const
{
    if(!data->date)
    {
        dt = "null date";
        return false;
    }

    dt = *(data->date);
    return true;
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
bool Message::setSender(const std::string &from)
{
    if(!data)
    {
        return false;
    }

    if(!data->sender)
        data->sender = new string(from);
    else
        *data->sender = from;
    return true;
}


/*
 * set the type of message this is i.e Text, Facebook, Reddit, Twitter.. etc
 * @param type - a string representing the message type.
 */
bool Message::setMsgType(const std::string &type)
{
    if(!data)
    {
        return false;
    }

    if(!data->msgType)
         data->msgType = new string(type);
    else
        *data->msgType = type;
    return true;
}



/*
 * Set this messages content
 * @param message a string representing this messages content
 */
bool Message::setMsgContent(const std::string &message)
{
    if(!data)
        return false;

    if(!data->content)
        data->content = new string(message);
    else
        *data->content = message;
    return true;
}


/*
 * Set this messages date
 * @param a string representing the date this message was sent in M/DD/YYYY
 */
bool Message::setMsgDate(const std::string &new_date)
{
    if(!data)
        return false;

    if(!data->date)
        data->date = new string(new_date);
    else
        *data->date = new_date;

    return true;
}


/*
 * Set all data attributes of the message_data pointer in the class
 * @param &values an std::array with the values we wish to set our
 * attributes too.
 */
bool Message::setAllData(const map<int,string>& values)
{
    if(data)
        destroy();

    data = new message_data();

    for(const auto & it : values)
    {
        int key = it.first;
        string value = it.second;
        if(key == 0)
            data->sender = new string(value);
        if(key == 1)
            data->msgType = new string(value);
        if(key == 2)
            data->content = new string(value);
        // because date is created at construct
        // we only need to update its value, not init.
        if(key == 3)
            setMsgDate(value);
    }

    return true;

}


// overloaded << operator to print all message data at stream extraction.
ostream& operator<<(ostream &out, Message &msg)
{
    if(!msg.data->hasAllVals())
    {
        out << " No message! ";
        return out;
    }

    out << "Message " << msg.msgNum << "\n\tFrom: " << *msg.data->sender <<
        "\n\tSource: " << *msg.data->msgType << "\n\tMessage: \n\t"
        << *msg.data->content << endl;
    cout << *msg.data->date;
    out << "****** END OF MESSAGE " << to_string(msg.msgNum) << " ******\n";

    return out;
}

