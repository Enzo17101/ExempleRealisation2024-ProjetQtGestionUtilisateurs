#ifndef LOGIN_H
#define LOGIN_H

#include "profilelist.h"
#include "user.h"
#include "userlist.h"
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void setData(vector<User> & userList);

private slots:
    void on_connexionButton_clicked();


private:
    Ui::Login *ui;
    vector<User> * userList;
};

#endif // LOGIN_H
