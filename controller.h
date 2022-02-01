#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    static void addRowPressed(DataTableModel *modelPtr);
signals:

public slots:
};

#endif // CONTROLLER_H
