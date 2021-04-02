#ifndef SOFTWARE_H
#define SOFTWARE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

#include <usbms_splash.h>

using namespace std;

namespace Ui {
class software;
}

class software : public QWidget
{
    Q_OBJECT

public:
    explicit software(QWidget *parent = nullptr);
    ~software();
    bool checkconfig(QString file) {
        QFile config(file);
        config.open(QIODevice::ReadOnly);
        QTextStream in (&config);
        const QString content = in.readAll();
        string contentstr = content.toStdString();
        if(contentstr.find("true") != std::string::npos) {
            return true;
        }
        else {
            return false;
        }
        config.close();
    }

private slots:
    void on_pushButton_clicked();

    void on_backBtn_clicked();

    void on_upgradeKernelBtn_clicked();

private:
    Ui::software *ui;
    usbms_splash *usbmsWindow;
};

#endif // SOFTWARE_H
