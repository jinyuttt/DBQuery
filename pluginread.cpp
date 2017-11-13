#include "pluginread.h"
#include <QTextStream>
#include <QXmlStreamReader>
#include <QFile>
PluginRead::PluginRead()
{

}

QMap<QString, PluginInfo> PluginRead::getPluginObj()
{

    return obj;

}

QMap<int, QString> PluginRead::getPluginNo()
{
    return no;
}

void PluginRead::readConfig(QString file)
{

    //将xml文件读取数据
    QFile f(file);
    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    //构建QXmlStreamReader对象
    QXmlStreamReader reader(&f);
    while(!reader.atEnd())
    {
    //判断是否是节点的开始
        reader.readNext();
    if(reader.isStartElement())
    {
      QString name=reader.name().toString().toLower();
      if(name=="config")
      {
          continue;
      }
      if(name=="plugin")
      {
          bool ok;
         PluginInfo p=  parsePlugin(reader);
         obj.insert(p.pluginName,p);
         no.insert(p.pluginNO.toInt(&ok,10),p.pluginName);

      }
      if(name=="ui")
      {
        QString  txt=  reader.readElementText();
        if(txt.toLower().trimmed()=="true")
        {
            istab=true;
        }
        else
        {
            istab=false;
        }
      }
         reader.readNext();
     }
    }
    }
    f.close();
}

bool PluginRead::getUI()
{
    return istab;
}

PluginInfo PluginRead::parsePlugin(QXmlStreamReader &xml)
{

    PluginInfo plugin;
       //检查是否获取person
       if(xml.tokenType() != QXmlStreamReader::StartElement &&
               xml.name().toString().toLower()== "plugin")
   {
           return plugin;
       }

       //获取person属性
       QXmlStreamAttributes attributes = xml.attributes();
       if(attributes.hasAttribute("id"))
       {
           //person["id"] = attributes.value("id").toString();
       }

   //操作下一个
       xml.readNext();
       while(!(xml.tokenType() == QXmlStreamReader::EndElement &&
               xml.name().toString().toLower() == "plugin"))
   {
           if(xml.tokenType() == QXmlStreamReader::StartElement)
   {
               if(xml.name() .toString().toLower()== "name")
   {
                   this->addElementDataToPlugin(xml, plugin);
               }

               if(xml.name().toString().toLower() == "no")
   {
                   this->addElementDataToPlugin(xml, plugin);
               }

               if(xml.name().toString().toLower() == "ico")
   {
                   this->addElementDataToPlugin(xml, plugin);
               }

               if(xml.name().toString().toLower() == "class")
               {
                   this->addElementDataToPlugin(xml, plugin);
               }
               if(xml.name().toString().toLower() == "dll")
               {
                   this->addElementDataToPlugin(xml, plugin);
               }
               if(xml.name().toString().toLower() == "arg")
               {
                   this->addElementDataToPlugin(xml, plugin);
               }
           }
           xml.readNext();
       }



       return plugin;
}

void PluginRead::addElementDataToPlugin(QXmlStreamReader &xml, PluginInfo &plugin)
{
    if(xml.tokenType() != QXmlStreamReader::StartElement)
    {
            return;
    }
        QString elementName = xml.name().toString().trimmed().toLower();
        xml.readNext();
        if(xml.tokenType() != QXmlStreamReader::Characters)
        {
            return;
        }
        QString txt=xml.text().toString();
     if(elementName=="name")
     {
         plugin.pluginName=txt;
     }
     if(elementName=="no")
     {
         plugin.pluginNO=txt;
     }
     if(elementName=="ico")
     {
         plugin.pluginICO=txt;
   }
     if(elementName=="class")
     {
         plugin.pluginCls=txt;
    }
     if(elementName=="dll")
     {
         plugin.pluginPath=txt;
     }
     if(elementName=="arg")
     {
           addElementDataToMap(xml,plugin.mapArg);
     }
}

void PluginRead::addElementDataToMap(QXmlStreamReader &xml, QMap<QString, QString> &arg)
{
    if(xml.tokenType() != QXmlStreamReader::StartElement)
   {
           return;
       }

       QString elementName = xml.name().toString();
       xml.readNext();

       if(xml.tokenType() != QXmlStreamReader::Characters)
   {
           return;
       }

       arg.insert(elementName, xml.text().toString());
}
