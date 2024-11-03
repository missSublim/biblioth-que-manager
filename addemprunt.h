#ifndef ADDEMPRUNT_H
#define ADDEMPRUNT_H

#include <QWidget>

namespace Ui {
class AddEmprunt;
}

class AddEmprunt : public QWidget
{
    Q_OBJECT

public:
    explicit AddEmprunt(QWidget *parent = nullptr);
    ~AddEmprunt();

private slots:
    void on_pushButton_clicked();


private:
    Ui::AddEmprunt *ui;
};

#endif // ADDEMPRUNT_H
