#include "view.h"
#include "model.h"
#include "parser.h"
#include "jsonparser.h"
#include "controller.h"
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
#include <QAbstractButton>
#include <QPushButton>
#include <QVPieModelMapper>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
#include <QMenu>
#include <QComboBox>
#include <QKeySequence>
#include <iostream>
#include <QFileDialog>
#include <QInputDialog>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include "scene.h"
#include "chart.h"
#include "linechart.h"
#include "barchart.h"
#include "pie_chart.h"
#include "polarchart.h"
#include "scatterchart.h"
#include "error.h"
#include "xmlparser.h"
using namespace std;


void View::setToolBar()
{
    chartSelector->addItem("Line Chart");
    chartSelector->addItem("Bar Chart");
    chartSelector->addItem("Pie Chart");
    chartSelector->addItem("PolarChart");
    chartSelector->addItem("ScatterChart");

    //toolBar->setOrientation(Qt::Vertical);
    toolBar->addSeparator();
    toolBar->addAction(newTab);
    toolBar->addSeparator();
    toolBar->addAction(openModel);
    toolBar->addAction(saveModeltoJson);
    toolBar->addAction(saveModeltoXml);
    toolBar->addSeparator();
    toolBar->addAction(renameHeaders);
    toolBar->addSeparator();
    toolBar->addAction(insertRow);
    toolBar->addAction(removeRow);
    toolBar->addSeparator();
    toolBar->addAction(insertColumn);
    toolBar->addAction(removeColumn);
    toolBar->addSeparator();
    toolBar->addWidget(chartSelector);
    toolBar->addSeparator();

    toolBar->setIconSize(QSize(36, 36));
}

void View::setMenus()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newTab);
    fileMenu->addSeparator();
    fileMenu->addAction(openModel);
    fileMenu->addAction(saveModeltoJson);
    fileMenu->addAction(saveModeltoXml);
    fileMenu->addSeparator();
    fileMenu->addAction(exitApp);

    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(renameHeaders);
    editMenu->addSeparator();
    editMenu->addAction(insertRow);
    editMenu->addAction(removeRow);
    editMenu->addSeparator();
    editMenu->addAction(insertColumn);
    editMenu->addAction(removeColumn);
    editMenu->addSeparator();
}

//============================== COSTRUTTORE ===========================================

// IMPORTANTISSIMO!!!!! IMPLEMENTARE UN VETTORE CHE SCORRE I MODELLI E GESTISCE I MODELLI DI OGNI TAB
View::View(QWidget *parent)
    : QWidget(parent), mainLayout(new QGridLayout), tabView(new QTabWidget), toolBar(new QToolBar),
      menuBar(new QMenuBar), fileMenu(new QMenu), editMenu(new QMenu),
      newTab(new QAction(QIcon(":/res/new-file.png"), "New", this)),
      openModel(new QAction(QIcon(":/res/open-file.png"), "Open", this)),
      saveModel(new QAction(QIcon(":/res/save-file.png"), "Save", this)),
      saveModeltoJson(new QAction(QIcon(":/res/save-file.png"), "Save as Json", this)),
      saveModeltoXml(new QAction(QIcon(":/res/save-file.png"), "Save as Xml", this)),
      renameHeaders(new QAction(QIcon(":/res/rename-headers.png"), "Rename headers", this)),
      insertRow(new QAction(QIcon(":/res/insert-row.png"), "Insert row", this)),
      removeRow(new QAction(QIcon(":/res/remove-row.png"), "Remove row", this)),
      insertColumn(new QAction(QIcon(":/res/insert-column.png"), "Insert column", this)),
      removeColumn(new QAction(QIcon(":/res/remove-column.png"), "Remove column", this)),
      chartSelector(new QComboBox),
      exitApp(new QAction(QIcon(":/res/exit-app.png"), "Exit", this))
{
    tabView->setTabsClosable(true);

    // QActions shortcuts
    // TODO ADD MORE SHORTCUTS
    QList<QKeySequence> newTabShortcuts;
    newTabShortcuts << QKeySequence::New << QKeySequence::AddTab;
    newTab->setShortcuts(newTabShortcuts);
    openModel->setShortcuts(QKeySequence::Open);
    saveModeltoJson->setShortcut(QKeySequence(tr("Ctrl+Shift+J")));
    saveModeltoXml->setShortcut(QKeySequence(tr("Ctrl+Shift+X")));
    renameHeaders->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    insertRow->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    removeRow->setShortcut(QKeySequence(tr("Ctrl+Shift+R")));
    insertColumn->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_K));
    removeColumn->setShortcut(QKeySequence(tr("Ctrl+Shift+C")));

    QShortcut* save = new QShortcut(QKeySequence(tr("Ctrl+Shift+S")), this);

    connect(tabView, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(newTab, SIGNAL(triggered()), this, SLOT(newTabDialog()));
    connect(openModel, SIGNAL(triggered()), this, SLOT(importFile()));
    connect(saveModel, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(saveModeltoJson, SIGNAL(triggered()), this, SLOT(saveAsJson()));
    connect(saveModeltoXml, SIGNAL(triggered()), this, SLOT(saveAsXml()));
    connect(renameHeaders, SIGNAL(triggered()), this, SLOT(renameHeadersDialog()));
    connect(insertRow, SIGNAL(triggered()), this, SLOT(insertRowTriggered()));
    connect(removeRow, SIGNAL(triggered()), this, SLOT(removeRowTriggered()));
    connect(insertColumn, SIGNAL(triggered()), this, SLOT(insertColumnTriggered()));
    connect(removeColumn, SIGNAL(triggered()), this, SLOT(removeColumnTriggered()));
    connect(chartSelector, SIGNAL(activated(int)), this, SLOT(changeCurrentChart(int)));
    connect(tabView, SIGNAL(tabBarClicked(int)), this, SLOT(setChartSelectorIndex(int)));
    connect(tabView, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(changeTabName(int)));
    connect(save, SIGNAL(activated()), this, SLOT(saveFile()));
    // connect(exitApp, SIGNAL(triggered()), this, SLOT(QApplication::quit())); // non funzia

    setToolBar();
    setMenus();

    // VISUALIZER E SELETTORE GRAFICI (DA FARE)
    // TODO: CREARE UNA QLIST DI PUNTATORI A CHARVIEW PER SCORRERE I GRAFICI

    // TOGLIERE LA DEFAULT TAB UNA VOLTA CHE IL PROGETTO È FINITO PERCHÈ È STUPIDO PARTIRE DA UN SAMPLE


    DataTableModel* model =new DataTableModel(10,10,nullptr);
    createNewTab("Project1",model);

    mainLayout->addWidget(menuBar, 0, 0);
    mainLayout->addWidget(toolBar, 1, 0);
    mainLayout->addWidget(tabView, 2, 0);
    setLayout(mainLayout);
}


//======================== PUBLIC SLOTS =========================================


Scene *View::createNewTab(QString tabName,DataTableModel *model)
{
    Scene *scene = new Scene(model, new Chart(model));
    tabView->addTab(scene, tabName); // possible conflicts with openfile
    tabView->setCurrentIndex(tabView->currentIndex() + 1);
    chartSelector->setCurrentIndex(-1);
    return scene;
}

void View::newTabDialog()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QString tabLabel = QString("Tab name");
    QLineEdit* tabInput = new QLineEdit(&dialog);
    QString rowsLabel = QString("Rows number");
    QLineEdit *rowsInput = new QLineEdit(&dialog);
    QString colsLabel = QString("Columns number");
    QLineEdit *colsInput = new QLineEdit(&dialog);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("Create new table:"));
    form.addRow(new QLabel());
    form.addRow(tabLabel, tabInput);
    form.addRow(new QLabel());
    form.addRow(rowsLabel, rowsInput);
    form.addRow(colsLabel, colsInput);
    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    int rows, cols;
    QString tabName;
    bool safe;

    if (dialog.exec() == QDialog::Accepted) {
        rows = rowsInput->text().toInt(&safe, 10);
        cols = colsInput->text().toInt(&safe, 10);
        tabName = tabInput->text();
        if (rows && cols)
        {
            DataTableModel *model = new DataTableModel(rows, cols,nullptr);
            createNewTab(tabName,model);
            renameHeadersDialog();
        }
        else dialog.reject();
    }
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
    if(tabView->count()<=0) chartSelector->setCurrentIndex(-1);
}

void View::renameHeadersDialog()
{
    if(tabView->count()==0) return;
    QDialog dialog(this);
    QFormLayout form(&dialog);

    vector<QVariant> rowsHeaders = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->getRowsHeaders();
    vector<QVariant> columnsHeaders = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->getColumnsHeaders();

    vector<QLineEdit *> rowsHeadersInputs;
    vector<QLineEdit *> columnsHeadersInputs;

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("Rename table headers:"));
    form.addRow(new QLabel());
    form.addRow(new QLabel("Rows headers:"));

    int i = 0;
    for (auto it = rowsHeaders.begin(); it != rowsHeaders.end(); it++)
    {
        QString label = QString("%1").arg(i);
        QLineEdit *rowInput = new QLineEdit(&dialog);
        rowInput->setPlaceholderText(QString(it->toString()));
        rowsHeadersInputs.push_back(rowInput);
        form.insertRow(i+3, new QLabel(label), rowInput);
        i++;
    }

    form.addRow(new QLabel());
    form.addRow(new QLabel("Columns headers:"));

    int j = 0;
    for (auto it = columnsHeaders.begin(); it != columnsHeaders.end(); it++)
    {
        QString label = QString("%1").arg(j);
        QLineEdit *colInput = new QLineEdit(&dialog);
        colInput->setPlaceholderText(QString(it->toString()));
        columnsHeadersInputs.push_back(colInput);
        form.insertRow(j+i+5, new QLabel(label), colInput);
        j++;
    }

    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // TODO: PREVENT SAME HEADERS NAME IN THE SAME ORIENTATION
    if (dialog.exec() == QDialog::Accepted) {
        for (unsigned int i = 0; i < rowsHeadersInputs.size(); i++)
        {
            QVariant newHeader = rowsHeadersInputs[i]->text();
            if (newHeader != "") static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->setHeaderData(i, Qt::Vertical, newHeader);
        }
        for (unsigned int i = 0; i < columnsHeadersInputs.size(); i++)
        {
            QVariant newHeader = columnsHeadersInputs[i]->text();
            if (newHeader != "") static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->setHeaderData(i, Qt::Horizontal, newHeader);
        }
    }
    else dialog.reject();
}

void View::changeCurrentChart(int index)
{
   if(tabView->count()>=1) static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->setActiveChart(index);
}

void View::setChartSelectorIndex(int tabIndex){
    QChart* current_chart = static_cast<Scene *>(tabView->widget(tabIndex))->getChart();
    int chartIndex=-1;
    if(typeid(*current_chart) == typeid(LineChart)) chartIndex=0;
    else if(typeid(*current_chart) == typeid(BarChart)) chartIndex=1;
    else if(typeid(*current_chart) == typeid(PieChart)) chartIndex=2;
    else if(typeid(*current_chart) == typeid(PolarChart)) chartIndex=3;
    else if(typeid(*current_chart) == typeid(ScatterChart)) chartIndex=4;
    chartSelector->setCurrentIndex(chartIndex);
}

void View::changeTabName(int tabIndex){

    QString newname = QInputDialog::getText(this,tr(""), tr("New Tab Name:"), QLineEdit::Normal);
    if(!newname.isEmpty()){
        tabView->setTabText(tabIndex,newname);
    }
}

void View::insertRowCol(DataTableModel* model){
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QString rowLabel = QString("Row Header");
    QLineEdit *rowInput = new QLineEdit(&dialog);
    QString colLabel = QString("Column Header");
    QLineEdit *colInput = new QLineEdit(&dialog);
    QString Value = QString("Value");
    QLineEdit *valueInput = new QLineEdit(&dialog);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("New Model"));
    form.addRow(new QLabel());
    form.addRow(rowLabel, rowInput);
    form.addRow(new QLabel());
    form.addRow(colLabel,colInput);
    form.addRow(new QLabel());
    form.addRow(Value, valueInput);
    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    double value;
    QString rowHeader;
    QString colHeader;

    if (dialog.exec() == QDialog::Accepted) {
        value = valueInput->text().toDouble();
        rowHeader = rowInput->text();
        colHeader = colInput->text();
        if (!valueInput->text().isEmpty() && !rowHeader.isEmpty() && !colHeader.isEmpty())
        {
            controller.insertColumnReceived(model,colHeader,value);
            controller.insertRowReceived(model,rowHeader,value);
            Chart* chart = dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart());
            chart->insertSeries();
            chart->insertSeriesValue();
        }
        else dialog.reject();
    }
}

void View::insertRowTriggered()
{
    if(tabView->count()==0) return;
    DataTableModel* model = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel();
    if(model->rowCount()==0 && model->columnCount()==0){
        insertRowCol(model);
        return;
    }
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QString rowLabel = QString("Row Header");
    QLineEdit *rowInput = new QLineEdit(&dialog);
    QString defaultValue = QString("Default Value");
    QLineEdit *valueInput = new QLineEdit(&dialog);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("New Row"));
    form.addRow(new QLabel());
    form.addRow(rowLabel, rowInput);
    form.addRow(new QLabel());
    form.addRow(defaultValue, valueInput);
    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    double d_value;
    QString rowHeader;

    if (dialog.exec() == QDialog::Accepted) {
        d_value = valueInput->text().toDouble();
        rowHeader = rowInput->text();
        if (!valueInput->text().isEmpty() && !rowHeader.isEmpty())
        {
            controller.insertRowReceived(model,rowHeader,d_value);
            dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->insertSeries();
        }
        else dialog.reject();
    }
}

void View::removeRowTriggered()
{
    if(tabView->count()==0) return;
    try
    {
        controller.removeRowReceived(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel());
        dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->removeSeries(); // TOFIX: ERRORE QUANDO SI PROVA A RIMUOVERE ULTIMA RIGA RIMASTA
    }
    catch (const QString &errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage);
    }


}

void View::insertColumnTriggered()
{
    if(tabView->count()==0) return;
    DataTableModel* model = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel();
    if(model->rowCount()==0 && model->columnCount()==0){
        insertRowCol(model);
        return;
    }
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QString columnLabel = QString("Column Header");
    QLineEdit *columnInput = new QLineEdit(&dialog);
    QString defaultValue = QString("Default Value");
    QLineEdit *valueInput = new QLineEdit(&dialog);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);

    form.addRow(new QLabel("New Column"));
    form.addRow(new QLabel());
    form.addRow(columnLabel, columnInput);
    form.addRow(new QLabel());
    form.addRow(defaultValue, valueInput);
    form.addRow(new QLabel());
    form.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    double d_value;
    QString rowHeader;

    if (dialog.exec() == QDialog::Accepted) {
        d_value = valueInput->text().toDouble();
        rowHeader = columnInput->text();
        if (!valueInput->text().isEmpty() && !rowHeader.isEmpty())
        {

            controller.insertColumnReceived(model,rowHeader,d_value);
            dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->insertSeriesValue();
        }
        else dialog.reject();
    }
}

void View::removeColumnTriggered()
{
    if(tabView->count()==0) return;
    try
    {
        controller.removeColumnReceived(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel());
        dynamic_cast<Chart *>(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getChart())->removeSeriesValue();
    }
    catch (const QString &errorMessage)
    {
        QMessageBox::critical(this, "Error", errorMessage);
    }
}

void View::importFile(){

    QString import = QFileDialog::getOpenFileName(nullptr, tr("Select a Document"),"/home", tr("Json files (*.json);;XML files (*.xml)"));
    QFile file(import);
    if(import != ""){

        QFileInfo fileInfo(file.fileName());
        QString filename(fileInfo.fileName());

        Parser* parser;

        if(import.endsWith(".xml")){
            parser=new XmlParser();
            filename.replace(".xml","");
        }
        if(import.endsWith(".json")){
            parser=new JsonParser();
            filename.replace(".json","");

        }
        try{
            DataTableModel* model = parser->load(file);
            delete parser;

            createNewTab(filename,model);
            tabView->setCurrentIndex(tabView->currentIndex() + 1);
            chartSelector->setCurrentIndex(-1);
        }
        catch(const QString& message ){
            delete parser;
            QMessageBox::critical(this,"Error found while parsing",message);
        }
    }
}

void View::saveFile(){
    if(tabView->count()==0) return;
    QDialog saveDialog;
    QFormLayout form(&saveDialog);
    QLabel* text = new QLabel("Choose the file format");
    text->setAlignment(Qt::AlignCenter);
    form.addRow(text);
    form.addRow(new QLabel("          "));
    QDialogButtonBox buttons;
    QPushButton* Xml = new QPushButton("Xml",this);
    QPushButton* Json = new QPushButton("Json", this);
    buttons.addButton(Xml,QDialogButtonBox::DestructiveRole);
    buttons.addButton(Json,QDialogButtonBox::DestructiveRole);
    form.addRow(&buttons);
    connect(Xml, SIGNAL(clicked()), this, SLOT(saveAsXml()));
    connect(Json, SIGNAL(clicked()), this, SLOT(saveAsJson()));
    connect(Xml, SIGNAL(clicked()), &saveDialog, SLOT(reject()));
    saveDialog.exec();
}

void View::saveAsJson(){
    if(tabView->count()==0) return;
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Select a directory"), "/home" );
    Parser* parser;
    QFile f(fileName + ".json");
    f.open( QIODevice::WriteOnly );
    parser = new JsonParser();
    try{
    parser->save(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel(), f);
    }
    catch(const QString& message){
        QMessageBox::critical(this,"Error found while parsing",message);
    }
    delete parser;
    f.close();
}

void View::saveAsXml(){

    auto rows_heads = static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel()->getRowsHeaders();
    for(auto head : rows_heads) if(DataTableModel::is_number(head.toString().toStdString())){
        QMessageBox::critical(this, "Error found while parsing","In Xml files row headers cannot be numbers");
        return;
    }

    if(tabView->count()==0) return;
    QString fileName = QFileDialog::getSaveFileName(nullptr, tr("Select a directory"), "/home" );
    Parser* parser;
    QFile f(fileName + ".xml");
    f.open( QIODevice::WriteOnly );
    parser = new XmlParser();
    parser->save(static_cast<Scene *>(tabView->widget(tabView->currentIndex()))->getModel(), f);
    delete parser;
    f.close();
}

View::~View()
{
}

