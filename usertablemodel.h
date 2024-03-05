#include "user.h"
#include <QAbstractTableModel>
#include <QVariant>

class UserTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    UserTableModel(vector<User> * utilisateurs, QObject *parent = nullptr) :
        QAbstractTableModel(parent), userList(utilisateurs) {}

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int column, Qt::Orientation orientation, int role) const override;


    // Ajout et suppression de ligne
    void addData(const User& user);
    void removeData(int row);


    void updateTable();

private:
    // Structure de données pour stocker les données du tableau
    vector<User> * userList;
};
