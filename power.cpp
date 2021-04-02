#include "power.h"
#include "ui_power.h"

#include <QFile>
#include <QProcess>

power::power(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::power)
{
    ui->setupUi(this);

    // Stylesheet
    QFile stylesheetFile(":/eink.qss");
    stylesheetFile.open(QFile::ReadOnly);
    this->setStyleSheet(stylesheetFile.readAll());
    stylesheetFile.close();

    ui->backBtn->setStyleSheet("font-size: 10pt; padding: 25px");
    ui->rebootBtn->setStyleSheet("font-size: 10pt; padding: 25px");
    ui->poweroffBtn->setStyleSheet("font-size: 10pt; padding: 25px");
}

power::~power()
{
    delete ui;
}

void power::on_rebootBtn_clicked()
{
    QString prog ("sh");
    QProcess *proc = new QProcess();
    QStringList args;
    args << "/opt/recovery/scripts/reboot.sh";
    proc->startDetached(prog, args);
}

void power::on_poweroffBtn_clicked()
{
    QString prog ("sh");
    QProcess *proc = new QProcess();
    QStringList args;
    args << "/opt/recovery/scripts/poweroff.sh";
    proc->startDetached(prog, args);
}

void power::on_backBtn_clicked()
{
    power::close();
}
