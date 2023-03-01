#include "diagswindow.h"
#include "ui_diagswindow.h"

#include <QMessageBox>
#include <QProcess>
#include <QDebug>

diagsWindow::diagsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::diagsWindow)
{
    ui->setupUi(this);

    ui->getBattLevelBtn->setStyleSheet("font-size: 10pt; padding: 30px");
    ui->getKernelBtn->setStyleSheet("font-size: 10pt; padding: 30px");
    ui->powerOptionsBtn->setStyleSheet("font-size: 10pt; padding: 30px");
    ui->resetOptionsBtn->setStyleSheet("font-size: 10pt; padding: 30px");
    ui->softwareOptionsBtn->setStyleSheet("font-size: 10pt; padding: 30px");
    ui->shellBtn->setStyleSheet("font-size: 10pt; padding: 30px");

    // Setting some checkboxes based on the value of the flags in /boot/flags
    if(checkconfig("/boot/flags/DIAGS_BOOT") == true) {
        ui->checkBox->click();
    }
    if(checkconfig("/boot/flags/FIRST_BOOT") == true) {
        ui->checkBox_2->click();
    }
    if(checkconfig("/boot/flags/X11_START") == true) {
        ui->checkBox_5->click();
    }
    if(checkconfig("/boot/flags/DISPLAY_DEBUG") == true) {
        ui->displayDebugCheckBox->click();
    }
    if(checkconfig("/boot/flags/GUI_DEBUG") == true) {
        ui->guiDebugCheckBox->click();
    }
    if(checkconfig("/boot/flags/IPD_DEBUG") == true) {
        ui->ipdDebugCheckBox->click();
    }

    // Check if device is rooted
    if(checkconfig("/opt/root/rooted") == true) {
        rooted = true;
        if(checkconfig("/boot/flags/USBNET_ENABLE") == true) {
            ui->checkBox_3->click();
        }
        if(checkconfig("/boot/flags/ALLOW_DOWNGRADE") == true) {
            ui->checkBox_4->click();
        }
    }
    else {
        rooted = false;
        ui->checkBox_3->hide(); // USBNet checkbox
        ui->checkBox_3->deleteLater();
        ui->checkBox_4->hide(); // Downgrade checkbox
        ui->checkBox_4->deleteLater();
        ui->label_4->hide();
        ui->label_4->deleteLater();
        ui->label_5->hide();
        ui->label_5->deleteLater();
        ui->shellBtn->hide();
        ui->shellBtn->deleteLater();
        ui->softwareOptionsBtn->hide();
        ui->softwareOptionsBtn->deleteLater();
    }

    // Stylesheet
    QFile stylesheetFile(":/eink.qss");
    stylesheetFile.open(QFile::ReadOnly);
    this->setStyleSheet(stylesheetFile.readAll());
    stylesheetFile.close();
}

diagsWindow::~diagsWindow()
{
    delete ui;
}


void diagsWindow::on_getBattLevelBtn_clicked()
{
    get_battery_level();
    QString msg = "Current battery level: ";
    msg.append(batt_level);
    QMessageBox::information(this, tr("Battery level info"), msg);
}

void diagsWindow::on_resetOptionsBtn_clicked()
{
    resetWindow = new resetMenu();
    resetWindow->setAttribute(Qt::WA_DeleteOnClose);
    resetWindow->showFullScreen();
}

void diagsWindow::on_softwareOptionsBtn_clicked()
{
    softwareWindow = new software();
    softwareWindow->setAttribute(Qt::WA_DeleteOnClose);
    softwareWindow->showFullScreen();
}

void diagsWindow::on_powerOptionsBtn_clicked()
{
    powerWindow = new power();
    powerWindow->setAttribute(Qt::WA_DeleteOnClose);
    powerWindow->showFullScreen();
}

void diagsWindow::on_getKernelBtn_clicked()
{
    get_kernel_version();
    QMessageBox::information(this, "Kernel version", "<font face='Noto Mono'>" + kernel_file_str + "</font>");
}

void diagsWindow::on_checkBox_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/DIAGS_BOOT", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/DIAGS_BOOT", "false\n");
    }
}

void diagsWindow::on_checkBox_2_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/FIRST_BOOT", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/FIRST_BOOT", "false\n");
    }
}

void diagsWindow::on_checkBox_3_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/USBNET_ENABLE", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/USBNET_ENABLE", "false\n");
    }
}

void diagsWindow::on_shellBtn_clicked()
{
    QString prog ("sh");
    QStringList args;
    args << "/opt/recovery/scripts/telnet_shell.sh";
    QProcess *proc = new QProcess();
    proc->start(prog, args);
    proc->waitForFinished();
    if(QFile::exists("/boot/flags/USBNET_IP")) {
        QString ip = readFile("/boot/flags/USBNET_IP");
        if(!ip.isEmpty()) {
            QMessageBox::information(this, "USBNet Info", "USBNet has been set up and a telnet server was started.\nIP: " + ip);
        }
        else {
            QMessageBox::information(this, "USBNet Info", "USBNet has been set up and a telnet server was started.\nIP: 192.168.2.2");
        }
    }
    else {
        QMessageBox::information(this, "USBNet Info", "USBNet has been set up and a telnet server was started.\nIP: 192.168.2.2");
    }
}

void diagsWindow::on_checkBox_4_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/ALLOW_DOWNGRADE", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/ALLOW_DOWNGRADE", "false\n");
    }
}

void diagsWindow::on_checkBox_5_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/X11_START", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/X11_START", "false\n");
    }
}

QString diagsWindow::readFile(QString file) {
    if(QFile::exists(file)) {
        QFile fileToRead(file);
        fileToRead.open(QIODevice::ReadOnly);
        QTextStream in (&fileToRead);
        QString content = in.readAll();
        return content;
    }
    else {
        return NULL;
    }
}

void diagsWindow::on_displayDebugCheckBox_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/DISPLAY_DEBUG", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/DISPLAY_DEBUG", "false\n");
    }
}


void diagsWindow::on_guiDebugCheckBox_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/GUI_DEBUG", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/GUI_DEBUG", "false\n");
    }
}

void diagsWindow::on_ipdDebugCheckBox_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/IPD_DEBUG", "true\n");
    }
    else {
        string_writeconfig("/boot/flags/IPD_DEBUG", "false\n");
    }
}
