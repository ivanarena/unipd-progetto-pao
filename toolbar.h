#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QAction>
#include <QToolBar>
#include <QKeySequence>
#include <QList>
#include "view.h"

class ToolBar
{
    Q_OBJECT

private:
    QAction *newTab;
    QAction *openModel;
    QAction *saveModel;
    QAction *addRow;
    QAction *removeRow;
    QAction *addColumn;
    QAction *removeColumn;

public:
    ToolBar();
    void setUpToolBar();
};

#endif // TOOLBAR_H
