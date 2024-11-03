#ifndef REPPORTGENERATOR_H
#define REPPORTGENERATOR_H
#include"QVector"

class RepportGenerator
{
public:
    RepportGenerator();
    int bookSatistics();
    QVector<QVector<QString>> loadTopEmpruntedBook();
};

#endif // REPPORTGENERATOR_H
