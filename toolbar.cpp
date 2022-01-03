#include "toolbar.h"
#include <QToolBar>

ToolBar::ToolBar()
{
    QToolBar *toolBar = new QToolBar;
    toolBar->setOrientation(Qt::Vertical);
    toolBar->addAction("New");
    toolBar->addAction("Open");
    toolBar->addAction("Save");
    toolBar->addAction("+Tab");
    toolBar->addAction("-Tab");
    toolBar->addAction("+row");
    toolBar->addAction("-row");
    toolBar->addAction("+col");
    toolBar->addAction("-col");
    toolBar->addAction("Line");
}
