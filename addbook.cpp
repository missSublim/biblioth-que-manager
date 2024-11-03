#include "addbook.h"
#include "ui_addbook.h"
#include "dbacess.h"
#include "QSqlQuery"
#include "QSqlError"


AddBook::AddBook(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddBook)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}
// soumission d'ajout de livre dans la base de données
void AddBook::on_pushButton_clicked()
{
    DBAcess dbAcess;
    dbAcess.open();
    QString titre,auteur,date_ajout,genre;
    titre=ui->titreLineEdit->text();
    auteur=ui->auteurLineEdit->text();
    genre=ui->genreLineEdit->text();
    date_ajout=ui->dateDAjoutLineEdit->text();

    QSqlQuery query(dbAcess.db);
    query.prepare("insert into Livre(Titre, Auteur, Date_ajout, Genre) values(:titre, :auteur, :date_ajout, :genre)");
    query.bindValue(":titre", titre);
    query.bindValue(":auteur", auteur);
    query.bindValue(":date_ajout", date_ajout);
    query.bindValue(":genre", genre);

    if (query.exec()){
        qDebug("Livre ajouté avec succes !");
        ui->titreLineEdit->clear();
        ui->auteurLineEdit->clear();
        ui->genreLineEdit->clear();
        ui->dateDAjoutLineEdit->clear();

    } else
    {
        qDebug() << "echec de l'ajout: " << query.lastError().text();

    }
    dbAcess.close();
}


