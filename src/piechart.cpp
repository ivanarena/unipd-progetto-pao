#include "piechart.h"
#include <iostream>
#include <QMessageBox>

MainSlice::MainSlice(QPieSeries *Series, QObject *parent)
    : QPieSlice(parent),
      mSeries(Series)
{
    connect(this, &MainSlice::percentageChanged, this, &MainSlice::updateLabel);
    connect(this, &MainSlice::brushChanged, this , &MainSlice::updateColor);
}


QPieSeries *MainSlice::Series() const
{
    return mSeries;
}

void MainSlice::setName(QString name)
{
    mName = name;
}

QString MainSlice::name() const
{
    return mName;
}


void MainSlice::updateLabel()
{
    this->setLabel(QString("%1 %2%").arg(mName).arg(percentage() * 100, 0, 'f', 2));
}


void MainSlice::updateColor(){
    for(auto slice : mSeries->slices())  slice->setColor(this->color());
}


QPieSeries* MainSlice::extseries() const{
    return mSeries;
}

void PieChart::setAngles() {
    qreal angle = 0;
    const auto slices = mainSeries->slices();
    for (QPieSlice *slice : slices) {
        QPieSeries *Series = qobject_cast<MainSlice *>(slice)->Series();
        Series->setPieStartAngle(angle);
        angle += slice->percentage() * 360.0;
        Series->setPieEndAngle(angle);
    }
}

void PieChart::setMaxSlice(){
    MainSlice* max = nullptr;
    double maxPerc=0.0;
    for(auto it = mainSlices.begin(); it!= mainSlices.end(); ++it ){
        if((*it)->percentage()>maxPerc) {
            max = *it;
            maxPerc = (*it)->percentage();
        }
    }
    if(maxSlice == max) return;

    else {
        if(maxSlice)  maxSlice->extseries()->setLabelsVisible(false);
        maxSlice = max;
        QPieSeries* maxSeries = maxSlice->extseries();
        maxSeries->setLabelsVisible();
        maxSeries->setLabelsPosition(QPieSlice::LabelOutside);

    }
}

void PieChart::updateChartView(){
    for(auto slice : mainSlices){
        slice->setValue(slice->extseries()->sum());
        slice->setLabelVisible(true);
    }
    setAngles();
    setMaxSlice();
}

void PieChart::setExtSeries(QPieSeries * serie, QFont font){
    const auto slices = serie->slices();
    for (QPieSlice *slice : slices) {
        slice->setLabelFont(font);
    }
}

void PieChart::insertToPie(QPieSeries* externalSeries){
    QFont font("Arial", 8);


    MainSlice *mainSlice = new MainSlice(externalSeries);
    mainSlice->setName(externalSeries->name());
    mainSlice->setValue(externalSeries->sum());
    mainSeries->append(mainSlice);


    mainSlice->setLabelVisible(true);
    mainSlice->setLabelColor(Qt::white);
    mainSlice->setLabelPosition(QPieSlice::LabelInsideNormal);
    mainSlice->setLabelFont(font);
    mainSlices.push_back(mainSlice);

    externalSeries->setPieSize(0.7);
    externalSeries->setHoleSize(0.6);
    QChart::addSeries(externalSeries);

    setExtSeries(externalSeries, font);


    PieChart::updateChartView();
}

bool PieChart::isEmpty() const{
    for(int i = 0; i<model->columnCount(); ++i) for(auto row : model->getData()) if(row[i]!= 0) return false;
    return true;
}

bool PieChart::hasNegative() const{
    for(int i = 0; i<model->columnCount(); ++i) for(auto row : model->getData()) if(row[i]< 0) return true;
    return false;
}

void PieChart::clearChart(){
    for(auto slice : mainSlices){
        slice->extseries()->slices().clear();
        slice->extseries()->clear();
    }
    mainSlices.clear();
    mainSeries->clear();
    maxSlice = nullptr;
}

void PieChart::mapData(){
    vector<vector<double>> values = model->getData();
    vector<QVariant> rowHeaders = model-> getRowsHeaders();
    vector<QVariant> columnHeaders = model->getColumnsHeaders();
    for(int row_i = 0; row_i < model->rowCount(); ++row_i){
        QPieSeries* serie = new QPieSeries();
        serie->setName(rowHeaders[row_i].toString());
        for(int column_i = 0; column_i < model->columnCount(); ++column_i){
            serie->append(columnHeaders[column_i].toString(),values[row_i][column_i]);
        }
        insertToPie(serie);
    }
}


void PieChart::checkState(){
    bool zero = isEmpty();
    bool negative = hasNegative();
    if(state == consistent && !zero && !negative) return;
    else if(zero || negative){
        state=inconsistent;
        PieChart::clearChart();
        if(zero) throw QString("PieChart cannot be completely empty");
        else if(negative) throw QString("PieChart cannot have negative values");
    }

    else{
        PieChart::mapData();
        state=consistent;
    }
}


PieChart::PieChart(DataTableModel *p_model): Chart(p_model) {

    mainSeries = new QPieSeries();
    mainSeries->setPieSize(0.6);
    QChart::addSeries(mainSeries);
    setTitle("PieChart");
    setAnimationOptions(QChart::NoAnimation);
    legend()->setVisible(false);

    try {
        PieChart::checkState();
        if(state == consistent) PieChart::mapData();
    }
    catch(QString message) {QMessageBox::critical(nullptr,"Error",message); return; }
}


void PieChart::insertSeries(){
    try {
        if(state==inconsistent){
            checkState();
            return;
        }
    }
    catch(QString message) {QMessageBox::critical(nullptr,"Error",message); return; }
    catch(bool) { return; }
    vector<double> values = model->getData()[model->rowCount()-1];
    vector<QVariant> columnHeaders = model->getColumnsHeaders();
    const QString label = (model->getRowsHeaders()[model->rowCount()-1]).toString();
    QPieSeries* serie = new QPieSeries();
    serie->setName(label);
    for(int column_i = 0; column_i < model->columnCount(); ++column_i){
        serie->append(columnHeaders[column_i].toString(),values[column_i]);
    }
    insertToPie(serie);
}

void PieChart::removeSeries(){
    try {
        checkState();
        if(state==inconsistent) return;
    }
    catch(QString message) {QMessageBox::critical(nullptr,"Error",message); return; }
    catch(bool) {return; }

    mainSlices.back()->extseries()->clear();
    mainSlices.pop_back();
    mainSeries->remove(mainSeries->slices().back());
    updateChartView();

}

void PieChart::insertSeriesValue(){

    try {
        if(state==inconsistent){
            checkState();
            return;
        }
    }
    catch(QString message) {QMessageBox::critical(nullptr,"Error",message); return; }
    catch(bool) { return; }

    for(auto it = mainSlices.begin(); it!= mainSlices.end(); ++it){
            auto ext = (*it)->extseries();
            vector<vector<double>> data = model->getData();
            QPieSlice* newSlice = new QPieSlice(model->getColumnsHeaders()[model->columnCount()-1].toString(),model->getData()[model->rowCount()-1][model->columnCount()-1]);
            newSlice->setColor((*it)->color());
            if(model->rowCount()>0) ext->append(newSlice);
            setExtSeries(ext, QFont("Arial",8));
            updateChartView();
         }
}


void PieChart::removeSeriesValue(){
    try {
        checkState();
        if(state==inconsistent) return;

    }
    catch(QString message) {QMessageBox::critical(nullptr,"Error",message); return; }
    catch(bool) {return; }
    for(auto it = mainSlices.begin(); it!= mainSlices.end(); ++it){
        QPieSeries* serie = (*it)->extseries();
        if(serie && !(serie->slices().isEmpty())) serie->remove(serie->slices().back());
    }
    updateChartView();
}


void PieChart::replaceValue(QModelIndex i, QModelIndex j){
    try {checkState();}
    catch(QString message) {QMessageBox::critical(nullptr,"Error",message); return; }
    catch(bool) {return; }
    mainSlices[i.row()]->extseries()->slices()[j.column()]->setValue(model->getData()[i.row()][j.column()]);
    updateChartView();
}

void PieChart::updateSeriesName(Qt::Orientation orientation, int first, int last){
    if (orientation == Qt::Vertical){
        MainSlice* slice =mainSlices[first];
        slice->setName(model->getRowsHeaders()[last].toString());
        slice->updateLabel();
    }
    else for(auto slice : mainSlices) slice->extseries()->slices()[last]->setLabel(model->getColumnsHeaders()[last].toString());
    updateChartView();
}

PieChart::~PieChart(){
    PieChart::clearChart();
}
