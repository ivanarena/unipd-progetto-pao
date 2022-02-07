#ifndef PARSER_H
#define PARSER_H

#include "model.h"
#include "controller.h"

#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>

class Parser{
private:

public:
    virtual DataTableModel* load(const QString&) const = 0;
    virtual void save(DataTableModel*, QFile&) const = 0;
    virtual ~Parser() = default;
};

#endif
