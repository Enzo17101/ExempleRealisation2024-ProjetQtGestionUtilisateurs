#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User
{
private:
    string username;
    string password;
    unsigned int admin;
    vector<string> profils;
public:
    User(string username, string password, unsigned int admin);

    string getUsername() const;
    void setUsername(string username);
    string getPassword() const;
    void setPassword(string password);
    unsigned int getAdmin() const;
    void setAdmin(unsigned int admin);
    vector<string> & getProfils();
    void setProfils(vector<string> profils);
    void print();
};

#endif // USER_H
