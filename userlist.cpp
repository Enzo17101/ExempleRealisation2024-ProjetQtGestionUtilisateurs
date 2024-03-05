#include <iostream>

#include "userlist.h"
#include "login.h"
#include "ui_userlist.h"

using namespace std;

UserList::UserList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserList)
{
    ui->setupUi(this);

    //Initialisation des champs de saisie
    ui->fieldUsername->setPlaceholderText("Entrez un nom");
    ui->fieldMdp->setPlaceholderText("Entrez un mot de passe");

    //Initialisation du menu déroulant pour choisir le niveau d'un nouvel utilisateur
    ui->comboBoxAdmin->addItem(QString::number(2));
    ui->comboBoxAdmin->addItem(QString::number(1));
    ui->comboBoxAdmin->addItem(QString::number(0));
}

UserList::~UserList()
{
    delete ui;
}

void UserList::setData(vector<User> & userList)
{
    this->userList = &userList;

    //Création du modèle pour la liste des utilisateurs
    model = new UserTableModel(this->userList);

    ui->tableUser->setModel(model);
    ui->tableUser->resizeColumnsToContents();

    connect(model, &UserTableModel::dataChanged, ui->tableUser, &QTableView::reset);
}

void UserList::on_newUserButton_clicked()
{
    //Récupération des infos des champs de saisie
    QString username = ui->fieldUsername->text();
    QString password = ui->fieldMdp->text();
    int admin = ui->comboBoxAdmin->currentText().toUInt();

    bool alreadyExist = false;

    //Recherche si l'identifiant existe déjà
    for (User user : *userList) {
        if(user.getUsername() == username.toStdString()){
            alreadyExist = true;
            break;
        }
    }

    if(username.isEmpty())
    {
        ui->errorLabel->setText("Veuillez entrer un nom");
    }
    else if(password.isEmpty())
    {
        ui->errorLabel->setText("Veuillez entrer un mot de passe");
    }
    else if(alreadyExist)
    {
        ui->errorLabel->setText("Identifiant déjà existant");
    }
    else
    {
        ui->errorLabel->setText("");

        //Création du nouvel utilisateur
        User* user = new User(username.toStdString(),password.toStdString(),admin);
        model->addData(*user);

        user->print();
    }


    model->updateTable();
}

void UserList::on_delUserButton_clicked()
{
    //Récupération de la ligne sélectionnée dans le tableau
    QModelIndexList select = ui->tableUser->selectionModel()->selectedIndexes();

    if (!select.isEmpty()) {
        //Suppression de l'utilisateur sélectionné
        int idUser = select.first().row();
        if(idUser == 0)
        {
            //Le super utilisateur ne peut pas être supprimé
            ui->errorLabel->setText("Cet utilisateur ne peut être supprimé");
        }
        else
        {
            ui->errorLabel->setText("");
            model->removeData(idUser);
        }
    }

    model->updateTable();
}

void UserList::on_showProfileButton_clicked()
{
    //Récupération de la ligne sélectionnée dans le tableau
    QModelIndexList select = ui->tableUser->selectionModel()->selectedIndexes();

    if (!select.isEmpty()) {
        this->close();

        int idUser = select.first().row();
        User * user = &(*userList)[idUser];

        //Affichage de la liste des profils de l'utilisateur sélectionné
        ProfileList * profileList = new ProfileList();
        profileList->setData(user->getProfils(), 0, *userList);

        profileList->show();
    }
}

void UserList::on_disconnectButton_clicked()
{
    this->close();

    Login * login = new Login();

    login->setData(*userList);

    login->show();
}
