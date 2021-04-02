#include "usbms_splash.h"
#include "ui_usbms_splash.h"

#include <QProcess>
#include <QThread>
#include <QtConcurrent/QtConcurrent>

usbms_splash::usbms_splash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usbms_splash)
{
    ui->setupUi(this);
    QPixmap pixmap(":/resources/usbms_white.png");
    QPixmap pixmap_1(":/resources/usbms.png");
    ui->label_2->setPixmap(pixmap);
    ui->label_4->hide();
    ui->label_4->setPixmap(pixmap_1);
    ui->label_3->setStyleSheet("font-size: 9pt");
    QtConcurrent::run(this, &usbms_splash::usbms_setup);
}

void usbms_splash::usbms_setup() {
    // Here we set up an USB mass storage from a backing file extracted in a ramdisk.
    // Update files are generally no larger than 90 MB, so 140MiB of RAM space will probably be enough.

    QString prog ("sh");
    QStringList args;
    args << "/opt/recovery/scripts/update.sh";
    QProcess *proc = new QProcess();
    proc->start(prog, args);
    proc->waitForFinished();

    this->setStyleSheet("background-color:black;");
    ui->label->setText("USB connected");
    ui->label_3->setText("Don't forget to eject the device before unplugging the USB cable.");
    ui->label->setStyleSheet("QLabel { background-color : black; color : white; }");
    ui->label_3->setStyleSheet("QLabel { background-color : black; color : white; font-size: 9pt}");
    ui->label_2->hide();
    ui->label_4->show();
}

usbms_splash::~usbms_splash()
{
    delete ui;
}
