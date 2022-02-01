#include "controller.h"
#include "model.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::addRowPressed(DataTableModel *modelPtr)
{
    modelPtr->addRow();
}
