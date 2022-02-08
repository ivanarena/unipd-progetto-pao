#ifndef VIEW_H
#define VIEW_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QTableView>
#include <QMenuBar>
#include <QGridLayout>
#include <QToolBar>
#include "model.h"
#include "controller.h"
#include "parser.h"
#include "jsonparser.h"

using namespace QtCharts;
using namespace std;

class View : public QWidget
{
    Q_OBJECT

private:
    QTabWidget *tabView;
    vector<QTableView *> tables;
    QGridLayout *mainLayout;
    QToolBar *toolBar;
    vector<DataTableModel *> tabModels;
    Controller controller;

public:
    View(QWidget *parent = nullptr);
    ~View();
    QChart *createLineChart(DataTableModel *model);
    QChart *createPieChart(DataTableModel *model);
    QToolBar *createToolBar();
    void createTableView();
    QTableView * createTableView(DataTableModel *model);

public slots:
    void newTabDialog();
    QWidget * createNewTab(DataTableModel *model = new DataTableModel(0, true));
    void closeTab(const int& index);
    void importFile();
    void saveFile();
};

#endif // VIEW_H
