#ifndef MODIFYBOOK_H
#define MODIFYBOOK_H

#include <QWidget>

namespace Ui {
class ModifyBook;
}

class ModifyBook : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyBook(QWidget *parent = nullptr);
    ~ModifyBook();
    QString getTitre();
    QString getAuteur();
    QString getGenre();
    QString getDateAjout();

signals:
    void soumissionClicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ModifyBook *ui;
};

#endif // MODIFYBOOK_H
