#include "diagswindow.h"
#include "ui_diagswindow.h"

#include <QMessageBox>
#include <QProcess>

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
        ui->checkBox_4->hide(); // Downgrade checkbox
        ui->label_4->hide();
        ui->label_5->hide();
        ui->shellBtn->hide();
        ui->softwareOptionsBtn->hide();
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
    QMessageBox::information(this, tr("Kernel version"), kernel_file_str);
}

void diagsWindow::on_checkBox_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/DIAGS_BOOT", "true");
    }
    else {
        string_writeconfig("/boot/flags/DIAGS_BOOT", "false");
    }
}

void diagsWindow::on_checkBox_2_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/FIRST_BOOT", "true");
    }
    else {
        string_writeconfig("/boot/flags/FIRST_BOOT", "false");
    }
}

void diagsWindow::on_checkBox_3_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/USBNET_ENABLE", "true");
    }
    else {
        string_writeconfig("/boot/flags/USBNET_ENABLE", "false");
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
    QMessageBox::information(this, tr("Kernel version"), tr("USBNet is set up and a telnet server was started.\nIP: 192.168.2.2"));
}

void diagsWindow::on_checkBox_4_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/ALLOW_DOWNGRADE", "true");
    }
    else {
        string_writeconfig("/boot/flags/ALLOW_DOWNGRADE", "false");
    }
}

void diagsWindow::on_checkBox_5_toggled(bool checked)
{
    if(checked == true) {
        string_writeconfig("/boot/flags/X11_START", "true");
    }
    else {
        string_writeconfig("/boot/flags/X11_START", "false");
    }
}
