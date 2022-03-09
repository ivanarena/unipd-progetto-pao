#include "parsingerror.h"


void parsingError::show() const{
        QMessageBox error;
        error.setText("Input is not in the valid form");
        error.detailedText();
        error.exec();
}
