#include "membermanager.h"
#include "ui_membermanager.h"
#include "modifymember.h"
#include "addmember.h"
#include "dbacess.h"
#include "QMessageBox"
#include "QSqlError"
#include "QSqlQuery"
#include "QLayout"

MemberManager::MemberManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemberManager)
{
    ui->setupUi(this);
    displayMember();
}

MemberManager::~MemberManager()
{
    delete ui;
}
//rechercher un membre
void MemberManager::on_pushButton_5_clicked()
{
        DBAcess dbacess;
        dbacess.open();

        QString searchText = ui->lineEdit->text();

        QSqlQuery query(dbacess.db);
        query.prepare("SELECT * FROM Membre WHERE IDMembre=:id OR Nom LIKE :nom");
        query.bindValue(":id", searchText);
        query.bindValue(":nom", "%" + searchText + "%");

        if (query.exec())
        {
            // Configurer le QTableWidget
            ui->tableWidget->clear(); // éffacer les données existantes
            ui->tableWidget->setRowCount(0); // Reinitialiser les lignes

            // Definir le decompte des colones (4 colones pour les données + 1 colone pour les boutons)
            ui->tableWidget->setColumnCount(6);
            ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prenom" "Date d'inscription", "Actions"});

            int row = 0;
            while (query.next())
            {
                // Ajouter une nouvelle ligne à la QTableWidget
                ui->tableWidget->insertRow(row);

                // Remplir les cellules avec les données de la base de données
                for (int col = 0; col < 5; ++col)
                {
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
                }

                // Créer les boutons "Edit" et "Delete"
                QPushButton *editButton = new QPushButton("Modifier");
                QPushButton *deleteButton = new QPushButton("Supprimer");

                // Styler les boutons
                editButton->setStyleSheet("background-color: blue; color: white;");
                deleteButton->setStyleSheet("background-color: red; color: white;");

                // Créer un widget pour contenir les boutons
                QWidget *buttonWidget = new QWidget();
                QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
                layout->addWidget(editButton);
                layout->addWidget(deleteButton);
                layout->setContentsMargins(0, 0, 0, 0);
                buttonWidget->setLayout(layout);

                // Ajouter le widget avec boutons à la colone des actions
                ui->tableWidget->setCellWidget(row, 5, buttonWidget);

                // Connecter les boutons aux slots
                connect(editButton, &QPushButton::clicked, this, [this, row]() {
                    this->onEditButtonClicked(row);
                });
                connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
                    this->onDeleteButtonClicked(row);
                });

                ++row;
            }

            // Ajuster la taille des colones au besoin
            ui->tableWidget->resizeColumnsToContents();
        }
        else
        {
            qDebug() << "Echec de l'execution";
        }

        dbacess.close();
}

// acces au formulaire d'ajouter d'un membre
void MemberManager::on_pushButton_4_clicked()
{
    addMember->show();
}

// Methode pour afficher les membres
void MemberManager::displayMember()
{

    DBAcess dbacess;
    dbacess.open();

    // Query pour obtenir tous les membres
    QSqlQuery query(dbacess.db);
    query.prepare("SELECT  *FROM Membre");

    if (query.exec())
    {

        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);


        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderLabels({"IDMembre", "Nom", "Prenom", "Date_inscription", "Actions"});

        int row = 0;
        while (query.next())
        {

            ui->tableWidget->insertRow(row);


            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // IDMembre
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Nom
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Prenom
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // Date_inscription

            QPushButton *editButton = new QPushButton("Modifier");
            QPushButton *deleteButton = new QPushButton("Supprimer");


            editButton->setStyleSheet("background-color: blue; color: white; margin:5px;border-radius:5px; ");
            deleteButton->setStyleSheet("background-color: red; color: white;margin:5px; border-radius:5px; ");




            QWidget *buttonWidget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(buttonWidget);
            layout->addWidget(editButton);
            layout->addWidget(deleteButton);
            layout->setContentsMargins(0, 0, 0, 0);
            buttonWidget->setLayout(layout);


            ui->tableWidget->setCellWidget(row, 4, buttonWidget);


            connect(editButton, &QPushButton::clicked, this, [this, row]() {
                this->onEditButtonClicked(row);
            });
            connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
                this->onDeleteButtonClicked(row);
            });

            ++row;
        }


        ui->tableWidget->resizeColumnsToContents();

        qDebug() << "Membres affichés !";
    }
    else
    {
        qDebug() << "Echec de l'affichage: " << query.lastError().text();
    }


    dbacess.close();
}
// Methode pour supprimer des membres
void MemberManager::onDeleteButtonClicked(int row)
{
    QString id = ui->tableWidget->item(row, 0)->text();

    // Confirmer suppression
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Supprimer membre", "êtes-vous sûr de vouloir supprimer ce membre?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        DBAcess dbacess;
        dbacess.open();
        QSqlQuery query(dbacess.db);
        query.prepare("DELETE FROM Membre WHERE IDMembre = :ID");
        query.bindValue(":ID", id);

        if (query.exec()) {
            qDebug() << "Membre supprime avec succes";
            displayMember();
        } else {
            qDebug() << "echec de la suppression: " << query.lastError().text();
        }

        dbacess.close();
    }
}

// Methode pour modifier un membre
void MemberManager:: onEditButtonClicked(int row)
{

    QString id = ui->tableWidget->item(row, 0)->text();
    QString nom = ui->tableWidget->item(row, 1)->text();
    QString prenom = ui->tableWidget->item(row, 2)->text();
    QString Date_inscription = ui->tableWidget->item(row, 3)->text();

    ModifyMember *modifyMember= new ModifyMember();
    modifyMember->show();




    connect(modifyMember, &ModifyMember::soumissionClicked, this, [this, modifyMember, id]() {
        QString nom = modifyMember->getNom();
        QString prenom = modifyMember->getPrenom();
        QString date_inscription = modifyMember->getDateInscription();


        DBAcess dbacess;
        dbacess.open();
        QSqlQuery query(dbacess.db);
        query.prepare("update Membre set  Nom=:nom, Prenom=:prenom, Date_Inscription=:date_inscription WHERE IDMembre=:ID");

        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":date_inscription", date_inscription);
        query.bindValue(":ID", id);

        if (query.exec()) {
            qDebug() << "Membre modifié avec succes !";
            displayMember();
        } else {
            qDebug() << "Echec de la modification: " << query.lastError().text();
        }

        dbacess.close();
        modifyMember->deleteLater();
    });

}


