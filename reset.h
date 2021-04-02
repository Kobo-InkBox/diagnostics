#ifndef RESET_H
#define RESET_H

#include <QWidget>
#include <QList>

namespace Ui {
class reset;
}

class resetMenu : public QWidget
{
    Q_OBJECT

public:
    explicit resetMenu(QWidget *parent = nullptr);
    ~resetMenu();
    QString onboard_size;

private slots:
    void on_hardResetBtn_clicked();

    void on_backBtn_clicked();

    void on_resetConfigBtn_clicked();

    void on_hardResetRootBtn_clicked();

    void on_softResetBtn_clicked();

private:
    Ui::reset *ui;
};

#endif // RESET_H
