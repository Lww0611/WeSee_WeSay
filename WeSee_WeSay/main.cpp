#include "Widget.h"
#include "ProjectPeopleOfAllAges.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProjectPeopleOfAllAges w;
    w.show();
    return a.exec();
}
