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
    if (model->rowCount() <= 1) throw QString("You need at least one row.");
    else model->removeRow();
}

void Controller::insertColumnReceived(DataTableModel *model, const QString& label, double d_value)
{
    model->insertColumn(label,d_value);
}

void Controller::removeColumnReceived(DataTableModel *model)
{
    if (model->columnCount() <= 1) throw QString("You need at least one column.");
    else model->removeColumn();
}


