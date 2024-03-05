#include "usertablemodel.h"

int UserTableModel::rowCount(const QModelIndex &parent = QModelIndex()) const {
    return (*userList).size();
}

int UserTableModel::columnCount(const QModelIndex &parent = QModelIndex()) const {
    //La taille est fixe
    return 3;
}

QVariant UserTableModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const  {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= (int)(*userList).size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const User & user = (*userList)[index.row()];
        switch (index.column())
        {
        case 0: return QVariant::fromValue(QString::fromStdString(user.getUsername()));
        case 1: return QVariant::fromValue(QString::fromStdString(user.getPassword()));
        case 2: return QVariant::fromValue(QString::number(user.getAdmin()));
        default: return QVariant();
        }
    }

    return QVariant();
}

void UserTableModel::addData(const User& user) {
    int row = (*userList).size();
    beginInsertRows(QModelIndex(), row, row);

    (*userList).push_back(user);

    endInsertRows();
}

void UserTableModel::removeData(int row) {

    beginRemoveRows(QModelIndex(), row, row);

    (*userList).erase((*userList).begin()+row);

    endRemoveRows();
}

void UserTableModel::updateTable()
{
    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

QVariant UserTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(column)
        {
        case 0:
            return tr("Nom d'utilisateur");
        case 1:
            return tr("Mot de passe");
        case 2:
            return tr("Niveau de droits");
        default :
            return QVariant();
        }
    }

    return QVariant();
}
