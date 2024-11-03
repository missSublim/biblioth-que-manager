#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <addmember.h>
#include <QWidget>

namespace Ui {
class MemberManager;
}

class MemberManager : public QWidget
{
    Q_OBJECT

public:
    explicit MemberManager(QWidget *parent = nullptr);
    ~MemberManager();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MemberManager *ui;
    AddMember *addMember= new AddMember();
    void displayMember();
    void onDeleteButtonClicked(int row);
    void onEditButtonClicked(int row);
};

#endif // MEMBERMANAGER_H
