#ifndef POWER_H
#define POWER_H

#include <QWidget>

namespace Ui {
class power;
}

class power : public QWidget
{
    Q_OBJECT

public:
    explicit power(QWidget *parent = nullptr);
    ~power();

private slots:
    void on_rebootBtn_clicked();

    void on_poweroffBtn_clicked();

    void on_backBtn_clicked();

private:
    Ui::power *ui;
};

#endif // POWER_H
