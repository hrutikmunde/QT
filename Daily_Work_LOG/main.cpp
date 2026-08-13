#include "loginpage.h"

#include <QApplication>

#include "loginpage.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!Database::initialize())
    {
        return -1;
    }

    LoginPage w;
    w.show();

    return a.exec();
}
