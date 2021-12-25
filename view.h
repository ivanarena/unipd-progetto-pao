#ifndef VIEW_H
#define VIEW_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QTableView>
#include <QMenuBar>
#include <QToolBar>
#include "model.h"

using namespace QtCharts;

class View : public QWidget
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();
    QChart *createLineChart(DataTableModel *model);
    QToolBar *createToolBar();
    void createTableView();
    QTableView * createTableView(DataTableModel *model);
};
#endif // VIEW_H
