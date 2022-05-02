#include "jsonparser.h"
#include <QByteArray>
#include <QList>
#include <QVariant>

#include <iostream>

DataTableModel* JsonParser::load(QFile& file) const {
    file.open(QIODevice::ReadOnly);
    QByteArray loading = file.readAll();
    QJsonDocument JDoc = QJsonDocument::fromJson(loading);
    QJsonObject JObj = JDoc.object();
    if(JObj.isEmpty()) throw true;
    vector<QVariant> columnsHeaders;
    vector<QVariant> rowsHeaders;
    vector<vector<double>> values;

    QJsonValue JV_columns =  JObj[QString("Columns")];
    if(JV_columns.isNull()) throw true;
    QJsonArray JA_columns = JV_columns.toArray();
    int col_Count=0;
    for(auto it = JA_columns.begin(); it!=JA_columns.end(); ++it){
        col_Count++;
        columnsHeaders.push_back(((*it).toVariant()));
    }

    QJsonValue JV_rows = JObj[QString("Rows")];
    if(JV_rows.isNull()) throw true;
    QJsonObject rowsObj=JV_rows.toObject();
    QMap<QString,QVariant> rows_map = rowsObj.toVariantMap();
    int row_Count=0;
    int checkcol;
    for(auto it = rows_map.begin(); it!=rows_map.end(); ++it){
        rowsHeaders.push_back((it.key()));
        QList<QVariant> row_Array = (it.value()).toList();
        values.push_back(*(new vector<double>));
        checkcol=0;
        for(auto vit = row_Array.begin(); vit!= row_Array.end(); ++vit){

            QString numCheck = vit->toString();
            string negCheck = (numCheck.replace("-","")).toStdString();
            string decCheck = (numCheck.replace(".","")).toStdString();
            if(!DataTableModel::is_number(negCheck) && !DataTableModel::is_number(decCheck)) throw true;

            values[row_Count].push_back(vit->toDouble());
            checkcol++;
        }
        if(checkcol!=col_Count) throw true;
        row_Count++;
    }

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
    file.close();
}

