#include<iostream>
#include"Message.h"
#include"User.h"
#include<string>
#include<fstream>
using namespace std;


class Except : public exception
{
private:
    string _message;
public:
    Except(string message) : _message(message) {};
    const char* what() const noexcept { return _message.c_str(); }
};

void NewUser(const string& uname, const string& upass)
{
    fstream userlog, userpas;
    string buff;
    bool stm = true;
    userlog.open("Users.txt", fstream::in | fstream::out | fstream::app);
    if (!userlog.is_open())
    {
        throw Except("NewUser(): File is not open");
    }
    else
    {
        while (getline(userlog, buff))
        {
            if (uname == buff)
            {
                cout << "\t" << "Username is taken" << endl;
                stm = false;
            }
        }
        userlog.close();
    }
    if (stm == true)
    {
        userlog.open("Users.txt", fstream::in | fstream::out | fstream::app);
        userpas.open("Pass.txt", fstream::in | fstream::out | fstream::app);
        if (!userlog.is_open() && !userpas.is_open())
        {
            throw Except("NewUser(): File is not open");
        }
        else
        {
            userlog << uname << endl;
            userpas << upass << endl;
            userlog.close();
            userpas.close();
            cout << "\t" << "New user added" << endl;;
            return;
        }
    }
};

bool Auth(const string& uname, const string& upass)
{
    fstream userlog, userpas;
    string buff, buffpas;
    userlog.open("Users.txt", fstream::in | fstream::out | fstream::app);
    userpas.open("Pass.txt", fstream::in | fstream::out | fstream::app);
    if (!userlog.is_open() && !userpas.is_open())
    {
        throw Except("Auth(): File is not open");
    }
    else
    {
        while ((getline(userlog, buff)), (getline(userpas, buffpas)))
        {
            if (uname == buff && upass == buffpas)
            {
                system("cls");
                cout << "\t" << "You authorized!" << "\n" << endl;
                userlog.close();
                return true;
            }
        }
        system("cls");
        cout << "\t" << "Wrong username or password" << endl;
        return false;
    }
};
void OpenChat(const User& user)
{
    fstream messlog;
    string name, message;
    name = user.getName();
    messlog.open("OpenChat.txt", fstream::in | fstream::out | fstream::app);
    if (!messlog.is_open())
    {
        throw Except("OpenChat(): File is not open");
    }
    else
    {
        cout << "\t" << "--------Open chat---------" << endl;
        cout << "\t" << "Enter 'quit' for exit" << endl;
        while (getline(messlog, message))
        {
            cout << message << endl;
        }
        cout << "\n";
    }
    messlog.close();
    cin.get();
    messlog.open("OpenChat.txt", fstream::in | fstream::out | fstream::app);
    while (true)
    {
        cout << name << ": ";
        getline(cin, message);
        if (message == "quit")
        {
            messlog.close();
            system("cls");
            return;
        }
        messlog << name << ": " << message << "\n";
    }
};
void PersChat(const User& user, Message& ms)
{
    fstream userlog;
    string message, nameFrom, nameTo;
    nameFrom = user.getName();
    userlog.open("Users.txt", fstream::in | fstream::out | fstream::app);
    if (!userlog.is_open())
    {
        throw Except("PersChat(): File is not open");
    }
    else
    {
        cout << "\t" << "Choice user to send message or 'quit' to exit" << endl;
        while (getline(userlog, nameTo))
        {
            cout << nameTo << endl;
        }
        cout << "\n";

    }
    userlog.close();
    cin >> nameTo;
    if (nameTo == "quit")
    {
        return;
    }
    cout << "\t" << "Enter you message" << endl;
    cout << nameFrom << ": ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, message);
    ms.setMessage(message);
    ms.setNameFrom(nameFrom);
    ms.setNemeTo(nameTo);
    userlog.open(nameTo + ".txt", fstream::in | fstream::out | fstream::app);
    if (!userlog.is_open())
    {
        throw Except("PersChat(): File is not open");
    }
    else
    {
        userlog << ms.getNameFrom() << ": " << ms.getMessage() << "\n";
        userlog.close();
    }
    system("cls");
};

int main()
{
    try
    {
        User user;
        Message ms;
        string uname, upass, exit;
        int choice = 0;
        while (!(exit == "Yes") && !(exit == "yes"))
        {
            cout << "\t" << "----------Welcome to Chat----------" << endl;
            cout << "\t" << "What would you like to do:" << "\n" << "1: New user" << "\n" << "2: Authorization" << "\n" << "3: Close Chat" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                cout << "\t" << "Enter username: " << endl;;
                cin >> uname;
                cout << "\t" << "Enter password: " << endl;
                cin >> upass;
                system("cls");
                user.setName(uname);
                user.setPass(upass);
                NewUser(uname, upass);
                break;
            }
            case 2:
            {
                int chatChoice;
                string ex, pmessage;
                fstream persmess;
                cout << "\t" << "Enter username: " << endl;;
                cin >> uname;
                cout << "\t" << "Enter password: " << endl;
                cin >> upass;
                user.setName(uname);
                user.setPass(upass);
                system("cls");
                if (Auth(uname, upass) == true)
                {
                    while (!(ex == "Yes") && !(ex == "yes"))
                    {
                        cout << "\t" << "Chat selection: " << "\n" << "1: Open chat" << "\n" << "2: Personal messages" << "\n" << "3: For exit" << endl;
                        cin >> chatChoice;
                        switch (chatChoice)
                        {
                        case 1:
                        {
                            OpenChat(user);
                            break;
                        }
                        case 2:
                        {
                            cout << "\t" << "You personal messages" << endl;
                            persmess.open(uname + ".txt", fstream::in | fstream::out | fstream::app);
                            if (!persmess.is_open())
                            {
                                throw Except("Personal Messages: File is not open");
                            }
                            else
                            {
                                while (getline(persmess, pmessage))
                                {
                                    cout << pmessage << endl;
                                }
                                cout << "\n";
                                PersChat(user, ms);
                            }
                            break;
                        }
                        case 3:
                        {
                            cout << "\t" << "Input 'yes' to confirm exit" << endl;
                            cin >> ex;
                            break;
                        }
                        }
                        system("cls");
                    };
                }
                break;
            }
            case 3:
            {
                cout << "\t" << "Input 'yes' to confirm exit" << endl;
                cin >> exit;
                break;
            }
            }
        }
    }
    catch (Except& exception)
    {
        cerr << "Error: " << exception.what() << endl;
    }
    catch (...)
    {
        cerr << "Unknown error" << endl;
    }
    return 0;
};