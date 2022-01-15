#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QtCharts>
#include <QWidget>

class Chart
{
private:
    QChart *chartPtr;
public:

    //std::string ofProject; // Voglio sapere a che DataSet un certo grafo appartiene. Motivi: - quando chiudo un progetto voglio chiudere/distruggere tutti i suoi grafi
                           //                                                                - serve per sapere in quali schede far visualizzare quali grafi
    Chart(QChart *newChart = nullptr);
    Chart(Chart &c);
    ~Chart();


};

#endif // CHART_H
