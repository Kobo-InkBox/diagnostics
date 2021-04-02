#ifndef DIAGSWINDOW_H
#define DIAGSWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>

#include <reset.h>
#include <software.h>
#include <power.h>
#include <usbms_splash.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class diagsWindow; }
QT_END_NAMESPACE

class diagsWindow : public QMainWindow
{
    Q_OBJECT

public:
    diagsWindow(QWidget *parent = nullptr);
    ~diagsWindow();
    QString batt_level;
    QString kernel_file_str;
    bool rooted;
    void get_battery_level() {
        QFile batt_level_file("/sys/devices/platform/pmic_battery.1/power_supply/mc13892_bat/capacity");
        batt_level_file.open(QIODevice::ReadOnly);
        batt_level = batt_level_file.readAll();
        batt_level = batt_level.trimmed();
        batt_level = batt_level.append("%");
        batt_level_file.close();
    }
    void get_kernel_version() {
        QFile kernel_file("/proc/version");
        kernel_file.open(QIODevice::ReadOnly);
        kernel_file_str = kernel_file.readAll();
        kernel_file.close();
    }
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
    void string_writeconfig(string file, string config_option) {
        ofstream fhandler;
        fhandler.open(file);
        fhandler << config_option;
        fhandler.close();
    }

private slots:
    void on_getBattLevelBtn_clicked();

    void on_resetOptionsBtn_clicked();

    void on_softwareOptionsBtn_clicked();

    void on_powerOptionsBtn_clicked();

    void on_getKernelBtn_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_shellBtn_clicked();

private:
    Ui::diagsWindow *ui;
    resetMenu *resetWindow;
    software *softwareWindow;
    power *powerWindow;
};
#endif // DIAGSWINDOW_H
