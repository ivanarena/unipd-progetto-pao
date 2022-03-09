#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "parser.h"
#include "controller.h"

class XmlParser : public Parser
{
public:
    DataTableModel* load(const QString&) const override;
    void save(DataTableModel*, QFile&) const override;
};

#endif // XMLPARSER_H
