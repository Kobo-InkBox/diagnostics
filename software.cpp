#include "software.h"
#include "ui_software.h"

#include <QFile>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QTextStream>

using namespace std;

software::software(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::software)
{
    ui->setupUi(this);

    ui->backBtn->setStyleSheet("font-size: 10pt; padding: 25px");
    ui->pushButton->setStyleSheet("font-size: 10pt; padding: 15px");
    ui->pushButton->setProperty("type", "borderless");
    ui->upgradeKernelBtn->setStyleSheet("font-size: 10pt; padding: 15px");
    ui->upgradeKernelBtn->setProperty("type", "borderless");

    // General stylesheet
    QFile stylesheetFile(":/eink.qss");
    stylesheetFile.open(QFile::ReadOnly);
    this->setStyleSheet(stylesheetFile.readAll());
    stylesheetFile.close();

    // Check if the device is rooted
    if(checkconfig("/opt/root/rooted") == true) {
        ui->upgradeKernelBtn->show();
        ui->label_3->show();
    }
    else {
        ui->upgradeKernelBtn->hide();
        ui->label_3->hide();
    }
}

software::~software()
{
    delete ui;
}

void software::on_pushButton_clicked()
{
    QMessageBox::information(this, tr("Information"), tr("The Kobo will now enter an USB mass storage session. Please put the relevant 'update.isa' file in the root of the USB storage, then eject and unplug."));

    usbmsWindow = new usbms_splash();
    usbmsWindow->setAttribute(Qt::WA_DeleteOnClose);
    usbmsWindow->showFullScreen();

    QTimer *usbms_t = new QTimer(this);
    usbms_t->setInterval(1000);
    connect(usbms_t, &QTimer::timeout, [&]() {
        QString prog ("/opt/recovery/scripts/mass_storage.sh");
        QStringList args;
        QProcess *proc = new QProcess();
        proc->start(prog, args);
        proc->waitForFinished();

        QFile modules("/tmp/usbevent");
        modules.open(QIODevice::ReadWrite);
        QTextStream in (&modules);
        const QString content = in.readAll();
        string contentstr = content.toStdString();
        modules.close();
        if(contentstr.find("1") != std::string::npos) {
            QString update_prog ("sh");
            QStringList update_args;
            update_args << "/opt/recovery/scripts/update_install.sh";
            QProcess *update_proc = new QProcess();
            update_proc->start(update_prog, update_args);
            update_proc->waitForFinished();
            usbms_t->stop();
        }
        else {
            ;
        }
    } );
    usbms_t->start();
}

void software::on_backBtn_clicked()
{
    software::close();
}

void software::on_upgradeKernelBtn_clicked()
{
    QMessageBox::information(this, tr("Information"), tr("The Kobo will now enter an USB mass storage session. Please put the relevant 'uImage' file in the root of the USB storage, then eject and unplug."));

    usbmsWindow = new usbms_splash();
    usbmsWindow->setAttribute(Qt::WA_DeleteOnClose);
    usbmsWindow->showFullScreen();

    QTimer *usbms_t = new QTimer(this);
    usbms_t->setInterval(1000);
    connect(usbms_t, &QTimer::timeout, [&]() {
        QString prog ("/opt/recovery/scripts/mass_storage.sh");
        QStringList args;
        QProcess *proc = new QProcess();
        proc->start(prog, args);
        proc->waitForFinished();

        QFile modules("/tmp/usbevent");
        modules.open(QIODevice::ReadWrite);
        QTextStream in (&modules);
        const QString content = in.readAll();
        string contentstr = content.toStdString();
        modules.close();
        if(contentstr.find("1") != std::string::npos) {
            QString reboot_prog ("sh");
            QStringList reboot_args;
            reboot_args << "/opt/recovery/scripts/kernel_upgrade.sh";
            QProcess *reboot_proc = new QProcess();
            reboot_proc->start(reboot_prog, reboot_args);
            reboot_proc->waitForFinished();
            usbms_t->stop();
        }
        else {
            ;
        }
    } );
    usbms_t->start();
}
