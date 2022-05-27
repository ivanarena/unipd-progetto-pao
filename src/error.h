#ifndef ERROR_H
#define ERROR_H

#include <QMessageBox>

class Error: public QMessageBox
{
public:
    Error() = default;
    virtual void show()=0;
    virtual ~Error() = default;
};

#endif // ERROR_H
