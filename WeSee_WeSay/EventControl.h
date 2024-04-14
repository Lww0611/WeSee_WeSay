#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H
#include <QtSql>
#include <QList>
#include "StructOfEvents.h"

class EventControl
{
public:

    QSqlDatabase db;
    QSqlQuery query;
    QSqlQuery queryindex;

    EventControl();
    ~EventControl();


    QList<Eventinformation>* getHistoryOfToday(int month, int day);
    QList<EventShort>* getEventshort(int month, int day);
    Eventinformation* getevent(qint64 eventid);
};

#endif // EVENTCONTROL_H
