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
    DataTableModel* model;
    QPieSeries* mainSeries;
    vector<MainSlice*> mainSlices;
    MainSlice* maxSlice;

    vector<QColor> colors;

    void insertToPie(QPieSeries*, QColor);

    void setMaxSlice();
    void setAngles();
    bool colorYetUsed(const QColor&) const;
    QColor createRandomColor();

public:
    PieChart(DataTableModel *c_model);

    virtual void mapData() override;
    virtual void updateChartView() override;
    virtual void insertSeries() override; // add row
    virtual void removeSeries() override;
    //virtual void insertSeriesValue() override; // add column
    //virtual void removeSeriesValue() override;

public slots:
    //virtual void replaceValue(QModelIndex, QModelIndex) override;
    //virtual void updateSeriesName(Qt::Orientation, int, int) override;

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
    QPieSeries* series() const;

public Q_SLOTS:
    void updateLabel();
};

#endif // PIECHART_H

