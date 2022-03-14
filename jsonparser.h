#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "parser.h"


class JsonParser: public Parser{
public:
    DataTableModel* load(QFile&) const override;
    void save(DataTableModel*, QFile&) const override;
};

#endif // JSONPARSER_H
