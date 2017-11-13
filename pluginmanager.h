#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
#include<QMap>
#include<QHash>
#include <QObject>
#include "plugininfo.h"
#include "pluginread.h"
class PluginManager
{
public:
    void initPlugin(QString path);
    void loadPlugins(QString path);
     QHash<QString,QObject*> *hash;
     QMap<QString,QString> *map;
    //
     QMap<QString,PluginInfo> mapPlugins;
     QMap<int,QString> mapNo;
     bool  istab=false;
public:
    static PluginManager* instance()
    {
        if (m_pInstance == nullptr)
        {
            m_pInstance = new PluginManager();
        }
        return m_pInstance;
    }

    static void Release()
    {
        if (m_pInstance != nullptr)
        {
            delete m_pInstance;
            delete m_pInstance->hash;
            delete m_pInstance->map;

            m_pInstance->hash=nullptr;
            m_pInstance->map=nullptr;
             m_pInstance = nullptr;
        }
    }
private:
    PluginManager(){}
    PluginManager(const PluginManager&){}
    PluginManager& operator==(const PluginManager&){}
    bool createPlugin(PluginInfo &plugin, QString fPath);
private:
    static PluginManager* m_pInstance;
};

#endif // PLUGINMANAGER_H
