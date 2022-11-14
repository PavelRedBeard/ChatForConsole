#pragma once
#include<string>
using namespace std;

class User
{
public:
	User() = default;
	User(const string& name, const string& pass) : _name(name), _pass(pass) {};
	~User() = default;
	void setName(const string& name);
	void setPass(const string& pass);
	string getName() const;
	string getPass() const;
	void outfield();
private:
	string _name;
	string _pass;
};