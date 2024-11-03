#include "modifymember.h"
#include "ui_modifymember.h"

ModifyMember::ModifyMember(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModifyMember)
{
    ui->setupUi(this);
}

ModifyMember::~ModifyMember()
{
    delete ui;
}
void ModifyMember::on_pushButton_clicked()
{
    emit soumissionClicked();
}
QString ModifyMember:: getNom(){
    return ui->nomLineEdit->text();
}
QString ModifyMember:: getPrenom(){
    return ui->prenomLineEdit->text();
}
QString ModifyMember:: getDateInscription(){
    return ui->dateDInscriptionLineEdit->text();
}
