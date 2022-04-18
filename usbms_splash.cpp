#include "usbms_splash.h"
#include "ui_usbms_splash.h"

#include <QProcess>
#include <QThread>
#include <QScreen>

usbms_splash::usbms_splash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usbms_splash)
{
    ui->setupUi(this);
    ui->label->setFont(QFont("Inter"));
    ui->label->setStyleSheet("QLabel { color: black; font-size: 15pt; font-weight: bold }");
    ui->label_3->setStyleSheet("QLabel { color : black; font-size: 10pt }");

    // Getting the screen's size
    int sW = QGuiApplication::screens()[0]->size().width();
    int sH = QGuiApplication::screens()[0]->size().height();

    // Defining what the default icon size will be
    float stdIconWidth = sW / 1.15;
    float stdIconHeight = sH / 1.15;

    QPixmap pixmap(":/resources/usbms.png");
    QPixmap scaledPixmap = pixmap.scaled(stdIconWidth, stdIconHeight, Qt::KeepAspectRatio);
    QPixmap pixmap_1(":/resources/usbms_white.png");
    QPixmap scaledPixmap_1 = pixmap_1.scaled(stdIconWidth, stdIconHeight, Qt::KeepAspectRatio);
    ui->label_2->setPixmap(scaledPixmap_1);
    ui->label_4->hide();
    ui->label_4->setPixmap(scaledPixmap);
    QTimer::singleShot(100, this, SLOT(usbms_setup()));
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
    ui->label->setText("<b>USB connected</b>");
    ui->label_3->setText("Don't forget to eject the device before unplugging the USB cable.");
    ui->label->setStyleSheet("QLabel { background-color : black; color : white; font-size: 15pt }");
    ui->label_3->setStyleSheet("QLabel { background-color : black; color : white; font-size: 9pt}");
    ui->label_2->hide();
    ui->label_4->show();
}

usbms_splash::~usbms_splash()
{
    delete ui;
}
