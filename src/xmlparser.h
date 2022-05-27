#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "parser.h"
#include "controller.h"

#include <QXmlSimpleReader>
#include <QXmlInputSource>
#include <QDomDocument>

class XmlParser : public Parser
{
public:
    DataTableModel* load(QFile&) const override;
    void save(DataTableModel*, QFile&) const override;
};

#endif // XMLPARSER_H
