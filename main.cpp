#include <QApplication>

#include "RegistrationForm.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        QApplication app(argc, argv);
        RegistrationForm regForm(0, argv[1]);
        regForm.show();
        return app.exec();
    }
    else
    {
        qDebug() << "Must provide filename!";
        return -1;
    }
}
