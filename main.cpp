#include "view.h"
#include "model.h"

#include <QApplication>
#include <QTableView>

#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    View gui;
    gui.show();



    //TEST PARSER: /*

        //SAVING PART:
/*
    pair<vector<string>,vector<vector<int>>> test;

    test.first.push_back("Lunedi");
    test.first.push_back("Martire");
    test.first.push_back("Mercore");

    vector<int> testin = {2,3,45,1};

    test.second.push_back(testin);
    test.second.push_back(testin);
    test.second.push_back(testin);

    saveJson(test,"test");


    //LOADING PART:

    pair<vector<string>,vector<vector<int>>> data = loadJson("test.json");
    */
    //END OF TEST


    return app.exec();
}
