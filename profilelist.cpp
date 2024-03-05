
#include <iostream>

#include "profilelist.h"
#include "login.h"
#include "qstringlistmodel.h"
#include "ui_profilelist.h"

using namespace std;

ProfileList::ProfileList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProfileList)
{
    ui->setupUi(this);

    //Initialisation des champs de saisie
    ui->newProfileText->setPlaceholderText("Entrez un nom de profil");
}

ProfileList::~ProfileList()
{
    delete ui;
}

void ProfileList::setData(vector<string> & profileList, int perm, vector<User> & userList)
{

    this->profileList = &profileList;
    this->userList = &userList;

    //Création du modèle pour la liste des profils
    model = new ProfileTableModel(this->profileList);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Profile name"));

    ui->tableProfile->setModel(model);
    ui->tableProfile->resizeColumnsToContents();

    connect(model, &ProfileTableModel::dataChanged, ui->tableProfile, &QTableView::reset);


    //Le niveau de permission 2 étant le plus bas, ces boutons sont cachés
    if(perm == 2)
    {
        ui->newProfileButton->hide();
        ui->delProfileButton->hide();
        ui->newProfileText->hide();
        ui->newProfileLabel->hide();
        ui->returnButton->hide();
    }
    else if(perm==1)
    {
        ui->returnButton->hide();
    }
    else if(perm==0)
    {
        ui->disconnectButton->hide();
    }
}

void ProfileList::on_newProfileButton_clicked()
{
    //Récupération des infos du champ de saisie
    QString profilename = ui->newProfileText->text();

    if(profilename.isEmpty())
    {
        ui->errorLabel->setText("Veuillez entrer un nom");
    }
    else
    {
        ui->errorLabel->setText("");

        //Création du nouveau profil
        model->addData(profilename);

        model->updateTable();
    }
}

void ProfileList::on_delProfileButton_clicked()
{
    //Récupération de la ligne sélectionnée dans le tableau
    QModelIndexList select = ui->tableProfile->selectionModel()->selectedIndexes();

    if (!select.isEmpty()) {
        //Suppression du profil sélectionné
        int idProfil = select.first().row();
        model->removeData(idProfil);
    }

    model->updateTable();
}

void ProfileList::on_disconnectButton_clicked()
{
    this->close();

    Login * login = new Login();

    login->setData(*userList);

    login->show();
}

void ProfileList::on_returnButton_clicked()
{
    this->close();

    UserList * userListController = new UserList();

    userListController->setData(*userList);

    userListController->show();
}
