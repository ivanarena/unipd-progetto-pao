#ifndef PARSER_H
#define PARSER_H

#include "controller.h"


#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

class DataTableModel;

class Parser{
private:

public:
    virtual DataTableModel* load(QFile&) const = 0;
    virtual void save(DataTableModel*, QFile&) const = 0;
    virtual ~Parser() = default;
};

#endif
