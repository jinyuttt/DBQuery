#ifndef PLUGINREAD_H
#define PLUGINREAD_H

#include "plugininfo.h"
#include<QXmlStreamReader>
class PluginRead
{
public:
    PluginRead();
    QMap<QString,PluginInfo> getPluginObj();
    QMap<int,QString> getPluginNo();
    void readConfig(QString file);
     bool getUI();
public:
     QString pluginXml="plugin.xml";
private:
    PluginInfo  parsePlugin(QXmlStreamReader& xml);
    void addElementDataToPlugin(QXmlStreamReader& xml, PluginInfo& plugin);
     void addElementDataToMap(QXmlStreamReader& xml, QMap<QString,QString>& arg);
private:
     QMap<QString,PluginInfo> obj;
     QMap<int,QString> no;
     bool istab=false;
};

#endif // PLUGINREAD_H
