#include "view.h"
#include "model.h"
#include "toolbar.h"
#include "parser.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QLineSeries>
#include <QGridLayout>
#include <QApplication>
#include <QStyle>
#include <QVXYModelMapper>
#include <QHeaderView>
#include <QTabWidget>
#include <QToolButton>
#include <QToolBar>
#include <QMenuBar>
#include <QList>
#include <QVPieModelMapper>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QMenu>
#include <QComboBox>
#include <QKeySequence>

// TODO: FARE UNA CLASSE PER OGNI CHART ED IMPLEMENTARE QUESTO METODO COME UNICO createChart POLIMORFO
QChart * View::createLineChart(DataTableModel *model)
{
    QChart *lineChart = new QChart();
    //lineChart->legend()->hide(); LEGENDA
    lineChart->setTitle("Title");
    lineChart->setAnimationOptions(QChart::AllAnimations);

    // mapper table->chart
    for (int i = 1; i < model->columnCount(); i++) {
        QLineSeries *series = new QLineSeries;
        QVXYModelMapper *mapper = new QVXYModelMapper(this);
        series->setName(QString("%1").arg(i));
        mapper->setXColumn(0);
        mapper->setYColumn(i);
        mapper->setSeries(series);
        mapper->setModel(model);
        lineChart->addSeries(series);
    }

    lineChart->createDefaultAxes();

    return lineChart;
}

QChart * View::createPieChart(DataTableModel *model)
{
    QChart *pieChart = new QChart();
    QVPieModelMapper *pieMapper = new QVPieModelMapper();
    pieChart->setTitle("Pie chart");
    pieChart->setAnimationOptions(QChart::AllAnimations);
    QPieSeries *series = new QPieSeries(pieChart);

    pieMapper->setSeries(series);
    pieMapper->setModel(model); //TODO: capire come implementare il piechart con questo set di dati
    pieMapper->setLabelsColumn(0); // a quale colonna associare  label
    pieMapper->setValuesColumn(1); // a quale colonna associare valore
    pieMapper->setFirstRow(0); //da che riga del model inizio
    pieMapper->setRowCount(model->rowCount()); //una riga -> una slice

    pieChart->addSeries(series);
    series->setPieSize(5);
    series->setHoleSize(0.5);


    return pieChart;
}

// TODO: SPOSTARE IN UN ALTRO FILE PER USARLO CON CONTROLLER
QToolBar * View::createToolBar()
{
    toolBar->setIconSize(QSize(36, 36));
    QAction *newTab = new QAction(QIcon(":/res/new-file.png"), "New", this);
    QList<QKeySequence> newTabShortcuts;
    newTabShortcuts << QKeySequence::New << QKeySequence::AddTab;
    newTab->setShortcuts(newTabShortcuts);

    QAction *openModel = new QAction(QIcon(":/res/open-file.png"), "Open", this);
    openModel->setShortcuts(QKeySequence::Open);

    QAction *saveModel = new QAction(QIcon(":/res/save-file.png"), "Save", this);
    saveModel->setShortcuts(QKeySequence::SaveAs);

    QAction *addRow = new QAction(QIcon(":/res/insert-row.png"), "+row", this);
    QAction *removeRow = new QAction(QIcon(":/res/remove-row.png"), "-row", this);
    QAction *addColumn = new QAction(QIcon(":/res/insert-column.png"), "+col", this);
    QAction *removeColumn = new QAction(QIcon(":/res/remove-column.png"), "-col", this);

    // DA SPOSTARE NEL CONTROLLER PROBABILMENTE
    connect(newTab, SIGNAL(triggered()), this, SLOT(createNewTab()));

    //toolBar->setOrientation(Qt::Vertical);
    toolBar->addAction(newTab);
    toolBar->addAction(openModel);
    toolBar->addAction(saveModel);
    toolBar->addAction(addRow);
    toolBar->addAction(removeRow);
    toolBar->addAction(addColumn);
    toolBar->addAction(removeColumn);

    QComboBox *chartSelectionBox = new QComboBox;
    chartSelectionBox->addItem("Line Chart");
    chartSelectionBox->addItem("Pie Chart");

    toolBar->addWidget(chartSelectionBox);

    return toolBar;
}

QTableView * View::createTableView(DataTableModel *model)
{
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    return tableView;
}

QWidget * View::createNewTab(DataTableModel *model)
{
    QWidget *newTab = new QWidget;

    QGridLayout *sceneLayout = new QGridLayout(newTab);

    // SOLUZIONE TEMPORANEA (poi si dovrà implementare quella che scorre e sceglie il grafico voluto)
    QChartView *chartView = new QChartView(createLineChart(model));
    chartView->setMinimumSize(640, 480);
    chartView->setRenderHint(QPainter::Antialiasing);


    sceneLayout->addWidget(createTableView(model), 1, 0);
    sceneLayout->addWidget(chartView, 1, 1);
    sceneLayout->setColumnStretch(0, 2);
    sceneLayout->setColumnStretch(1, 3);

    newTab->setLayout(sceneLayout);
    tabView->addTab(newTab, "test");
    tabView->setCurrentIndex(tabView->currentIndex() + 1);

    return newTab;
}

void View::closeTab(const int& index)
{
    if (index == -1) {
        return;
    }

    QWidget* tabItem = tabView->widget(index);
    // Removes the tab at position index from this stack of widgets.
    // The page widget itself is not deleted.
    tabView->removeTab(index);

    delete(tabItem);
    tabItem = nullptr;
}

View::View(QWidget *parent)
    : QWidget(parent), tabView(new QTabWidget), mainLayout(new QGridLayout), toolBar(new QToolBar)
{
    connect(tabView, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    tabView->setTabsClosable(true);

    //DataTableModel *model = new DataTableModel;

    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI

    // TOGLIERE LA DEFAULT TAB UNA VOLTA CHE IL PROGETTO È FINITO PERCHÈ È STUPIDO PARTIRE DA UN SAMPLE
    QWidget *defaultTab = createNewTab(new DataTableModel);
    tabView->addTab(defaultTab, "Model");

    mainLayout->addWidget(tabView, 1, 0);
    mainLayout->addWidget(createToolBar(), 0, 0);
    setLayout(mainLayout);

}


View::~View()
{
}

