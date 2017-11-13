#ifndef XMLCONFIG_H
#define XMLCONFIG_H

#include <QMap>
class XMLConfig
{
public:
    XMLConfig();
    QMap<QString,QString> read(QString filepath);
    void write(QString filePath, QMap<QString, QString> xml);
    void write(QString filePath,QString xml);
};

#endif // XMLCONFIG_H
