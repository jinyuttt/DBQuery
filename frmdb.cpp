#include "frmdb.h"
#include "ui_frmdb.h"
#include <QStringList>
#include<QDebug>
#include<QSqlError>
#include "datacloumn.h"
#include "datarow.h"
#include "datatable.h"
#include "datatabletojson.h"
#include "xmlconfig.h"
FrmDB::FrmDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmDB)
{
    ui->setupUi(this);
    //
   readConfig();
   //
   QLibrary  mylib("DBComTools");
   bool r=false;
   if(mylib.load())
   {
          typedef DBComTools*(*tools)();
          tools m_tool=(tools)mylib.resolve("getDBComTools");
          if(m_tool)
          {
              tool= m_tool();
              r=true;
              ui->lbl_Error->setText("加载DBTool正常");
          }
   }
   //
   if(!r)
   {
       ui->lbl_Error->setText("加载DBTool异常");
       ui->lbl_Error->setStyleSheet("color::red");
   }
}

FrmDB::~FrmDB()
{
    delete ui;
}

void FrmDB::readConfig()
{
    XMLConfig cf;
    QMap<QString, QString>::iterator it;
 QMap<QString,QString>  dbcf=cf.read("dbConfig.xml");
 it=dbcf.find("IP");
 if(it!=dbcf.end())
 {
     ui->txt_addr->setText(it.value());
 }
 it=dbcf.find("Port");
 if(it!=dbcf.end())
 {
     ui->txt_port->setText(it.value());
 }
 it=dbcf.find("Name");
 if(it!=dbcf.end())
 {
     ui->txt_name->setText(it.value());
 }
  it=dbcf.find("User");
 if(it!=dbcf.end())
 {
     ui->txt_user->setText(it.value());
 }
 it=dbcf.find("Psw");
 if(it!=dbcf.end())
 {
     ui->txt_psw->setText(it.value());
 }

 it=dbcf.find("DBType");
 if(it!=dbcf.end())
 {
     ui->txt_driver->setText(it.value());
 }
}

void FrmDB::on_btn_con_clicked()
{

   QSqlDatabase db=QSqlDatabase::addDatabase(databaseType,"dbReader");
   db.setHostName(hostName);
   db.setDatabaseName(databaseName);
   db.setUserName(username);
   db.setPassword(password);
   db.setPort(5432);
  bool r=  db.isValid();
  if(!r)
  {
       ui->lbl_result->setText("不支持驱动");
       return;
  }
  bool ok=  db.open();
  if(ok)
  {
     ui->lbl_result->setText("连接成功！");
     ui->lbl_result->setStyleSheet("color::black");
    // QPalette palette;
    // palette.setColor(QPalette::Text,Qt::black);
   //  ui->lbl_result->setPalette(palette);
  }
  else
  {
       ui->lbl_result->setText("连接失败！"+db.lastError ().text ());

  }
  db.close();
}

void FrmDB::on_btn_sql_clicked()
{

    QSqlDatabase db =tool->getDB();
    QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery(this->ui->txt_sql->text(),db);//这里直接设置SQL语句，忽略最后一个参数
      ui->tableView->setModel(model);
           //以下是视觉方面的效果，不加也没影响
           //隔行变色
           ui->tableView->setAlternatingRowColors(true);
           //设置行高
           int row_count = model->rowCount();
           for(int i =0; i < row_count; i++)
           {
               ui->tableView->setRowHeight(i, 20);
           }
      tool->closeConnectDB(db);
}

void FrmDB::on_btn_Test_clicked()
{
    // QSqlDatabase db =tool->getDB();
     DBArgModel model;
     model.sql=ui->txt_sql->text().trimmed();
     model.sqltype=Select;
     DBResult r= tool->exeSql(model,true);
     QString dt=  r.getJsonTable();
     if(dt.isNull()||dt.isEmpty())
     {
         qDebug()<<"没有数据信息返回";
     }
     else
         {
          qDebug()<<dt;
     }

}

void FrmDB::on_btn_save_clicked()
{
    QMap<QString,QString> map;
    map["IP"]=ui->txt_addr->text();
    map["Port"]=ui->txt_port->text();
    map["Name"]=ui->txt_name->text();
    map["User"]=ui->txt_user->text();
    map["Psw"]=ui->txt_psw->text();
    map["DBType"]=ui->txt_driver->text();
    XMLConfig cf;
    cf.write("dbConfig.xml",map);

}
