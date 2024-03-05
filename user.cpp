#include "user.h"
#include "qdebug.h"

User::User(string username, string password, unsigned int admin) {
    this->username = username;
    this->password = password;
    this->admin = admin;
}

string User::getUsername() const{
    return username;
}

void User::setUsername(string username){
    this->username = username;
}

string User::getPassword() const{
    return password;
}

void User::setPassword(string password){
    this->password = password;
}

unsigned int User::getAdmin() const{
    return admin;
}

void User::setAdmin(unsigned int admin){
    this->admin = admin;
}

vector<string> & User::getProfils(){
    return profils;
}

void User::setProfils(vector<string> profils){
    this->profils = profils;
}

void User::print()
{
    qDebug() << "name : " << username << "\npass : " << password << "\nOP : " << to_string(admin);
}
