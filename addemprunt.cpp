#include "addemprunt.h"
#include "ui_addemprunt.h"
#include "dbacess.h"
#include "QSqlQuery"
#include "QSqlError"
#include "QMessageBox"


AddEmprunt::AddEmprunt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddEmprunt)
{
    ui->setupUi(this);
}

AddEmprunt::~AddEmprunt()
{
    delete ui;
}
// Enregistrer un d'emprunt
void AddEmprunt::on_pushButton_clicked()
{
    DBAcess dbAcess;
    dbAcess.open();
    QString id_membre,nom_membre,prenom_membre,id_livre,titre_livre,date_emprunt,date_retour_p,date_retour_r;

    id_membre=ui->iDMembreLineEdit->text();
    nom_membre=ui->nomMembreLineEdit->text();
    prenom_membre=ui->prenomMembreLineEdit->text();
    id_livre=ui->iDLivreLineEdit->text();
    titre_livre=ui->titreLivreLineEdit->text();
    date_emprunt=ui->dateDEmpruntLineEdit->text();
    date_retour_p=ui->dateDeRetourPrevueLineEdit->text();
    date_retour_r=ui->dateDeRetourReelleLineEdit->text();

    QSqlQuery query(dbAcess.db);

    query.prepare("SELECT * FROM Livre WHERE IDLivre = :id_livre AND isAvailable =:status");
    query.bindValue(":id_livre", id_livre);
    query.bindValue(":status", "true");

    if(query.exec() &&  query.next()){

        QSqlQuery qry(dbAcess.db);

        // Insérer un nouvel emprunt
        qry.prepare("INSERT INTO Emprunt (ID_Membre, Nom_Membre, Prenom_Membre, ID_Livre, Titre_Livre, Date_Emprunt, Date_Retour_P, Date_Retour_R) "
                    "VALUES (:id_membre,:nom_membre, :prenom_membre, :id_livre, :titre_livre, :date_emprunt, :date_retour_p, :date_retour_r)");


    qry.bindValue(":id_membre", id_membre);
    qry.bindValue(":nom_membre", nom_membre);
    qry.bindValue(":prenom_membre", prenom_membre);
    qry.bindValue(":id_livre", id_livre);
    qry.bindValue(":titre_livre", titre_livre);
    qry.bindValue(":date_emprunt", date_emprunt);
    qry.bindValue(":date_retour_p", date_retour_p);
    qry.bindValue(":date_retour_r", date_retour_r);



    if (qry.exec()) {
        //QMessageBox::information(this, "Emprunt ajouté avec succés");
        qDebug("Emprunt Ajouté avec succes !");

        // Mettre à jour le statut du livre pour indiquer qu'il n'est plus disponible
        QSqlQuery updateQuery(dbAcess.db);
        updateQuery.prepare("UPDATE Livre SET isAvailable = :isAvailable WHERE IDLivre = :id");
        updateQuery.bindValue(":isAvailable", "false");  // Utilisation de 0 pour indiquer que le livre est emprunté
        updateQuery.bindValue(":id", id_livre);

        if (updateQuery.exec()) {
            qDebug() << "Statut du livre mis à jour avec à 'Non disponible' succès";

        } else {
            qDebug() << "Erreur lors de la mise à jour du statut du livre:" << updateQuery.lastError().text() << id_livre;
        }

        // Réinitialiser les champs du formulaire
        ui->iDMembreLineEdit->setText("");
        ui->nomMembreLineEdit->setText("");
        ui->prenomMembreLineEdit->setText("");
        ui->iDLivreLineEdit->setText("");
        ui->titreLivreLineEdit->setText("");
        ui->dateDEmpruntLineEdit->setText("");
        ui->dateDeRetourPrevueLineEdit->setText("");
        ui->dateDeRetourReelleLineEdit->setText("");
    } else
    {
        qDebug() <<"erreur lors de l'ajout" << qry.lastError().text();

    }
    }else{
        qDebug() << "Erreur sur la requête: " << query.lastError().text();
        QMessageBox::critical(this,"error","Le livre a déjà été emprunté");
    }

    dbAcess.close();
}



