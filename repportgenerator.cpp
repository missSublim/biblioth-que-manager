#include "repportgenerator.h"
#include "dbacess.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVector>

RepportGenerator::RepportGenerator() {

    }



    int RepportGenerator::bookSatistics() {
        DBAcess dbacess;
        dbacess.open();

        QSqlQuery query(dbacess.db);
        query.prepare("SELECT count(*) FROM Livre");
        int numbersOfBook = 0;
        if(query.exec()) {
            if(query.next()) {
                numbersOfBook = query.value(0).toInt();
                qDebug() << "Requête exécutée avec succès. Nombre de livres :" << numbersOfBook;
            }
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        }

        dbacess.close();
        return numbersOfBook;
    }


    QVector<QVector<QString>> RepportGenerator::loadTopEmpruntedBook() {
        DBAcess dbacess;
        dbacess.open();

        QVector<QVector<QString>> bookList;

        QSqlQuery query(dbacess.db);
        query.prepare(R"(
        SELECT L.Titre, L.Date_ajout, L.Auteur, L.Genre, COUNT(Em.ID_Livre) AS nombres_emprunts
        FROM Emprunt Em
        JOIN Livre L ON Em.ID_Livre = L.IDLivre
        GROUP BY L.Titre, L.Date_ajout, L.Auteur, L.Genre
        ORDER BY nombres_emprunts DESC
    )");

        if (query.exec()) {
            while (query.next()) {
                QVector<QString> row;
                row.append(query.value(0).toString()); // Titre
                row.append(query.value(1).toString()); // Date ajout
                row.append(query.value(2).toString()); // Auteur
                row.append(query.value(3).toString()); // Genre
                row.append(query.value(4).toString()); // Nombre emprunts

                bookList.append(row);
            }
        } else {
            qDebug() << "Erreur lors de la récupération des livres:" << query.lastError().text();
        }

        dbacess.close();
        return bookList;
}
