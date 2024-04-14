#include "EventControl.h"

EventControl::EventControl()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString currentPath = QCoreApplication::applicationDirPath();
    QFileInfo fileInfo;
    fileInfo.setFile(currentPath);
    QString rootPath;
    rootPath= fileInfo.absolutePath();
    fileInfo.setFile(rootPath);
    rootPath= fileInfo.absolutePath();
    db.setDatabaseName(rootPath + "/WeSee_WeSay/recources/history_today.db");

    if (!db.open()) {
        qDebug() << "Error: Failed to open database:" << db.lastError().text();
        exit(1);
    }

    query = QSqlQuery(db);
    queryindex = QSqlQuery(db);
}

EventControl::~EventControl()
{
    db.close();
}

QList<Eventinformation> *EventControl::getHistoryOfToday(int month, int day)
{

}

QList<EventShort> *EventControl::getEventshort(int month, int day)
{

}

Eventinformation *EventControl::getevent(qint64 eventid)
{

}
