#include "datatabletojson.h"


DataTableToJson::DataTableToJson()
{

}

QString DataTableToJson::toJson(DataTable dt)
{
    QJsonObject jdt;
    QJsonArray jcol;
    QJsonObject dcol;
    QJsonArray jrow;

   //列
    QList<DataCloumn>::iterator i;
   for (i = dt.col->begin(); i != dt.col->end(); ++i) {

        QJsonObject jcols=toJson(*i);
        jcol.push_back(jcols);
   }
  //行
  QList<DataRow>::iterator j;
  for (j = dt.rowList->begin();j!= dt.rowList->end();++j) {

       QJsonObject jcols=toJson(*j);
       jrow.push_back(jcols);
  }
  // 数据
  jdt.insert("index",dt.index);
  jdt.insert("rowNum",dt.rowNum);
  jdt.insert("colNum",dt.colNum);
  //
  jdt.insert("col",jcol);
  jdt.insert("rowList",jrow);
   return QString(QJsonDocument(jdt).toJson());
}

QJsonObject DataTableToJson::toJson(const DataRow &row)
{
    QJsonObject jrow;
    jrow.insert("rowNo",row.rowNo);
    //
     QVariant vrt(row.data);
    jrow.insert("data",vrt.toJsonValue());
    // QJsonArray datas=QJsonArray::fromVariantList(row.data);
    // jrow.insert("data",datas);
    return jrow;
}

QJsonObject DataTableToJson::toJson(const DataCloumn &col)
{
    QJsonObject jcol;
    jcol.insert("cloumnType",col.cloumnType);
    jcol.insert("length",col.length);
    jcol.insert("name",col.name);
    return jcol;
}
