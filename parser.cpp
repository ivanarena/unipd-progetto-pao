#include "parser.h"
#include "controller.h"

pair<vector<string>,vector<vector<int>>> loadjson(string &filename){

    pair<vector<string>,vector<vector<int>>> data;

    QFile loadfile(QString::fromStdString(filename));
    if (!loadfile.open(QIODevice::ReadOnly)){
       // controller::Error(1); TODO
    }

    QByteArray filearray = loadfile.readAll();

    QJsonDocument jsondoc = QJsonDocument::fromJson(filearray);
    QJsonObject jsonobj = jsondoc.object();

    //Headers:

    QStringList keylist = jsonobj.keys();
    QVector<QString> qheaders = keylist.toVector();
    QString iter;
    foreach(iter,qheaders)
        data.first.push_back(iter.toStdString());

    //Values:

    for(vector<string>::const_iterator it = data.first.begin(); it!= data.first.end(); ++it){
        if(jsonobj[QString::fromStdString(*it)].isArray()){ //trovo array associato a key
            QJsonArray qArray = jsonobj[QString::fromStdString(*it)].toArray();
            vector<int> values;
            for(QJsonArray::const_iterator ait = qArray.constBegin(); ait!=qArray.constEnd(); ++ait){
                values.push_back((*ait).toInt());
            }
            data.second.push_back(values);
        }
    }

    return data;
}



/* TODO:
 *  controllare che i valori siano numerici
 *  controllare che gli array abbiano stessa dimensione (?)
 *
 *
 *
 *
 *
 *
 *
 * */
