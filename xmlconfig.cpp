#include "xmlconfig.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QTextStream>
XMLConfig::XMLConfig()
{

}

QMap<QString, QString> XMLConfig::read(QString filepath)
{
    QMap<QString,QString> map;
    //将xml文件读取数据
    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    //构建QXmlStreamReader对象
    QXmlStreamReader reader(&file);
    while(!reader.atEnd())
    {
    //判断是否是节点的开始
        reader.readNext();
    if(reader.isStartElement())
    {

      QString name=reader.name().toString();
      if(name=="config")
      {
          continue;
      }
      QString txt=reader.readElementText();
      map[name]=txt;
    }
    }
    }
    return map;
    //将属性读出:例如 id="3" age = "23">
   // QXmlStreamAttributes attributes = reader.attributes();
//    //判断是否存在属性"id"
//    if(attributes.hasAttribute("id"))
//    {
//    //将属性id追加textBrower
//    ui->textBrowser->append(QString("id:%1").arg(attributes.value("id").toString()));
//    }
//    //判断当前节点的名字是否为Number
//    if(reader.name() == "Number")
//     ui->textBrowser->append(QString("Number:%1").arg(reader.readElementText()));
//    //判断当前节点的名字是否为Name
//     else if(reader.name() == "Name")
//    ui->textBrowser->append(QString("Name:%1").arg(reader.readElementText()));
//     //判断当前节点的名字是否为email
//     else if(reader.name() == "email")
//     ui->textBrowser->append(QString("email:%1").arg(reader.readElementText()));
//    //判断当前节点的名字是否为website
//     else if(reader.name() == "website")
//     ui->textBrowser->append(QString("website:%1").arg(reader.readElementText()));
//    }
//     //节点结束、并且节点名字为Data（含有子节点）
//    else if(reader.isEndElement() && reader.name() == "Data")
//    {
//      ui->textBrowser->append("----------------");
//    }

}

void XMLConfig::write(QString filePath, QMap<QString,QString> xml)
{
   QFile file(filePath);
   if(file.open(QIODevice::WriteOnly|QIODevice::Text))
      {
            QXmlStreamWriter writer(&file);
              writer.setAutoFormatting(true);
              //设置自动缩进大小
              writer.setAutoFormattingIndent( 2 );
              //写入xml文档头，一般为： \<?xml version="1.0" encoding="UTF-8"?>
              writer.writeStartDocument();
              //写入开始标记FileMsg
                writer.writeStartElement("config");
                QMap<QString,QString>::const_iterator it;
                for(it=xml.constBegin();it!=xml.constEnd();it++)
                {
                    writer.writeTextElement(it.key(),it.value());
                }
                writer.writeEndElement();
                writer.writeEndDocument();
                file.close();
   }
}

void XMLConfig::write(QString filePath, QString xml)
{
     QFile file(filePath);
     QTextStream txtOutput(&file);
     txtOutput<<xml;
     file.close();

}
