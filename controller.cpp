#include "controller.h"
#include "model.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::insertRowReceived(DataTableModel *model)
{
    model->insertRow();
}

void Controller::removeRowReceived(DataTableModel *model)
{
    model->removeRow();
}

void Controller::insertColumnReceived(DataTableModel *model)
{
    model->insertColumn();
}

void Controller::removeColumnReceived(DataTableModel *model)
{
    model->removeColumn();
}
