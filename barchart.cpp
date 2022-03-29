#include "barchart.h"
#include "model.h"

void BarChart::mapData()
{
    vector<vector<double>> data = model->getData();
    for (int i = 0; i < model->rowCount(); i++)
    {
        const QString label = model->getRowsHeaders().at(i).toString();
        QBarSet *set = new QBarSet(label);

        for (int j = 0; j < model->columnCount(); j++)
            set->append(data[i].at(j));

        m_series->append(set);
        m_sets.push_back(set);
    }

    addSeries(m_series);

    m_series->attachAxis(XAxis);
    m_series->attachAxis(YAxis);

    BarChart::updateChartView();
}

void BarChart::updateChartView()
{
    YAxis->setRange(model->min(), model->max());
}

BarChart::BarChart(DataTableModel *c_model)
    : model(c_model), XAxis(new QBarCategoryAxis), YAxis(new QValueAxis), m_series(new QBarSeries)
{
    setTitle("Bar Chart");
    // TODO: set title to bold
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignTop);
    setAnimationOptions(QChart::AllAnimations);

    for (int i = 0; i < model->columnCount(); i++)
        XAxis->append(model->getColumnsHeaders().at(i).toString());

    addAxis(XAxis, Qt::AlignBottom);
    addAxis(YAxis, Qt::AlignLeft);

    BarChart::mapData();

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(replaceValue(QModelIndex,QModelIndex)));
    connect(model, SIGNAL(headerDataChanged(Qt::Orientation,int,int)), this, SLOT(updateSeriesName(Qt::Orientation,int,int)));
}

void BarChart::insertSeries()
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    const QString label = model->getRowsHeaders().at(model->rowCount() - 1).toString();
    QBarSet *set = new QBarSet(label);

    for (int j = 0; j < model->columnCount(); j++)
        set->append(data[model->columnCount() - 1].at(j));

    m_series->append(set);
    m_sets.push_back(set);

    updateChartView();
}

void BarChart::removeSeries()
{
    setAnimationOptions(QChart::SeriesAnimations);

    m_series->remove(dynamic_cast<QBarSet *>(m_sets.back()));
    m_sets.pop_back();

    updateChartView();
}

void BarChart::insertSeriesValue()
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    int i = 0;
    for (auto it = m_sets.begin(); it != m_sets.end(); it++)
    {
        (*it)->append(data[i].at(model->columnCount() - 1));
        i++;
    }

    XAxis->append(model->getColumnsHeaders().at(model->columnCount() - 1).toString());
    updateChartView();
}

void BarChart::removeSeriesValue()
{
    setAnimationOptions(QChart::SeriesAnimations);

    for (auto it = m_sets.begin(); it < m_sets.end(); it++)
        (*it)->remove(model->columnCount());

    XAxis->remove(*XAxis->categories().rbegin());
    updateChartView();
}

void BarChart::replaceValue(QModelIndex i, QModelIndex j) // i == j
{
    setAnimationOptions(QChart::SeriesAnimations);

    vector<vector<double>> data = model->getData();
    m_sets.at(i.row())->replace(j.column(), data[i.row()].at(j.column()));
    updateChartView();
}

void BarChart::updateSeriesName(Qt::Orientation orientation, int first, int last) // first == last
{
    setAnimationOptions(QChart::SeriesAnimations);

    if (orientation == Qt::Vertical)
        m_sets.at(first)->setLabel(model->getRowsHeaders().at(last).toString());
    else
        XAxis->replace(XAxis->categories().at(first), model->getColumnsHeaders().at(last).toString());
}
