#include "parser.h"
#include "controller.h"

pair<vector<string>,vector<vector<int>>> loadjson(const string &filename){

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
    //loadfile.close();
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


void savejson(const pair<vector<string>,vector<vector<int>>> &data, const string &filename){

    QJsonArray big; //Array di array
    for(vector<vector<int>>::const_iterator bigit = data.second.cbegin(); bigit!=data.second.cend(); ++bigit ){ //ciclo il vettore di vettori
        QJsonArray small;
        for(vector<int>::const_iterator it = (*bigit).cbegin(); it!= (*bigit).cend(); ++it){ //ciclo i vettori di interi
            small.push_back(*it);
        }
        big.push_back(small);
    }
    QJsonObject jsonobj;
    for(vector<string>::const_iterator it = data.first.cbegin(); it!= data.first.cend(); ++it){
        jsonobj.insert(QString::fromStdString(*it),big.first());
        big.pop_front();
    }

    QJsonDocument jsondoc(jsonobj);
    QFile savedata(QString::fromStdString(filename));
    if(savedata.exists()){
        //TODO: Would u really like to overwrite your file?
    }
    savedata.open(QIODevice::WriteOnly);
    savedata.write(jsondoc.toJson());
    //savedata.close();
}
