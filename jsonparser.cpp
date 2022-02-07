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
    for(auto it = columns_head.begin(); it!=columns_head.end(); ++it){
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
        for(auto vit = row_Array.begin(); vit!= row_Array.end(); vit++){
            values[row_Count].push_back((*vit).toDouble());
        }
        //if(checkcol!=col_Count) throw Erroe;
        row_Count++;
    }
// ================================================
    file.close();
    return new DataTableModel(nullptr, row_Count, col_Count, values, headers);
}

void JsonParser::save(DataTableModel * model, QFile& file) const{
    vector<vector<string>> headers = model->getHeaders();
    vector<vector<double>> values = model->getValues();
    QJsonObject finalObj;
    QJsonArray columns;
    for(vector<string>::iterator it = (headers.front()).begin(); it!= (headers.front()).end(); ++it){
        columns.push_back(QJsonValue(QString::fromStdString(*it)));
    }
    finalObj.insert(QString("Columns"),columns);
    QJsonObject row_obj;
    for(std::pair<vector<vector<double>>::iterator,vector<string>::iterator> it(values.begin(),headers.back().begin()); it.first!=values.end() && it.second!=headers.back().end(); ++it.first, ++it.second ){
        QJsonArray r_values;
        for(vector<double>::iterator rv_it = (*it.first).begin(); rv_it!= (*it.first).end(); ++rv_it){
            r_values.push_back(*rv_it);
        }
    row_obj.insert(QString::fromStdString(*it.second),r_values);
    }
    finalObj.insert("Rows",row_obj);
    QJsonDocument doc(finalObj);
    QByteArray saving =doc.toJson();
    file.write(saving);
}
