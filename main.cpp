#include "ComTerm.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComTerm w;
    w.show();
    return a.exec();
}
