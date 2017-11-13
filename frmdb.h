#ifndef FRMDB_H
#define FRMDB_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include<QSqlQuery>
#include "connectionpool.h"
#include "dbcomtools.h"
namespace Ui {
class FrmDB;
}

class FrmDB : public QWidget
{
    Q_OBJECT

public:
    explicit FrmDB(QWidget *parent = 0);
    ~FrmDB();
   void readConfig();
private slots:
    void on_btn_con_clicked();

    void on_btn_sql_clicked();

    void on_btn_Test_clicked();
    
    void on_btn_save_clicked();

private:
     Ui::FrmDB *ui;
     QString   hostName     = "127.0.0.1";
     QString   databaseName = "postgres";
     QString    username     = "postgres";
     QString   password     = "1234";
     QString    databaseType = "QPSQL";
     DBComTools *tool;
};

#endif // FRMDB_H
