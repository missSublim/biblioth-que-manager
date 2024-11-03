#include "addmember.h"
#include "ui_addmember.h"
#include "dbacess.h"
#include "QSqlQuery"
#include "QSqlError"



AddMember::AddMember(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddMember)
{
    ui->setupUi(this);
}

AddMember::~AddMember()
{
    delete ui;
}
//soumission de l'ajout d'un membre dans la base de données
void AddMember::on_pushButton_clicked()
{
    DBAcess dbAcess;
    dbAcess.open();
    QString nom,prenom,date_inscription;
    nom=ui->nomLineEdit->text();
    prenom=ui->prenomLineEdit->text();
    date_inscription=ui->dateDInscriptionLineEdit->text();

    QSqlQuery query(dbAcess.db);
    query.prepare("insert into Membre(Nom, Prenom, Date_inscription) values(:nom, :prenom, :date_inscription)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_inscription", date_inscription);

    if (query.exec()){
        qDebug("Livre ajouté avec succes !");
        ui->nomLineEdit->clear();
        ui->prenomLineEdit->clear();
        ui->dateDInscriptionLineEdit->clear();
    }else
    {
        qDebug() <<"echec de l'ajout:" << query.lastError().text();
        qDebug() <<"echec de l'ajout:" << nom;
        qDebug() <<"echec de l'ajout:" << prenom;
        qDebug() <<"echec de l'ajout:" << date_inscription;
    }
    dbAcess.close();
}



