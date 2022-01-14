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

pair<vector<string>,vector<vector<int>>> loadJson(const string &fileName); //ALMOST DONE
void saveJson(const pair<vector<string>,vector<vector<int>>> &data, const string &fileName); //DOING

void loadXml(); //TODO
void saveXml(); //TODO

#endif
