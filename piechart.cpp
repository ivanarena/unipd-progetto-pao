#include "piechart.h"
#include "modelerror.h"

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

QPieSeries* MainSlice::series() const{
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
        QPieSeries* maxSeries = maxSlice->series();
        maxSeries->setLabelsVisible();
        maxSeries->setLabelsPosition(QPieSlice::LabelOutside);
    }
    if(maxSlice!=max){
        QPieSeries* maxSeries = maxSlice->series();
        maxSeries->setLabelsVisible(false);
        maxSlice = max;
        maxSeries = maxSlice->series();
        maxSeries->setLabelsVisible();
        maxSeries->setLabelsPosition(QPieSlice::LabelOutside);
    }
}

bool PieChart::colorYetUsed(const QColor& color) const{
    for(auto it = colors.begin(); it!=colors.end(); ++it){
        if(*it == color) return true;
    }
    return false;
}

void PieChart::updateChartView(){
    setAngles();
    setMaxSlice();
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
    const auto slices = externalSeries->slices();
    for (QPieSlice *slice : slices) {
        color = color.lighter(105);
        slice->setBrush(color);
        slice->setLabelFont(font);
    }


    QChart::addSeries(externalSeries);

    PieChart::updateChartView();
}

QColor PieChart::createRandomColor(){
    srand(time(NULL));
    QColor color = QColor(rand()%255,rand()%255,rand()%255);
    while(colorYetUsed(color) || color.lightness()>200 ) color = QColor(rand()%255,rand()%255,rand()%255);
    colors.push_back(color);
    return color;
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
    QPieSeries* serie = new QPieSeries();
    serie->setName("TEST");
    for(int i = 0; i<model->columnCount(); ++i){
        serie->append("test", 10);
    }
    insertToPie(serie,createRandomColor());
    //if(mainSeries->count()==1) setVisible(true);
}

void PieChart::removeSeries(){
    if(mainSeries->count()>1){
        mainSlices.back()->series()->clear();
        mainSlices.pop_back();
        mainSeries->remove(mainSeries->slices().back());
        updateChartView();
    }
    else{
        mainSlices.back()->series()->clear();
        mainSlices.pop_back();
        mainSeries->clear();
    }
}

void PieChart::mapData(){
    vector<vector<double>> values = model->getData();
    vector<QVariant> rowHeaders = model-> getRowsHeaders();
    vector<QVariant> columnHeaders = model->getColumnsHeaders();
    srand(time(NULL));
    for(int row_i = 0; row_i < model->m_rowCount; ++row_i){
        QPieSeries* serie = new QPieSeries();
        serie->setName(rowHeaders[row_i].toString());
        for(int column_i = 0; column_i < model->m_columnCount; ++column_i){
            serie->append(columnHeaders[column_i].toString(),values[row_i][column_i]);
        }
        insertToPie(serie, createRandomColor());
    }
}


PieChart::PieChart(DataTableModel *p_model): model(p_model) {
    if(model->isThereZeroRow()) throw new modelError();
    mainSeries = new QPieSeries();
    mainSeries->setPieSize(0.6);
    QChart::addSeries(mainSeries);
    setTitle("PieChart");
    legend()->setVisible(false);
    PieChart::mapData();
}
