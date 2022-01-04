#include "toolbar.h"
#include <QAction>
#include <QList>
#include <QList>

ToolBar::ToolBar()
{
    newTab = new QAction("New", this);
    QList<QKeySequence> newTabShortcuts;
    newTabShortcuts << QKeySequence::New << QKeySequence::AddTab;
    newTab->setShortcuts(newTabShortcuts);

    openModel = new QAction("Open", this);
    openModel->setShortcuts(QKeySequence::Open);

    saveModel = new QAction("Save", this);
    saveModel->setShortcuts(QKeySequence::SaveAs);

    addRow = new QAction("+row", this);
    removeRow = new QAction("-row", this);
    addColumn = new QAction("+col", this);
    removeColumn = new QAction("-col", this);

    // DA SPOSTARE NEL CONTROLLER PROBABILMENTE
    connect(newTab, SIGNAL(triggered()), this, SLOT(createNewTab()));
}

void setUpToolBar()
{
    ViewtoolBar->setOrientation(Qt::Vertical);
    toolBar->addAction(newTab);
    toolBar->addAction(openModel);
    toolBar->addAction(saveModel);
    toolBar->addAction(addRow);
    toolBar->addAction(removeRow);
    toolBar->addAction(addColumn);
    toolBar->addAction(removeColumn);
    toolBar->addAction("chart_sel");
}
