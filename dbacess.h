#ifndef DBACESS_H
#define DBACESS_H
#include <QSqlDatabase>

class DBAcess
{
private:

public:
    QSqlDatabase db;
    QSqlDatabase database () { return db; }

    DBAcess();
    ~DBAcess();

    bool open();
    void close();
};

#endif // DBACESS_H
