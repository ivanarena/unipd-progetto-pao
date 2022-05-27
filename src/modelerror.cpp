#include "modelerror.h"

modelError::modelError(m_type t): type(t) {}

m_type modelError::getType() const{ return type;}

void modelError::show() const{
        QMessageBox error;
        QString out;
        switch(getType()){
            case wrong_format:
                out="Only numbers accepted";
                break;
            case overflow:
                out="Overflow";
                break;
            case underflow:
                out="Underflow";
                break;
            default:
                out="Error";

        }
        error.setText(out);
        error.exec();
}
