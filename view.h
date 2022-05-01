#ifndef VIEW_H
#define VIEW_H

#include <QTableView>
#include <QMenuBar>
#include <QGridLayout>
#include <QtCharts/QChart>
#include <QChart>
#include <QtCharts/QChartView>
#include <QToolBar>
#include <QMenu>
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
    QLabel *welcome;

    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *aboutMenu;
    QMenu *samples;

    QAction *newTab;
    QAction *openModel;
    QAction *saveModeltoJson;
    QAction* saveModeltoXml;
    QAction *renameHeaders;
    QAction *renameTab;
    QAction *insertRow;
    QAction *removeRow;
    QAction *insertColumn;
    QAction *removeColumn;
    QComboBox *chartSelector;
    QAction *exportChart;
    QAction *exitApp;

    QAction *coronaSample;
    QAction *cryptoSample;
    QAction *expensesSample;


    QAction *help;
    QAction *about;

    Controller controller;

    void insertRowCol(DataTableModel*);

    bool firstStart;
    QString currentDirectory = "/home";

public:
    View(QWidget *parent = nullptr);
    ~View();
    QChart *createLineChart(DataTableModel *model);
    QChart *createPieChart(DataTableModel *model);

    void setToolBar();
    void setMenus();
    void setWelcome();
    void checkWelcome();

    void createTableView();
    QTableView * createTableView(DataTableModel *model);

public slots:
    Scene *createNewTab(QString, DataTableModel *model = new DataTableModel());
    void closeTab(const int& index);

    void changeCurrentChart(int);
    void setChartSelectorIndex(int);
    void renameTabDoubleClick(int);
    void renameTabFromButton();

    // QActions methods
    void newTabDialog();
    void importFile();
    void saveAsJson();
    void saveAsXml();
    void saveChartToPng();
    void renameHeadersDialog();
    void insertRowTriggered();
    void removeRowTriggered();
    void insertColumnTriggered();
    void removeColumnTriggered();

    void helpDialog();
    void aboutDialog();
    void openCoronaSample();
    void openCryptoSample();
    void openExpensesSample();
};

#endif // VIEW_H
