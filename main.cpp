#include "login.h"
#include "newuser.h"

#include "user.h"

#include <QApplication>
#include <iostream>

#include <QtXml>


using namespace std;

void save(vector<User> &listUser){

    // WRITING

    // Create a document to write XML
    QDomDocument document;

    // Making the root element
    QDomElement root = document.createElement("User");

    // Adding the root element to the document
    document.appendChild(root);

    for (User user : listUser) {
        QDomElement saveUser = document.createElement("User");
        saveUser.setAttribute("Username",  QString::fromLocal8Bit(user.getUsername()));
        saveUser.setAttribute("Password",  QString::fromLocal8Bit(user.getPassword()));
        saveUser.setAttribute("Admin", QString::number(user.getAdmin()));

        for(string profil : user.getProfils()){
            QDomElement saveProfil = document.createElement("Profil");
            saveProfil.setAttribute("Name",  QString::fromLocal8Bit(profil));
            saveUser.appendChild(saveProfil);
        }

        root.appendChild(saveUser);
    }

    // Writing to a file
    QFile file("./myXLM.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open the file for writing failed";
    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Writing is done";
    }
}


int main(int argc, char *argv[])
{


//data fonction à surcharger, prend un qmodelindex et un qvariant

    // READING

    vector<User> listUser;

    // Create a document to write XML
    QDomDocument document;

    // Open a file for reading
    QFile file("./myXLM.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open the file for reading.";
        return -1;
    }
    else
    {
        // loading
        if(!document.setContent(&file))
        {
            qDebug() << "Failed to load the file for reading.";
            return -1;
        }
        file.close();
    }

    // Getting root element
    QDomElement root = document.firstChildElement();

    QDomElement component=root.firstChild().toElement();

    while(!component.isNull())
    {
        if (component.tagName()=="User")
        {
            // Read and display the component informations
            QString username=component.attribute("Username");
            QString password=component.attribute("Password");
            QString admin=component.attribute("Admin");

            // Get the first child of the component
            QDomElement child=component.firstChild().toElement();

            // Création de la liste de profils
            vector<string> profils;

            // Lire les profils
            while (!child.isNull())
            {
                QString profil=child.attribute("Name");
                profils.push_back(profil.toStdString().c_str());

                // Next child
                child = child.nextSibling().toElement();
            }

            // Création de l'utilisateur
            User* user = new User(username.toStdString().c_str(), password.toStdString().c_str(), QVariant(admin).toInt());

            if(!profils.empty()){
                user->setProfils(profils);
            }

            listUser.push_back(*user);
        }

        // Next component
        component = component.nextSibling().toElement();
    }

    bool login = false;

    if(listUser.size() > 1){
        login = true;
    }


    QApplication application(argc, argv);

    if(!login)
    {
        NewUser newUser;
        newUser.setData(listUser);
        newUser.show();

        application.exec();
        save(listUser);
        return 1;
    }
    else
    {
        Login login;
        login.setData(listUser);
        login.show();

        application.exec();
        save(listUser);
        return 1;
    }


}



