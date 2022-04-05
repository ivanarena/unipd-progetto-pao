#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

signals:

public slots:
    void insertRowReceived(DataTableModel *model, const QString&, double);
    void removeRowReceived(DataTableModel *model);
    void insertColumnReceived(DataTableModel *model, const QString&, double);
    void removeColumnReceived(DataTableModel *model);
    void insertRowAndColumnReceived(DataTableModel *model, const QString&, const QString&, double);
};

#endif // CONTROLLER_H
