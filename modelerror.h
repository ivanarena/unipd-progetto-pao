#ifndef MODELERROR_H
#define MODELERROR_H
#include <QMessageBox>
#include "error.h"
using std::string;

enum m_type {wrong_format, overflow, underflow};

class modelError: public Error
{
private:
    m_type type;
public:
    explicit modelError(m_type);
    void show() const;
    m_type getType() const;
};

#endif // MODELERROR_H
