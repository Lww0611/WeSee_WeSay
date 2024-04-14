#ifndef STRUCTOFEVENTS_H
#define STRUCTOFEVENTS_H
#include <QString>

struct Eventinformation
{
    QString eventid;
    QString event;
    QString eventtime;
    QString month;
    QString day;
    QString content;
};

struct EventShort
{
    QString event;
    QString eventtime;
};


#endif // STRUCTOFEVENTS_H
