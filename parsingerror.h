#ifndef PARSINGERROR_H
#define PARSINGERROR_H

#include <QMessageBox>
#include <QDialog>
#include "error.h"

enum p_type {};

class parsingError: public Error
{
public:
    parsingError() = default;
    void show() const;
};

#endif // PARSINGERROR_H
