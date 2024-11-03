#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bookmanager.h>
#include <membermanager.h>
#include <empruntmanager.h>
#include <repportgenerator.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    BookManager *bookManager= new BookManager();
    MemberManager *memberManager= new MemberManager();
    EmpruntManager *empruntManager= new EmpruntManager();
    //RepportGenerator *repportGenerator= new RepportGenerator();
    void statisticsTopBooks();
    void getnomberofBooks();
};
#endif // MAINWINDOW_H
