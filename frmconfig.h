#ifndef FRMCONFIG_H
#define FRMCONFIG_H

#include <QWidget>

namespace Ui {
class FrmConfig;
}

class FrmConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FrmConfig(QWidget *parent = 0);
    ~FrmConfig();

private:
    Ui::FrmConfig *ui;
};

#endif // FRMCONFIG_H
