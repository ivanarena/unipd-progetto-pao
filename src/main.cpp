#include "view.h"
#include "model.h"

#include <QApplication>
#include <QTableView>

#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    View gui;
    gui.setWindowTitle("Progetto P.A.O.");
    gui.show();

    return app.exec();
}
