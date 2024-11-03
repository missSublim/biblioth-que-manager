#include "modifybook.h"
#include "ui_modifybook.h"

ModifyBook::ModifyBook(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModifyBook)
{
    ui->setupUi(this);
}

ModifyBook::~ModifyBook()
{
    delete ui;
}

void ModifyBook::on_pushButton_clicked()
{
    emit soumissionClicked();
}
QString ModifyBook:: getTitre(){
    return ui->titreLineEdit->text();
}
QString ModifyBook:: getAuteur(){
    return ui->auteurLineEdit->text();
}
QString ModifyBook:: getGenre(){
    return ui->genreLineEdit->text();
}
QString ModifyBook:: getDateAjout(){
    return ui->dateDAjoutLineEdit->text();
}
