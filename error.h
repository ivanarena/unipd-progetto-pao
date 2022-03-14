#ifndef ERROR_H
#define ERROR_H

enum type {parsingerror, modelerror};
enum subtype { format , data };

class Error
{
public:
    Error() = default;
    virtual void show() const = 0;
    virtual ~Error() = default;
};

#endif // ERROR_H
