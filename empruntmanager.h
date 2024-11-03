#ifndef EMPRUNTMANAGER_H
#define EMPRUNTMANAGER_H

#include <QWidget>
#include <addemprunt.h>


namespace Ui {
class EmpruntManager;
}

class EmpruntManager : public QWidget
{
    Q_OBJECT

public:
    explicit EmpruntManager(QWidget *parent = nullptr);
    ~EmpruntManager();

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::EmpruntManager *ui;
    AddEmprunt *addEmprunt= new AddEmprunt();
    void displayEmprunt();
    void returnLivre(int row);
};

#endif // EMPRUNTMANAGER_H
