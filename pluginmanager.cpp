#include "pluginmanager.h"
#include <QDir>
#include <QPluginLoader>
#include "iqpluginui.h"
#include "objectfactory.h"
void PluginManager::initPlugin(QString path)
{
    //
    this->hash=new QHash<QString,QObject*>();
    this->map=new QMap<QString,QString>();
    QDir  pluginsDir = QDir(path);
     pluginsDir.cd("plugins");
     foreach (QString fileName,pluginsDir.entryList(QDir::Files))
     {
             QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
              QObject *plugin = loader.instance();
                if (plugin)
                {
               IQPluginUi *iplugin = qobject_cast<IQPluginUi *>(plugin);
               QHash<QString,QObject*> tmpHash=  iplugin->createHashObject();
               QMap<QString,QString>  tmpMap=iplugin->getRegister();
               QHash<QString, QObject*>::const_iterator i=tmpHash.constBegin();
               while(i!=tmpHash.constEnd())
               {
                   hash->insert(i.key(),i.value());
                   ++i;
               }
               //
                  QMap<QString, QString>::const_iterator j=tmpMap.constBegin();
                  while(j!=tmpMap.constEnd())
                  {
                      map->insert(j.key(),j.value());
                      ++j;
                  }
                }

     }
}

void PluginManager::loadPlugins(QString path)
{

    PluginRead rd;
    rd.readConfig(path);
    //
    QMap<QString,PluginInfo> mapObj=rd.getPluginObj();
    QMap<int,QString >mapid=rd.getPluginNo();
    istab=rd.getUI();
    mapPlugins.unite(mapObj);
     mapNo.unite(mapid);

   //
   QMap<QString,PluginInfo>::iterator it;
   for(it=mapPlugins.begin();it!=mapPlugins.end();++it)
   {
       if(it.value().pluginObj==NULL)
       {
         createPlugin(it.value(), it.value().pluginPath);
       }
   }
}

bool PluginManager::createPlugin(PluginInfo& plugin, QString fPath)
{
    QPluginLoader pluginLoader(fPath);
    QObject* pluginObj = pluginLoader.instance();
   if(pluginObj)
   {
      IQPluginUi  *p = qobject_cast<IQPluginUi*>(pluginObj);
        if(p)
        {
          int r=p->getCreateWay();
          QObject  *obj;
          switch (r) {
          case 1:
             obj= p->createObject();
             plugin.pluginObj=obj;
              break;
           case 2:
             obj= p->createObject(plugin.pluginCls);
              break;
          case 3:
          {
               QHash<QString,QString> hash;
               QMap<QString, QString>::const_iterator it;
               for (it = plugin.mapArg.constBegin(); it !=plugin.mapArg.constEnd(); ++it) {
                   hash.insert(it.key(),it.value());
               }
               obj=p->createObject(hash);
               plugin.pluginObj=obj;
               break;
          }
          case 4:
          {
             QHash<QString, QObject*> mobj=p->createHashObject();
           //

             QHash<QString, QObject*>::const_iterator it;
             for (it = mobj.constBegin(); it != mobj.constEnd(); ++it) {
                 QMap<QString,PluginInfo>::iterator mi= mapPlugins.find(it.key());
                 if(mi!=mapPlugins.constEnd())
                 {
                     mi.value().pluginObj=it.value();
                     mapPlugins[it.key()]=mi.value();

                 }
             }
              break;
          }
          case 5:
          {
             QMap<QString,QString> nobj=p->getRegister();
             QMap<QString,QString>::const_iterator it;
             for(it=nobj.constBegin();it!=nobj.constEnd();++it)
             {
                 QMap<QString,PluginInfo>::iterator mi= mapPlugins.find(it.key());
                 if(mi!=mapPlugins.constEnd())
                 {
                     QString cls=it.value();
                     obj= ObjectFactory::createObject(cls.toLatin1());
                     mi.value().pluginObj=obj;
                     mi.value().pluginCls=cls;
                     mapPlugins[it.key()]=mi.value();
                 }
             }
             break;
          }
          default:
              break;
          }
        }
        else{
                  printf("plugin not load./n");
            }
   }
   return true;
}
PluginManager* PluginManager::m_pInstance = nullptr;
