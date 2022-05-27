#ifndef PARSINGERROR_H
#define PARSINGERROR_H

#include <QMessageBox>
#include <QDialog>
#include "error.h"


class parsingError: public Error
{
public:
    parsingError(const QString& message = "");
    void show() override;
};

#endif // PARSINGERROR_H
