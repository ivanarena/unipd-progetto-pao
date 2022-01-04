#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QWidget>

class Graph
{
public:

    std::string ofProject; // Voglio sapere a che DataSet un certo grafo appartiene. Motivi: - quando chiudo un progetto voglio chiudere/distruggere tutti i suoi grafi
                           //                                                                - serve per sapere in quali schede far visualizzare quali grafi
    Graph(std::string id): ofProject(id){};
    Graph(Graph &g);
    ~Graph();

    virtual void ShowGraph() = 0;

};

#endif // CHART_H
