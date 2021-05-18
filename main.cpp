#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 //   a.setWindowIcon(QIcon(":/icons/icon.png"));
    Dialog w;
    w.show();
    return a.exec();
}
