#ifndef FRMDBMAIN_H
#define FRMDBMAIN_H

#include <QMainWindow>

namespace Ui {
class FrmDBMain;
}

class FrmDBMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrmDBMain(QWidget *parent = 0);
    ~FrmDBMain();

private:
    Ui::FrmDBMain *ui;
};

#endif // FRMDBMAIN_H
