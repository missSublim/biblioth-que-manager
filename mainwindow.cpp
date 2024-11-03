#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statisticsTopBooks();
    getnomberofBooks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bookManager->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    memberManager->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    empruntManager->show();
}
void MainWindow::statisticsTopBooks(){


    RepportGenerator repportGenerator;
    QVector<QVector<QString>> topBooks = repportGenerator.loadTopEmpruntedBook();

    ui->tableWidget->setColumnCount(5);
    QStringList headers = { "Titre", "Date d'ajout", "Auteur", "Genre", "Nbrs d'emprunts" };
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (const QVector<QString>& book : topBooks) {
        ui->tableWidget->insertRow(row);
        for (int col = 0; col < book.size(); ++col) {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(book[col]));
        }
        row++;
    }
}
void MainWindow:: getnomberofBooks(){
    RepportGenerator repportGenerator;
    int nomberofBooks=repportGenerator.bookSatistics();
    ui->label->setText(QString::number(nomberofBooks)+"Livres");

}

