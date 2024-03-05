#include "newuser.h"
#include "ui_newuser.h"


NewUser::NewUser(QWidget *parent) : QWidget(parent), ui(new Ui::NewUser)
{
    ui->setupUi(this);

    //Initialisation des champs de saisie
    ui->fieldUsername->setPlaceholderText("Entrez un nom");
    ui->fieldMdp->setPlaceholderText("Entrez un mot de passe");
    ui->fieldMdp2->setPlaceholderText("Confirmez votre mot de passe");
}

NewUser::~NewUser()
{
    delete ui;
}

void NewUser::setData(vector<User> & userList)
{
    this->userList = &userList;
}

void NewUser::on_inscriptionButton_clicked()
{
    //Récupération des infos des champs de saisie
    QString username = ui->fieldUsername->text();
    QString password = ui->fieldMdp->text();
    QString password2 = ui->fieldMdp2->text();

    //On s'assure que les champs ne sont pas vides
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
    else if(password.isEmpty() || password2.isEmpty())
    {
        ui->errorLabel->setText("Veuillez entrer un mot de passe");
    }
    else if(alreadyExist)
    {
        ui->errorLabel->setText("Identifiant déjà existant");
    }
    else
    {
        if(password != password2)
        {
            ui->errorLabel->setText("Les mots de passe ne correspondent pas !");
        }
        else
        {
            ui->errorLabel->setText("");

            //Création du nouvel utilisateur par défaut au niveau 1 (le niveau 0 est pour l'admin)
            User* newUser = new User(username.toStdString(), password.toStdString(), 1);
            (*userList).push_back(*newUser);

            this->close();

            //Affichage de la liste des profils
            ProfileList * profileList = new ProfileList();

            profileList->setData(newUser->getProfils(), 1, *userList);

            profileList->show();
        }
    }
}
