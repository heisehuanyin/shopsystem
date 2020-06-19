#include "picswidget.h"
#include "winframe.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    DataModel::HostBase host;

    WinFrame w(&host);
    w.show();

    return a.exec();
}
