#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "parser.h"


class JsonParser: public Parser{
public:
    DataTableModel* load(const QString&) const override;
    //void save(const DataTableModel&) const override;
};

#endif // JSONPARSER_H
