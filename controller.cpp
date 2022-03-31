#include "controller.h"
#include "model.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

void Controller::insertRowReceived(DataTableModel *model, const QString& label, double d_value)
{
    model->insertRow(label,d_value);
}

void Controller::removeRowReceived(DataTableModel *model)
{
    model->removeRow();
}

void Controller::insertColumnReceived(DataTableModel *model,const QString& label, double d_value)
{
    model->insertColumn(label,d_value);
}

void Controller::removeColumnReceived(DataTableModel *model)
{
    model->removeColumn();
}
