#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <QWidget>
#include <addbook.h>


namespace Ui {
class BookManager;
}

class BookManager : public QWidget
{
    Q_OBJECT

public:
    explicit BookManager(QWidget *parent = nullptr);
    ~BookManager();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::BookManager *ui;
    AddBook *addBook= new AddBook();
    void displayBook();
    void onDeleteButtonClicked(int row);
    void onEditButtonClicked(int row);
};

#endif // BOOKMANAGER_H
