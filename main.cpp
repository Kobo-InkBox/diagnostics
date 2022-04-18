#include "diagswindow.h"

#include <QApplication>
#include <QRect>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setFont(QFont("u001"));
    diagsWindow w;
    const QScreen* screen = qApp->primaryScreen();
    w.setGeometry(QRect(QPoint(0,0), screen->geometry ().size()));
    w.show();
    return a.exec();
}
