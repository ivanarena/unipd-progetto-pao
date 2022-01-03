#ifndef PARSER_H
#define PARSER_H

#include "model.h"

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

DataTableModel* loadjson(QString filename);
void savejson(const DataTableModel &model);

void loadxml(); //TODO
void savexml(); //TODO

#endif
