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

pair<vector<string>,vector<vector<int>>> loadjson(const string &filename); //ALMOST DONE
void savejson(const pair<vector<string>,vector<vector<int>>> &data, const string &filename); //DOING

void loadxml(); //TODO
void savexml(); //TODO

#endif
