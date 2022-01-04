#ifndef PARSER_H
#define PARSER_H

#include "model.h"

#include <utility>

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

using std::vector;
using std::string;
using std::pair;

pair<vector<string>,vector<vector<int>>> loadjson(string &filename); //DOING
void savejson(pair<vector<string>,vector<vector<int>>>); //DOING

void loadxml(); //TODO
void savexml(); //TODO

#endif
