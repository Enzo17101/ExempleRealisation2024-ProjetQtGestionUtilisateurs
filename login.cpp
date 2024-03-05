#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    //Initialisation des champs de saisie
    ui->fieldUsername->setPlaceholderText("Entrez un nom");
    ui->fieldMdp->setPlaceholderText("Entrez un mot de passe");
}

Login::~Login()
{
    delete ui;
}

void Login::setData(vector<User> & userList)
{
    this->userList = &userList;
}

void Login::on_connexionButton_clicked()
{
    //Récupération des infos des champs de saisie
    QString username = ui->fieldUsername->text();
    QString password = ui->fieldMdp->text();

    //On s'assure que les champs ne sont pas vides
    if(username.isEmpty())
    {
        ui->errorLabel->setText("Veuillez entrer un nom");
    }
    else if(password.isEmpty())
    {
        ui->errorLabel->setText("Veuillez entrer un mot de passe");
    }
    else
    {

        bool userExist = false;
        User * userLogin;
        for(auto & user : *userList)
        {
            //Recherche des login/mdp parmis les utilisateurs entrés
            if(!user.getUsername().compare(username.toStdString()) && !user.getPassword().compare(password.toStdString()))
            {
                userExist = true;
                userLogin = &user;
                break;
            }
        }

        if(userExist)
        {
            this->close();

            if(userLogin->getAdmin() == 0)
            {
                //Affichage de la liste des utilisateurs si c'est un admin qui se connecte
                UserList * userListController = new UserList();

                userListController->setData(*userList);

                userListController->show();
            }
            else
            {
                //Affichage de la liste des profils si c'est un admin qui se connecte

                ProfileList * profileList = new ProfileList();

                profileList->setData(userLogin->getProfils(), userLogin->getAdmin(), *userList);

                profileList->show();
            }
        }
        else
        {
            //Si on ne trouve pas l'utilisateur dans la liste
            ui->errorLabel->setText("Identifiant ou mot de passe incorrect");
        }
    }
}
