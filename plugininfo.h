#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QMap>
# include <QObject>
class PluginInfo
{
public:
    PluginInfo();
    QMap<QString,QString> mapArg;
    QString  pluginName;
    QString  pluginICO;
    QString  pluginPath;
    QString  pluginCls;
    QObject* pluginObj=NULL;
    QString pluginNO;
};

#endif // PLUGININFO_H
