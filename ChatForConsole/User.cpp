#include<iostream>
#include "User.h"


void User::setName(const string& name)
{
	_name = name;
}

void User::setPass(const string& pass)
{
	_pass = pass;
}

string User::getName() const
{
	return _name;
}

string User::getPass() const
{
	return _pass;
}

void User::outfield()
{
	cout << _name << "\t" << _pass << endl;
}
