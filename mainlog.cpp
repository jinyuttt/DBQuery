#include "mainlog.h"
#include "ui_mainlog.h"

MainLog::MainLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainLog)
{
    ui->setupUi(this);
}

MainLog::~MainLog()
{
    delete ui;
}
