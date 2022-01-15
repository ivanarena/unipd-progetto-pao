#ifndef CHART_CONTAINER_H
#define CHART_CONTAINER_H

#include "chart.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;


/*
#include "Graph.h"



class GraphContainer
{
public:

    std::vector<std::shared_ptr<Graph>> Graphs;  //vettore contenente smart pointer che puntano ai grafici

    GraphContainer(Graph graph());
    ~GraphContainer();

    void addGraph();
    void removeGraph();
    void destroyProject();


};
*/

class ChartContainer
{
private:
    std::vector<std::shared_ptr<Chart>> charts;
public:
    ChartContainer();
    ChartContainer(std::vector<std::shared_ptr<Chart>> &charts);
    ~ChartContainer();

    void addChart();
};


#endif // CHART_CONTAINER_H
