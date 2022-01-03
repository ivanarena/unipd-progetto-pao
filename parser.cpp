/*#include "parser.h"

DataTableModel* loadjson(QString &filename){

    QFile loadfile(filename);
    loadfile.open(QIODevice::ReadOnly);
    QByteArray saveData = loadfile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    DataTableModel * model = new DataTableModel();

    for(int i=0; i<model->rowCount();i++){
        for(int j=0; j<model->columnCount(); j++){
            model->setData(i,loadDoc[i]);
        }
    }
    return model;
}*/
