#ifndef PIECHART_H
#define PIECHART_H

#include <QObject>
#include <QPieSeries>
#include "chart.h"
#include "model.h"

#include <QtCharts/QPieLegendMarker>
#include <QtCharts/QPieSlice>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class MainSlice;

class PieChart : public Chart
{
    Q_OBJECT

private:
    QPieSeries* mainSeries;
    vector<MainSlice*> mainSlices;
    MainSlice* maxSlice;

    vector<QColor> colors;

    void insertToPie(QPieSeries*, QColor);

    void setMaxSlice();
    void setAngles();
    bool colorYetUsed(const QColor&) const;
    QColor createRandomColor();
    void setExtSeries(QPieSeries*, QColor, QFont);
    void checkState() override;

public:
    PieChart(DataTableModel *c_model);
    ~PieChart();

    virtual void mapData() override;
    virtual void updateChartView() override;
    virtual void insertSeries() override; // add row
    virtual void removeSeries() override;
    virtual void insertSeriesValue() override; // add column
    virtual void removeSeriesValue() override;
    void clearChart() override;
    bool isEmpty() const;
    bool hasNegative() const;

public slots:
    virtual void replaceValue(QModelIndex, QModelIndex) override;
    virtual void updateSeriesName(Qt::Orientation, int, int) override;

};

class MainSlice : public QPieSlice
{
    Q_OBJECT
private:
    QPieSeries *mSeries;
    QString mName;
public:
    MainSlice(QPieSeries *Series, QObject *parent = 0);

    QPieSeries *Series() const;

    void setName(QString name);
    QString name() const;
    QPieSeries* extseries() const;

public Q_SLOTS:
    void updateLabel();
};

#endif // PIECHART_H

