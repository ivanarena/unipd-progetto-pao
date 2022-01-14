#include "parser.h"
#include "controller.h"

pair<vector<string>,vector<vector<int>>> loadJson(const string &fileName)
{

    pair<vector<string>,vector<vector<int>>> data;

    QFile loadFile(QString::fromStdString(fileName));
    if (!loadFile.open(QIODevice::ReadOnly))
    {
       // controller::Error(1); TODO
    }

    QByteArray fileArray = loadFile.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileArray);
    QJsonObject jsonObj = jsonDoc.object();

    //Headers:

    QStringList keylist = jsonObj.keys();
    QVector<QString> qHeaders = keylist.toVector();
    QString iter;
    foreach(iter, qHeaders)
        data.first.push_back(iter.toStdString());

    //Values:

    for(vector<string>::const_iterator it = data.first.begin(); it!= data.first.end(); ++it)
    {
        if(jsonObj[QString::fromStdString(*it)].isArray()) //trovo array associato a key
        {
            QJsonArray qArray = jsonObj[QString::fromStdString(*it)].toArray();
            vector<int> values;
            for(QJsonArray::const_iterator ait = qArray.constBegin(); ait!=qArray.constEnd(); ++ait)
            {
                values.push_back((*ait).toInt());
            }
            data.second.push_back(values);
        }
    }
    //loadFile.close();
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


void saveJson(const pair<vector<string>,vector<vector<int>>> &data, const string &fileName){

    QJsonArray big; //Array di array
    for(vector<vector<int>>::const_iterator bigit = data.second.cbegin(); bigit!=data.second.cend(); ++bigit ) //ciclo il vettore di vettori
    {
        QJsonArray small;
        for(vector<int>::const_iterator it = (*bigit).cbegin(); it!= (*bigit).cend(); ++it) //ciclo i vettori di interi
        {
            small.push_back(*it);
        }
        big.push_back(small);
    }
    QJsonObject jsonObj;
    for(vector<string>::const_iterator it = data.first.cbegin(); it!= data.first.cend(); ++it)
    {
        jsonObj.insert(QString::fromStdString(*it),big.first());
        big.pop_front();
    }

    QJsonDocument jsonDoc(jsonObj);
    QFile saveData(QString::fromStdString(fileName));
    if(saveData.exists())
    {
        //TODO: Would u really like to overwrite your file?
    }
    saveData.open(QIODevice::WriteOnly);
    saveData.write(jsonDoc.toJson());
    //saveData.close();
}
