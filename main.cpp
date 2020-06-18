#include "winframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("windows");

    WinFrame w;
    w.show();

    return a.exec();
}
