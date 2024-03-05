#ifndef NEWUSER_H
#define NEWUSER_H

#include <QWidget>
#include <iostream>
#include <userlist.h>
#include <profilelist.h>
#include "user.h"

using namespace std;

namespace Ui {
class NewUser;
}

class NewUser : public QWidget
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = nullptr);
    ~NewUser();
    void setData(vector<User> & userList);

private slots:
    void on_inscriptionButton_clicked();

private:
    Ui::NewUser *ui;
    vector<User> * userList;
};

#endif // NEWUSER_H
