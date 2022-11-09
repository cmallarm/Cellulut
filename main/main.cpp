#include <QApplication>
#include "autocell.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    AutoCell window;
    window.setWindowTitle("Cellul'UT");
    window.show();

    return app.exec();
}
