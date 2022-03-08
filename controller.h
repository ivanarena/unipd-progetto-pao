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
    void insertRowReceived(DataTableModel *model);
    void removeRowReceived(DataTableModel *model);
    void insertColumnReceived(DataTableModel *model);
    void removeColumnReceived(DataTableModel *model);
};

#endif // CONTROLLER_H
