#include "bookmanager.h"
#include "ui_bookmanager.h"
#include "QSqlQuery"
#include "dbacess.h"
#include "QLayout"
#include "QSqlError"
#include "QMessageBox"
#include "modifybook.h"


BookManager::BookManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookManager)
{
    ui->setupUi(this);
    displayBook();
}

BookManager::~BookManager()
{
    delete ui;
}
//  Methode pour rechercher un livre
void BookManager::on_pushButton_5_clicked()
{
    DBAcess dbacess;
    dbacess.open();

    QString searchText = ui->lineEdit->text();

    QSqlQuery query(dbacess.db);
    query.prepare("SELECT * FROM Livre WHERE IDLivre=:id OR Titre LIKE :titre");
    query.bindValue(":id", searchText);
    query.bindValue(":titre", "%" + searchText + "%");

    if (query.exec())
    {
        // Configurer le QTableWidget
        ui->tableWidget->clear(); // effacer les données existants
        ui->tableWidget->setRowCount(0); // Reinitialiser les lignes

        // Defit le décompte des colones (4 colones pour les données + 1 colone pour les boutons)
        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->setHorizontalHeaderLabels({"ID", "Titre", "Auteur", "Genre","Date d'ajout", "Actions"});

        int row = 0;
        while (query.next())
        {
            // Ajouter une nouvelle ligne à la QTableWidget
            ui->tableWidget->insertRow(row);

            // Peupler les cellules avec les données de la base de données
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

            // Ajouter le widget avec les boutons à la colone des actions
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

        // Aduster la taille des colones si necessaire
        ui->tableWidget->resizeColumnsToContents();
    }
    else
    {
        qDebug() << "Echec de l'execution ";
    }

    dbacess.close();
}

// Fonction vers le formulaire de l'ajout d'un livre
void BookManager::on_pushButton_4_clicked()
{
    addBook->show();

}
// Methode pour afficher les livres
void BookManager::displayBook()
{

    DBAcess dbacess;
    dbacess.open();

    // Query pour obtenir tous les livres
    QSqlQuery query(dbacess.db);
    query.prepare("SELECT  *FROM Livre");

    if (query.exec())
    {

        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);


        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->setHorizontalHeaderLabels({"ID", "Titre", "Auteur", "Date d'ajout", "Genre", "Actions"});

        int row = 0;
        while (query.next())
        {

            ui->tableWidget->insertRow(row);


            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Titre
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Auteur
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // Date
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // Genre


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


            ui->tableWidget->setCellWidget(row, 5, buttonWidget);


            connect(editButton, &QPushButton::clicked, this, [this, row]() {
                this->onEditButtonClicked(row);
            });
            connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
                this->onDeleteButtonClicked(row);
            });

            ++row;
        }


        ui->tableWidget->resizeColumnsToContents();

        qDebug() << "livres affichés avec succes!";
    }
    else
    {
        qDebug() << "Echec de l'affichage: " << query.lastError().text();
    }


    dbacess.close();
}

// Methode pour supprimer un livre
void BookManager::onDeleteButtonClicked(int row)
{
    QString id = ui->tableWidget->item(row, 0)->text();

    // Confirmer la suppression
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Book", "Are you sure you want to delete this book?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {

        DBAcess dbacess;
        dbacess.open();
        QSqlQuery query(dbacess.db);
        query.prepare("DELETE FROM Livre WHERE IDLivre = :ID");
        query.bindValue(":ID", id);

        if (query.exec()) {
            qDebug() << "Livre supprimé avec succes";
            displayBook();
        } else {
            qDebug() << "Echec de la suppression: " << query.lastError().text();
        }

        dbacess.close();
    }
}

// Methode pour modifier un livre
void BookManager:: onEditButtonClicked(int row)
{
    QString id = ui->tableWidget->item(row, 0)->text();
    QString title = ui->tableWidget->item(row, 4)->text();
    QString author = ui->tableWidget->item(row, 1)->text();
    QString genre = ui->tableWidget->item(row, 2)->text();
    QString date = ui->tableWidget->item(row, 3)->text();

    ModifyBook *modifyBook= new ModifyBook();
    modifyBook->show();




    connect(modifyBook, &ModifyBook::soumissionClicked, this, [this, modifyBook, id]() {
        QString titre = modifyBook->getTitre();
        QString auteur = modifyBook->getAuteur();
        QString genre = modifyBook->getGenre();
        QString date_ajout = modifyBook->getDateAjout();


        DBAcess dbacess;
        dbacess.open();
        QSqlQuery query(dbacess.db);
        query.prepare("update Livre set  Titre=:titre, Auteur=:auteur, Date_ajout=:date_ajout, Genre=:genre WHERE IDLivre=:ID");

        query.bindValue(":titre", titre);
        query.bindValue(":auteur", auteur);
        query.bindValue(":date_ajout", date_ajout);
        query.bindValue(":genre", genre);
        query.bindValue(":ID", id);

        if (query.exec()) {
            qDebug() << "Livre modifié avec succes !";
            displayBook();
        } else {
            qDebug() << "Echec de la modification: " << query.lastError().text();
        }

        dbacess.close();
        modifyBook->deleteLater();
    });

}


