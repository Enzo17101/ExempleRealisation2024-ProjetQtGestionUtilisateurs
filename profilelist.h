#ifndef PROFILELIST_H
#define PROFILELIST_H

#include <QWidget>

#include "user.h"
#include "profiletablemodel.h"

namespace Ui {
class ProfileList;
}

class ProfileList : public QWidget
{
    Q_OBJECT

public:
    explicit ProfileList(QWidget *parent = nullptr);
    ~ProfileList();
    //void setData(User & user);
    void setData(vector<string> & profileList, int perm, vector<User> & userList);

private slots:
    void on_newProfileButton_clicked();
    void on_delProfileButton_clicked();
    void on_disconnectButton_clicked();
    void on_returnButton_clicked();

private:
    Ui::ProfileList *ui;
    //User * user;
    vector<string> * profileList;
    vector<User> * userList;
    ProfileTableModel * model;
};

#endif // PROFILELIST_H
