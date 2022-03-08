#include "jsonparser.h"
#include <QByteArray>
#include <QList>
#include <QVariant>

#include "parsingerror.h"
#include <iostream>


DataTableModel* JsonParser::load(const QString& path) const {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray loading = file.readAll();
    QJsonDocument JDoc = QJsonDocument::fromJson(loading);
    //if(!JDoc.isObject()) throw new parsingError;                        //<-----
    QJsonObject JObj = JDoc.object();
    vector<QVariant> columnsHeaders;
    vector<QVariant> rowsHeaders;
    vector<vector<double>> values;

// ===============================   COLONNE:
    QJsonValue JV_columns =  JObj[QString("Columns")];
    //if(!rowsHeaders.isArray()) throw new parsingError();              //<----
    QJsonArray JA_columns = JV_columns.toArray();
    int col_Count=0;
    for(auto it = JA_columns.begin(); it!=JA_columns.end(); ++it){
        cout<<"ssss"<<endl;
        col_Count++;
        columnsHeaders.push_back(((*it).toVariant()));
    }
// ================================================



// ===============================  RIGHE:
    QJsonValue JV_rows = JObj[QString("Rows")];
    //if(!column.isObject()) throw new parsingError();
    QJsonObject rowsObj=JV_rows.toObject();
    QMap<QString,QVariant> rows_map = rowsObj.toVariantMap();
    int row_Count=0;
    int checkcol;
    for(auto it = rows_map.begin(); it!=rows_map.end(); ++it){
        cout<<"bb"<<endl;
        rowsHeaders.push_back((it.key()));
        //if(!(it.value()).canConvert<QJsonArray>()) throw new parsingError();
        cout<<it.value().typeName();
        QList<QVariant> row_Array = (it.value()).toList();
        values.push_back(*(new vector<double>));
        checkcol=0;
        cout<<row_Array[1].toDouble()<<endl;
        for(auto vit = row_Array.begin(); vit!= row_Array.end(); ++vit){
            values[row_Count].push_back((*vit).toDouble());
            checkcol++;
            std::cout<<"aa"<<endl;
        }
        std::cout<<col_Count<<" "<<checkcol<<endl;
        if(checkcol!=col_Count) throw new parsingError();
        row_Count++;
    }
// ================================================
    file.close();
    return new DataTableModel(nullptr, row_Count, col_Count, values, columnsHeaders , rowsHeaders);
}

void JsonParser::save(DataTableModel * model, QFile& file) const{
    vector<QVariant> columnsHeaders = model->getColumnsHeaders();
    vector<QVariant> rowsHeaders = model->getRowsHeaders();
    vector<vector<double>> values = model->getData();
    QJsonObject finalObj;
    QJsonArray columns;
    for(vector<QVariant>::iterator it = columnsHeaders.begin(); it!= columnsHeaders.end(); ++it){
        columns.push_back(QJsonValue::fromVariant(*it));
    }
    finalObj.insert(QString("Columns"),columns);
    QJsonObject row_obj;
    for(std::pair<vector<vector<double>>::iterator,vector<QVariant>::iterator> it(values.begin(), rowsHeaders.begin() ); it.first!=values.end() && it.second!=rowsHeaders.end(); ++it.first, ++it.second ){
        QJsonArray r_values;
        for(vector<double>::iterator rv_it = (*it.first).begin(); rv_it!= (*it.first).end(); ++rv_it){
            r_values.push_back(*rv_it);
        }
    row_obj.insert((*it.second).toString(),r_values);
    }
    finalObj.insert("Rows",row_obj);
    QJsonDocument doc(finalObj);
    QByteArray saving =doc.toJson();
    file.write(saving);
}

