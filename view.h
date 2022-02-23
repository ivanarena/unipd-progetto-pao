#ifndef VIEW_H
#define VIEW_H

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QTableView>
#include <QMenuBar>
#include <QGridLayout>
#include <QtCharts/QChart>
#include <QChart>
#include <QtCharts/QChartView>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include "model.h"
#include "controller.h"
#include "parser.h"
#include "jsonparser.h"
#include "scene.h"


using namespace QtCharts;
using namespace std;

class View : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *mainLayout;
    QTabWidget *tabView;

    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *newTab;
    QAction *openModel;
    QAction *saveModel;
    QAction *renameHeaders;
    QAction *insertRow;
    QAction *removeRow;
    QAction *insertColumn;
    QAction *removeColumn;
    QComboBox *chartSelector;
    QAction *exitApp;

    Controller controller;
public:
    View(QWidget *parent = nullptr);
    ~View();
    QChart *createLineChart(DataTableModel *model);
    QChart *createPieChart(DataTableModel *model);

    void setToolBar();
    void setMenus();

    void createTableView();
    QTableView * createTableView(DataTableModel *model);

public slots:
    Scene *createNewTab(DataTableModel *model = new DataTableModel, QChart *chart = new QtCharts::QChart);
    void closeTab(const int& index);

    void changeCurrentChart(int);

    // QActions methods
    void newTabDialog();
    //void importFile();
    //void saveFile();
    void renameHeadersDialog();
    void insertRowTriggered();
    void removeRowTriggered();
    void insertColumnTriggered();
    void removeColumnTriggered();
};

#endif // VIEW_H
