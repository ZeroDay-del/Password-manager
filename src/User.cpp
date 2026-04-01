#include "User.h"
#include <iostream>
using namespace std;

// constructor
User::User(string u, string p, string w)
{
    username = u;
    password = p;
    website = w;
}


// destructor
User::~User()
{
    //dtor
}

// The function to display user information
void User::display(){
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
}

string User::getUsername(){
    return username;
}

string User::publish(){
    return website + " | " + username + " | " + password + "\n";
}
