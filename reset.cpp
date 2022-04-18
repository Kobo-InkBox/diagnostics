#include "reset.h"
#include "ui_reset.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QScreen>
#include <QTextFormat>
#include <QAbstractButton>
#include <QProcess>
#include <QWidget>
#include <QLabel>
#include <QInputDialog>
#include <QStringList>

resetMenu::resetMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reset)
{
    ui->setupUi(this);
    ui->backBtn->setFont(QFont("Inter"));
    ui->resetConfigBtn->setFont(QFont("Inter"));
    ui->hardResetBtn->setFont(QFont("Inter"));
    ui->hardResetRootBtn->setFont(QFont("Inter"));
    ui->softResetBtn->setFont(QFont("Inter"));

    // Stylesheet
    QFile stylesheetFile(":/eink.qss");
    stylesheetFile.open(QFile::ReadOnly);
    this->setStyleSheet(stylesheetFile.readAll());
    stylesheetFile.close();

    ui->hardResetBtn->setStyleSheet("font-size: 10pt; padding: 15px; font-weight: bold");
    ui->resetConfigBtn->setProperty("type", "borderless");
    ui->hardResetBtn->setProperty("type", "borderless");
    ui->resetConfigBtn->setStyleSheet("font-size: 10pt; padding: 15px; font-weight: bold");
    ui->backBtn->setStyleSheet("font-size: 10pt; padding: 25px; font-weight: bold");
    ui->hardResetRootBtn->setStyleSheet("font-size: 10pt; padding: 15px; font-weight: bold");
    ui->hardResetRootBtn->setProperty("type", "borderless");
    ui->softResetBtn->setStyleSheet("font-size: 10pt; padding: 15px; font-weight: bold");
    ui->softResetBtn->setProperty("type", "borderless");

    ui->label->setFont(QFont("Inter"));
    ui->label->setStyleSheet("font-weight: bold");
}

resetMenu::~resetMenu()
{
    delete ui;
}

void resetMenu::on_hardResetBtn_clicked()
{
    QStringList storageValues;
    storageValues << "64" << "256" << "512" << "1024";

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Onboard storage size"), tr("Onboard storage size (MiB):"), storageValues, 0, false, &ok);

    if (ok && !item.isEmpty())
            onboard_size = item;

    qDebug() << onboard_size;

    if(onboard_size != "") {
        QMessageBox msgBox;

        QFile stylesheetFile(":/eink.qss");
        stylesheetFile.open(QFile::ReadOnly);
        msgBox.setStyleSheet(stylesheetFile.readAll());
        stylesheetFile.close();

        msgBox.setText("<p align=center><b>Warning!</b><br>This will erase <b>anything</b> you saved on the device, either in the onboard storage or on the rootfs. Are you sure?</p>");
        QAbstractButton* yesBtn = msgBox.addButton(tr("Proceed"), QMessageBox::YesRole);
        QAbstractButton* noBtn = msgBox.addButton(tr("Go back"), QMessageBox::NoRole);

        ui->label_2->setStyleSheet("font-size: 9pt");
        ui->label_3->setStyleSheet("font-size: 9pt");

        yesBtn->setProperty("type", "borderless");
        yesBtn->setStyleSheet("font-size: 9pt; padding: 10px; font-weight: bold; background: lightGrey");
        noBtn->setProperty("type", "borderless");
        noBtn->setStyleSheet("font-size: 9pt; padding: 10px; font-weight: bold; background: lightGrey");

        msgBox.exec();

        if(msgBox.clickedButton() == yesBtn) {
            QString prog ("sh");
            QStringList args;
            args << "/opt/recovery/scripts/restore.sh" << onboard_size;
            QProcess *proc = new QProcess();
            proc->startDetached(prog, args);
            qApp->quit();
        }
        else {
            ;
        }
    }
    else {
        ;
    }
}

void resetMenu::on_backBtn_clicked()
{
    resetMenu::close();
}

void resetMenu::on_resetConfigBtn_clicked()
{
    QString prog ("sh");
    QStringList args;
    args << "/opt/recovery/scripts/reset-config.sh";
    QProcess *proc = new QProcess();
    proc->startDetached(prog, args);
    qApp->quit();
}

void resetMenu::on_hardResetRootBtn_clicked()
{
    QStringList storageValues;
    storageValues << "64" << "256" << "512" << "1024";

    bool ok;
    QString item = QInputDialog::getItem(this, tr("Onboard storage size"), tr("Onboard storage size (MiB):"), storageValues, 0, false, &ok);

    if (ok && !item.isEmpty())
            onboard_size = item;

    qDebug() << onboard_size;

    if(onboard_size != "") {
        QMessageBox msgBox;

        QFile stylesheetFile(":/eink.qss");
        stylesheetFile.open(QFile::ReadOnly);
        msgBox.setStyleSheet(stylesheetFile.readAll());
        stylesheetFile.close();

        msgBox.setText("<p align=center><b>Warning!</b><br>This will erase <b>anything</b> you saved on the device, either in the onboard storage or on the rootfs. Are you sure?</p>");
        QAbstractButton* yesBtn = msgBox.addButton(tr("Proceed"), QMessageBox::YesRole);
        QAbstractButton* noBtn = msgBox.addButton(tr("Go back"), QMessageBox::NoRole);

        ui->label_2->setStyleSheet("font-size: 9pt");
        ui->label_3->setStyleSheet("font-size: 9pt");

        yesBtn->setProperty("type", "borderless");
        yesBtn->setStyleSheet("font-size: 9pt; padding: 10px; font-weight: bold; background: lightGrey");
        noBtn->setProperty("type", "borderless");
        noBtn->setStyleSheet("font-size: 9pt; padding: 10px; font-weight: bold; background: lightGrey");

        msgBox.exec();

        if(msgBox.clickedButton() == yesBtn) {
            QString prog ("sh");
            QStringList args;
            args << "/opt/recovery/scripts/restore-root.sh" << onboard_size;
            QProcess *proc = new QProcess();
            proc->startDetached(prog, args);
            qApp->quit();
        }
        else {
            ;
        }
    }
    else {
        ;
    }
}

void resetMenu::on_softResetBtn_clicked()
{
    QString prog ("sh");
    QStringList args;
    args << "/opt/recovery/scripts/soft-reset.sh";
    QProcess *proc = new QProcess();
    proc->startDetached(prog, args);
    qApp->quit();
}
