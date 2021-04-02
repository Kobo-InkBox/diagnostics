#include "diagswindow.h"

#include <QApplication>
#include <QRect>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    diagsWindow w;
    w.show();
    const QScreen* screen = qApp->primaryScreen();
    w.setGeometry(QRect(QPoint(0,0), screen->geometry ().size()));
    return a.exec();
}
