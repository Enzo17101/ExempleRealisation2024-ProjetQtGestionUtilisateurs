#include "profiletablemodel.h"


int ProfileTableModel::rowCount(const QModelIndex &parent = QModelIndex()) const {
    return profileList->size();
}

int ProfileTableModel::columnCount(const QModelIndex &parent = QModelIndex()) const {
    //La taille est fixe
    return 1;
}

QVariant ProfileTableModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const  {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= rowCount()|| index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        //const User & user = profileList[index.row()];
        const string & profile = (*profileList)[index.row()];

        switch (index.column())
        {
        case 0: return QVariant::fromValue(QString::fromStdString(profile));
        default: return QVariant();
        }
    }

    return QVariant();
}

void ProfileTableModel::addData(const QString & profilename) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    string name = profilename.toStdString();
    (*profileList).push_back(name);

    endInsertRows();
}

void ProfileTableModel::removeData(int row) {
    beginRemoveRows(QModelIndex(), row, row);

    (*profileList).erase((*profileList).begin()+row);

    endRemoveRows();
}

void ProfileTableModel::updateTable()
{
    emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, columnCount() - 1));
}

QVariant ProfileTableModel::headerData(int column, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch(column)
        {
        case 0:
            return tr("Nom du profil");
        default :
            return QVariant();
        }
    }

    return QVariant();
}
