#include "parsingerror.h"

parsingError::parsingError(const QString& message){
    setText("Parser found an error");
    setDetailedText(message);
}

void parsingError::show() {
    exec();
}
