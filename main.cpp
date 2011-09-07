#include <QApplication>

#include "RegistrationForm.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    RegistrationForm regForm(0, (argc > 1) ? argv[1] : "Data.csv");
    regForm.show();
    return app.exec();
}
