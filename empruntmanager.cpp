#include "empruntmanager.h"
#include "ui_empruntmanager.h"
#include "QSqlQuery"
#include "dbacess.h"
#include "QLayout"
#include "QSqlError"
#include "QMessageBox"

EmpruntManager::EmpruntManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmpruntManager)
{
    ui->setupUi(this);
    displayEmprunt();
}

EmpruntManager::~EmpruntManager()
{
    delete ui;
}
//method vers le formulaire d'ajout d'emprunt
void EmpruntManager::on_pushButton_4_clicked()
{
    addEmprunt->show();
}

void EmpruntManager::displayEmprunt()
{
    DBAcess dbacess;
    dbacess.open();


    ui->tableWidget->setColumnCount(8);
    QStringList headers = {  "id", "Nom", "Prenom", "ID Livre", "Titre Livre", "Date Emprunt", "Date Retour reelle", "Action" };
    ui->tableWidget->setHorizontalHeaderLabels(headers);


    QSqlQuery query(dbacess.db);
    query.prepare("SELECT  e.ID, m.Nom, m.Prenom, e.ID_Livre, l.Titre, e.Date_Emprunt,  e.Date_Retour_R "
                  "FROM Membre m "
                  "INNER JOIN Emprunt e ON m.IDMembre = e.ID_Membre "
                  "JOIN Livre l ON e.ID_Livre = l.IDLivre "
                  "WHERE l.isAvailable =:status");

    query.bindValue(":status","false");

    if (query.exec())
    {
        int row = 0;
        while (query.next())
        {
            ui->tableWidget->insertRow(row);


            QString id = query.value(0).toString();
            QString nom = query.value(1).toString();
            QString prenom = query.value(2).toString();
            QString idLivre = query.value(3).toString();
            QString titreLivre = query.value(4).toString();
            QString dateEmprunt = query.value(5).toString();
            QString dateRetourReelle = query.value(6).toString();


            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(id));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(nom));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(prenom));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(idLivre));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(titreLivre));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(dateEmprunt));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(dateRetourReelle));

            QPushButton *returnButton = new QPushButton("Retourner Livre");
            returnButton->setStyleSheet("background-color: blue; color: white; margin:3px;");

            // Utilisation correcte de l'ID du livre à l'intérieur du lambda
            connect(returnButton, &QPushButton::clicked, this, [this, row]() {
                this->returnLivre(row);
            });

            ui->tableWidget->setCellWidget(row, 7, returnButton);
            row++;
        }
    }
    else
    {
        qDebug() << "Erreur lors de la récupération des emprunts:" << query.lastError().text();
    }

    dbacess.close();
}


// Methode pour enregistrer retour
    void EmpruntManager::returnLivre(int row)
    {
        DBAcess dbacess;
        dbacess.open();


        QString  item= ui->tableWidget->item(row, 3)->text();
        QString idEmprunt = ui->tableWidget->item(row, 0)->text();

        int idLivre=item.toInt();


        QString isAvailable = "true";

        QSqlQuery query(dbacess.db);
        query.prepare("UPDATE Livre SET isAvailable =:isAvailable WHERE IDLivre =:id");



        query.bindValue(":isAvailable", isAvailable);
        query.bindValue(":id", idLivre);


        if (query.exec()) {
            QSqlQuery qry(dbacess.db);
            qry.prepare("DELETE from Emprunt WHERE ID =:id");
            qry.bindValue(":id", idEmprunt);
            if (qry.exec()){
                qDebug() << "L'emprunt a été supprimé avec succes";
                QMessageBox::information(this, "Retour du livre", "Le livre a été retourné avec succès !");
                displayEmprunt();
            }else{
                qDebug() << "Erreur" << qry.lastError().text() << idEmprunt ;
                QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors du retour du livre.");
            }

        } else {
            qDebug() << "Erreur lors du retour du livre:" << query.lastError().text() << idLivre ;
        }


        dbacess.close();
    }

