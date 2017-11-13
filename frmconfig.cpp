#include "frmconfig.h"
#include "ui_frmconfig.h"

FrmConfig::FrmConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmConfig)
{
    ui->setupUi(this);
}

FrmConfig::~FrmConfig()
{
    delete ui;
}
