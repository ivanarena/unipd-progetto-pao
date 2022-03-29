#include "piechart.h"
#include "modelerror.h"
#include <iostream>

MainSlice::MainSlice(QPieSeries *Series, QObject *parent)
    : QPieSlice(parent),
      mSeries(Series)
{
    connect(this, &MainSlice::percentageChanged, this, &MainSlice::updateLabel);
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
    if(!maxSlice){
        maxSlice = max;
        QPieSeries* maxSeries = maxSlice->extseries();
        maxSeries->setLabelsVisible(true);
        maxSeries->setLabelsPosition(QPieSlice::LabelOutside);
    }
    else if(maxSlice!=max){
        QPieSeries* maxSeries = maxSlice->extseries();
        maxSeries->setLabelsVisible(false);
        maxSlice = max;
        maxSeries = maxSlice->extseries();
        maxSeries->setLabelsVisible();
        maxSeries->setLabelsPosition(QPieSlice::LabelOutside);
    }
    else{
        QPieSeries* maxSeries = maxSlice->extseries();
        maxSeries->setLabelsVisible(true);
    }
}

bool PieChart::colorYetUsed(const QColor& color) const{
    for(auto it = colors.begin(); it!=colors.end(); ++it){
        if(*it == color) return true;
    }
    return false;
}


QColor PieChart::createRandomColor(){
    srand(time(NULL));
    QColor color = QColor(rand()%255,rand()%255,rand()%255);
    while(colorYetUsed(color) || color.lightness()>200 ) color = QColor(rand()%255,rand()%255,rand()%255);
    colors.push_back(color);
    return color;
}

void PieChart::updateChartView(){
    setAngles();
    setMaxSlice();
    for(auto slice : mainSlices){
        slice->setValue(slice->extseries()->sum());
    }
}

void PieChart::setExtSeries(QPieSeries * serie, QColor color, QFont font){
    const auto slices = serie->slices();
    for (QPieSlice *slice : slices) {
        color = color.lighter(105);
        slice->setBrush(color);
        slice->setLabelFont(font);
    }
}

void PieChart::insertToPie(QPieSeries* externalSeries, QColor color){
    QFont font("Arial", 8);


    MainSlice *mainSlice = new MainSlice(externalSeries);
    mainSlice->setName(externalSeries->name());
    mainSlice->setValue(externalSeries->sum());
    mainSeries->append(mainSlice);

    mainSlice->setBrush(color);
    mainSlice->setLabelVisible();
    mainSlice->setLabelColor(Qt::white);
    mainSlice->setLabelPosition(QPieSlice::LabelInsideNormal);
    mainSlice->setLabelFont(font);
    mainSlices.push_back(mainSlice);

    externalSeries->setPieSize(0.7);
    externalSeries->setHoleSize(0.6);
    setExtSeries(externalSeries, color, font);

    QChart::addSeries(externalSeries);

    PieChart::updateChartView();
}




void PieChart::insertSeries(){  //UNA SERIE CON TUTTI VALORI A 0 MANDA A PUTTANE LA PIE
    /*
    vector<double> values = model->getData()[model->rowCount()-1];
    vector<QVariant> columnHeaders = model->getColumnsHeaders();
    const QString label = (model->getRowsHeaders()[model->rowCount()-1]).toString();
    QPieSeries* serie = new QPieSeries();
    serie->setName(label);
    for(int column_i = 0; column_i < model->m_columnCount; ++column_i){
        serie->append(columnHeaders[column_i].toString(),values[column_i]);
    }
    */
    if(model->columnCount()==0) return;
    setVisible(true);
    QPieSeries* serie = new QPieSeries();
    serie->setName("TEST");
    for(int i = 0; i<model->columnCount(); ++i){
        serie->append("test", 10);
    }
    insertToPie(serie,createRandomColor());
}

void PieChart::removeSeries(){
    if(mainSeries->count()>1){
        mainSlices.back()->extseries()->clear();
        mainSlices.pop_back();
        mainSeries->remove(mainSeries->slices().back());
        updateChartView();
    }
    else if(mainSeries->count()==1){
        mainSlices.back()->extseries()->clear();
        mainSlices.pop_back();
        mainSeries->clear();
        colors.clear();
        maxSlice=nullptr;
    }
}

void PieChart::insertSeriesValue(){
    setVisible(true);
    /*
    vector<vector<double>> data = model->getData();
    QString label = model->getColumnsHeaders()[model->columnCount()-1].toString();
    int i=0;
    for(auto it = mainSlices.begin(); it!= mainSlices.end(); ++it, ++i){
        (*it)->series()->append(new QPieSlice(label,data[i][model->columnCount()-1]));
    }*/
    if(model->columnCount()==1 && model->rowCount()>0){
        /*
        vector<double> values = model->getData().front();
        QString rowHeader = model->getRowsHeaders().front().toString();
        vector<QVariant> columnHeaders = model->getColumnsHeaders();
        QPieSeries* serie = new QPieSeries();
        serie->setName(rowHeader);
        for(int i=0; i<model->columnCount(); ++i){
            serie->append(columnHeaders[i].toString(), values[i]);
        }*/

        QPieSeries* serie = new QPieSeries();
        serie->setName("prova");
        serie->append("e",2);
        insertToPie(serie,createRandomColor());
        updateChartView();
    }
    if(mainSeries->count()==0) return;
    for(auto it = mainSlices.begin(); it!= mainSlices.end(); ++it){
        auto ext = (*it)->extseries();
        ext->append(new QPieSlice("Ima",10));
        setExtSeries(ext, (*it)->color(), QFont("Arial",8));
    }
    updateChartView();
}

void PieChart::removeSeriesValue(){
    //if(mainSeries->count()==0) return;
    for(auto it = mainSlices.begin(); it!= mainSlices.end(); ++it){
        QPieSeries* serie = (*it)->extseries();
        if(serie && !(serie->slices().isEmpty())) serie->remove(serie->slices().back());
    }
    updateChartView();
    if(model->columnCount()==0) setVisible(false);
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
        insertToPie(serie, createRandomColor());
    }
}


PieChart::PieChart(DataTableModel *p_model): model(p_model) {
    //if(model->isThereZeroRow()) throw new modelError();
    mainSeries = new QPieSeries();
    mainSeries->setPieSize(0.6);
    QChart::addSeries(mainSeries);
    setTitle("PieChart");
    legend()->setVisible(false);
    PieChart::mapData();
}
