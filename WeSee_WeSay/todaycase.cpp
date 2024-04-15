#include "todaycase.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

TodayCase::TodayCase(const QDate &date, QWidget *parent) : QDialog(parent) {
    setFixedSize(1500, 1000);
    setWindowTitle("Today's Case");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    layout = new QGridLayout();
    mainLayout->addLayout(layout);

    label = new QLabel("Selected date: " + date.toString("yyyy-MM-dd"));
    mainLayout->addWidget(label);

    timeline = nullptr;
    loadEvents(date);
}

void TodayCase::loadEvents(const QDate &date) {
    QString month = date.toString("MM");
    QString day = date.toString("dd");
    QList<HistoricalEvent> events = retrieveEvents(month, day);
    for (const HistoricalEvent &event : events) {
        addToTimeline(event.year, event.event, event.eventTime, event.month, event.day, event.img, event.href, event.content);
    }
}

void TodayCase::addToTimeline(const QString &year, const QString &event, const QString &eventTime, const QString &month, const QString &day, const QString &img, const QString &href, const QString &content) {
    HistoricalEvent *newEvent = new HistoricalEvent;
    newEvent->event = event;
    newEvent->eventTime = eventTime;
    newEvent->month = month;
    newEvent->day = day;
    newEvent->img = img;
    newEvent->href = href;
    newEvent->content = content;
    newEvent->next = nullptr;

    if (!timeline) {
        timeline = newEvent;
        return;
    }

    HistoricalEvent *current = timeline;
    while (current->next) {
        current = current->next;
    }
    current->next = newEvent;
}

QList<HistoricalEvent> TodayCase::retrieveEvents(const QString &month, const QString &day) {
    QList<HistoricalEvent> events;

    // 这里是您从数据库中检索事件的示例代码
    // 请用您的实际数据库查询实现替换这部分代码

    // 假设您已经设置好了一个名为 "db" 的 QSqlDatabase
    QSqlQuery query;
    query.prepare("SELECT * FROM events WHERE month = :month AND day = :day");
    query.bindValue(":month", month);
    query.bindValue(":day", day);
    if (query.exec()) {
        while (query.next()) {
            HistoricalEvent event;
            event.year = query.value("year").toString();
            event.event = query.value("event").toString();
            event.eventTime = query.value("eventTime").toString();
            event.month = query.value("month").toString();
            event.day = query.value("day").toString();
            event.img = query.value("img").toString();
            event.href = query.value("href").toString();
            event.content = query.value("content").toString();
            events.append(event);
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return events;
}
