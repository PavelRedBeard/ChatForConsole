#include "Message.h"
#include<iostream>

string Message::getMessage() const
{
    return _message;
}

string Message::getNameFrom() const
{
    return _fromUser;
}

string Message::getNameTo() const
{
    return _toUser;
}

void Message::setMessage(const string& message)
{
    _message = message;
}

void Message::setNameFrom(const string& fromUser)
{
    _fromUser = fromUser;
}

void Message::setNemeTo(const string& toUser)
{
    _toUser = toUser;
}

void Message::outfild()
{
    cout << _message << "\t" << _fromUser << "\t" << _toUser << endl;
}
