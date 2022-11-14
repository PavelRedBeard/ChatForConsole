#pragma once
#include<string>
using namespace std;

class Message
{
public:
	Message() = default;
	Message(string& message, string& fromUser, string& toUser) : _message(message), _fromUser(fromUser), _toUser(toUser) {};
	~Message() = default;
	string getMessage() const;
	string getNameFrom() const;
	string getNameTo() const;
	void setMessage(const string& message);
	void setNameFrom(const string& fromUser);
	void setNemeTo(const string& toUser);
	void outfield();
private:
	string _message;
	string _fromUser;
	string _toUser;
};