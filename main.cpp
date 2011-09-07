#include <QApplication>

#include "RegistrationForm.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        QApplication app(argc, argv);
        // While true:
        //     1. Instantiate RegistrationForm
        RegistrationForm regForm(0, argv[1]);
        //     2. Show regForm
        regForm.show();
        //     3. regForm done?
        return app.exec();
    }
    else
    {
        qDebug() << "Must provide filename!";
        return -1;
    }
}
