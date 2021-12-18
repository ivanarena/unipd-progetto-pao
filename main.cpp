#include "view.h"
#include "model.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    View gui;
    gui.show();

    return app.exec();
}
