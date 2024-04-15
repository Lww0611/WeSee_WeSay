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
    newEvent->year = year;
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
    // 假设数据库查询的实现在这里
    // 这里只是一个示例，实际实现会根据您的数据库结构来编写查询语句
    QString query = QString("SELECT * FROM events WHERE month = '%1' AND day = '%2'").arg(month, day);
    // 执行查询并将结果存入 events 列表
    // 示例代码中未包含数据库查询的完整实现，您需要根据自己的数据库和查询方式进行实现
    return events;
}
