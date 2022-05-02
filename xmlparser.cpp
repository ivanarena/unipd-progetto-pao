#include "xmlparser.h"
#include <iostream>
using namespace std;


DataTableModel* XmlParser::load(QFile& file) const{
    file.open(QIODevice::ReadOnly);
    QDomDocument doc("xml");
    doc.setContent(&file);
    file.close();
    vector<vector<double>> values;
    vector<QVariant> columnsHeader;
    vector<QVariant> rowsHeaders;
    int rowCount=0;
    int columnCount=0;

    QDomElement docElem = doc.documentElement();
    QDomNode child = docElem.firstChild();
    if(child.isNull()) throw true;
    QDomElement xml_columnsHeaders = child.toElement();
    if(xml_columnsHeaders.tagName()!="Columns") throw true;
    QString s_columnsHeaders = xml_columnsHeaders.text();
    QStringList l_columnHeaders = s_columnsHeaders.split(',');
    if(l_columnHeaders.count()==1 && l_columnHeaders.front()=="") l_columnHeaders.clear();
    for(auto it = l_columnHeaders.begin(); it!= l_columnHeaders.end(); ++it) {
        if((*it)=="") throw true;
        columnsHeader.push_back(*it);
        columnCount++;
    }
    child=child.nextSibling();
    QDomElement xml_rowsHeaders = child.toElement();
    if(xml_rowsHeaders.tagName()!="Rows") throw true;
    QDomNode subchild = xml_rowsHeaders.firstChild();
    if(columnCount>0 && subchild.isNull()) throw true;
    for(int i=0; !subchild.isNull(); ++i , subchild=subchild.nextSibling(), ++rowCount){
        QDomElement xml_rows = subchild.toElement();
        rowsHeaders.push_back(xml_rows.tagName());
        QString s_rowsValues = xml_rows.text();
        QStringList l_rowValues = s_rowsValues.split(',');
        if(l_rowValues.count()==1 && l_rowValues.front()=="") l_rowValues.clear();
        values.push_back(*new vector<double>);
        int colCheck=0;
        for(auto it = l_rowValues.begin(); it!=l_rowValues.end(); ++it, ++colCheck) {

            QString numCheck = *it;
            numCheck.replace(" ","");
            int nDots =0, nMin=0;
            for(auto c = numCheck.begin(); c!= numCheck.end(); ++c) {if(*c == ".") nDots++; else if(*c=="-") nMin++; }
            if(nDots>1 || nMin>1) throw true;
            string negCheck = (numCheck.replace("-","")).toStdString();
            string decCheck = (numCheck.replace(".","")).toStdString();
            if(!DataTableModel::is_number(negCheck) && !DataTableModel::is_number(decCheck)) throw true;

            if(*it=="") throw true;
             values[i].push_back((*it).toDouble());
        }
        if(colCheck!=columnCount)
            throw true;
    }

    return new DataTableModel(nullptr, rowCount, columnCount, values, columnsHeader, rowsHeaders);
}

void XmlParser::save(DataTableModel* model, QFile& file) const{

    QDomDocument doc("xml");
    QDomElement root = doc.createElement("Doc");
    doc.appendChild(root);

    QDomElement columnTag = doc.createElement("Columns");
    root.appendChild(columnTag);

    vector<QVariant> col_Heads = model->getColumnsHeaders();
    QString col_JoinHeads = "";
    for(auto it = col_Heads.begin(); it!= col_Heads.end(); ++it){
        col_JoinHeads = col_JoinHeads +  it->toString() + ',';
    }
    col_JoinHeads.remove(col_JoinHeads.size()-1,1);

    QDomText columnHeaders = doc.createTextNode(col_JoinHeads);
    columnTag.appendChild(columnHeaders);

    QDomElement rowTag = doc.createElement("Rows");
    root.appendChild(rowTag);

    vector<QVariant> row_Heads = model->getRowsHeaders();

    vector<vector<double>> values = model->getData();
    int i=0;
    for(auto it = row_Heads.begin(); it!= row_Heads.end(); ++it, ++i){
        QDomElement i_header = doc.createElement(it->toString().replace(" ","_"));
        rowTag.appendChild(i_header);
        vector<double> i_value = values[i];
        QString joinedValues = "";
        for(auto vit = i_value.begin(); vit!= i_value.end(); ++vit) joinedValues = joinedValues + QString::number(*vit) + ',';
        joinedValues.remove(joinedValues.size()-1,1);
        QDomText rowValues = doc.createTextNode(joinedValues);
        i_header.appendChild(rowValues);
    }

    QString xml = doc.toString();
    QByteArray saving = xml.toUtf8();
    file.write(saving);

}
