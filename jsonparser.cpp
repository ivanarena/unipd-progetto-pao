#include "jsonparser.h"
#include <QByteArray>
#include <QList>
#include <QVariant>

DataTableModel* JsonParser::load(const QString& path) const {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray loading = file.readAll();
    QJsonDocument JDoc = QJsonDocument::fromJson(loading);
    //if(!JDoc.isObject()) throw error;
    const QJsonObject JObj = JDoc.object();
    vector<vector<string>> headers;
    vector<string> h_col;
    vector<string> h_row;
    headers.push_back(h_col);
    headers.push_back(h_row);
    vector<vector<double>> values;

// ===============================   COLONNE:
    const QJsonValue columns_headers =  JObj[QString("Columns")];
    //if(!rows_headers.isArray()) throw errore
    const QJsonArray columns_head = columns_headers.toArray();
    int col_Count=0;
    for(auto it = columns_head.cbegin(); it!=columns_head.cend(); ++it){
        col_Count++;
        headers[0].push_back(((*it).toString()).toStdString());
    }
// ================================================



// ===============================  RIGHE:
    const QJsonValue rows = JObj[QString("Rows")];
    //if(!columns.isObject()) throw Errore;
    const QJsonObject colObj=rows.toObject();
    const QMap<QString,QVariant> rows_map = colObj.toVariantMap();
    int row_Count=0;
    int checkcol;
    for(auto it = rows_map.constBegin(); it!=rows_map.constEnd(); ++it){
        headers[1].push_back((it.key()).toStdString());
        checkcol=0;
        //if(!(it.value()).canConvert<QJsonArray>()) throw Errore;
        const QJsonArray row_Array = it.value().toJsonArray();
        vector<double> v;
        values.push_back(v);
        for(auto vit = row_Array.cbegin(); vit!= row_Array.cend(); vit++){
            values[row_Count].push_back((*vit).toDouble());
        }
        //if(checkcol!=col_Count) throw Erroe;
        row_Count++;
    }
// ================================================
    file.close();
    return new DataTableModel(nullptr, row_Count, col_Count, values, headers);
}
