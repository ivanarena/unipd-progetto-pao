#include "xmlparser.h"
#include <iostream>
using namespace std;
DataTableModel* XmlParser::load(QFile& file) const{
    //cout<<path.toStdString();
    file.open(QIODevice::ReadOnly);
    QDomDocument doc("xml");
    //if(!doc.setContent(&file)) cout<<"";
    file.close();
    vector<vector<double>> values;
    vector<QVariant> columnsHeader;
    vector<QVariant> rowsHeaders;
    int rowCount=0;
    int columnCount=0;

    QDomElement docElem = doc.documentElement();
    QDomNode child = docElem.firstChild();
    QDomElement xml_columnsHeaders = child.toElement();
    //cout<<xml_columnsHeaders.tagName().toStdString();
    //if(xml_columnsHeaders.tagName()!="Columns") throw new ParsingError();
    QString s_columnsHeaders = xml_columnsHeaders.text();
    QStringList l_columnHeaders = s_columnsHeaders.split(',');
    for(auto it = l_columnHeaders.begin(); it!= l_columnHeaders.end(); ++it , ++columnCount) columnsHeader.push_back(*it);
    child=child.nextSibling();
    QDomElement xml_rowsHeaders = child.toElement();
    //if(xml_rowsHeaders.tagName()!="Rows") throw new ParsingError();
    QDomNode subchild = xml_rowsHeaders.firstChild();
    for(int i=0; !subchild.isNull(); ++i , subchild=subchild.nextSibling(), ++rowCount){
        QDomElement xml_rows = subchild.toElement();
        rowsHeaders.push_back(xml_rows.tagName());
        QString s_rowsValues = xml_rows.text();
        QStringList l_rowValues = s_rowsValues.split(',');
        values.push_back(*new vector<double>);
        for(auto it = l_rowValues.begin(); it!=l_rowValues.end(); ++it) if(*it!="") values[i].push_back((*it).toDouble());
    }
    //if(!n.nextSibling().isNull()) throw new ParsingError();

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

    QDomText columnHeaders = doc.createTextNode(col_JoinHeads);
    columnTag.appendChild(columnHeaders);

    QDomElement rowTag = doc.createElement("Rows");
    root.appendChild(rowTag);

    vector<QVariant> row_Heads = model->getRowsHeaders();
    vector<vector<double>> values = model->getData();
    int i=0;
    for(auto it = row_Heads.begin(); it!= row_Heads.end(); ++it, ++i){
        QDomElement i_header = doc.createElement(it->toString());
        rowTag.appendChild(i_header);
        vector<double> i_value = values[i];
        QString joinedValues = "";
        for(auto vit = i_value.begin(); vit!= i_value.end(); ++vit) joinedValues = joinedValues + QString::number(*vit) + ',';
        QDomText rowValues = doc.createTextNode(joinedValues);
        i_header.appendChild(rowValues);
    }

    QString xml = doc.toString();
    QByteArray saving = xml.toUtf8();
    file.write(saving);

}
