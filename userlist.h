#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>

#include "profilelist.h"
#include "qtableview.h"
#include "user.h"
#include "usertablemodel.h"

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = nullptr);
    ~UserList();
    void setData(vector<User> & userList);

private slots:
    void on_newUserButton_clicked();
    void on_delUserButton_clicked();
    void on_showProfileButton_clicked();
    void on_disconnectButton_clicked();

private:
    Ui::UserList *ui;
    vector<User> * userList;
    UserTableModel * model;
};

#endif // USERLIST_H
