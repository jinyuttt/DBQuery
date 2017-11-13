#include "frmdbmain.h"
#include "ui_frmdbmain.h"

FrmDBMain::FrmDBMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmDBMain)
{
    ui->setupUi(this);

}

FrmDBMain::~FrmDBMain()
{
    delete ui;
}
