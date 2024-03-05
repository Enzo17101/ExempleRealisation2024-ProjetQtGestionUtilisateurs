#include <QAbstractTableModel>
#include <QVariant>
#include <string>

#include "user.h"

class ProfileTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    ProfileTableModel(vector<string> * listeProfils, QObject *parent = nullptr) :
        QAbstractTableModel(parent), profileList(listeProfils) {}

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int column, Qt::Orientation orientation, int role) const override;


    // Ajout et suppression de lignes
    void addData(const QString & profilename);
    void removeData(int row);

    void updateTable();

private:
    vector<string> * profileList;

    //User * user;
};
