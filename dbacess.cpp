#include "dbacess.h"

DBAcess::DBAcess() {
    // Créez une connexion à la base de données SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Ngoné/Desktop/Master1/ProjetQt/dbLibrary.db");
    qDebug("Accès à la base de données 'dbLibrary.db' effectif");
}


bool DBAcess::open() {
    if (db.isOpen() == true)
        return true;
    if (db.open() == true)
    {
        qDebug("Connexion ouverte avec la base de données !");
        return true;
    } else
    {
        qDebug("Echec d'ouverture de la connexion avec la base de données !");
        return false;
    }
}

void DBAcess::close() {
    if (db.isOpen() == false) return;
        db.close();
        qDebug("Fermeture de la connexion effectuée avec succès !");

}
DBAcess::~DBAcess() {}
