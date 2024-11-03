#ifndef MODIFYMEMBER_H
#define MODIFYMEMBER_H

#include <QWidget>

namespace Ui {
class ModifyMember;
}

class ModifyMember : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyMember(QWidget *parent = nullptr);
    ~ModifyMember();
    QString getNom();
    QString getPrenom();
    QString getDateInscription();

signals:
    void soumissionClicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ModifyMember *ui;
};

#endif // MODIFYMEMBER_H
