#ifndef TODAYCASE_H
#define TODAYCASE_H

#include <QDialog>
#include <QDate>
#include <QList>

// 定义历史事件结构体
struct HistoricalEvent {
    QString event;
    QString eventTime;
    QString month;
    QString day;
    QString img;
    QString href;
    QString content;
    HistoricalEvent *next;
};


class QLabel;
class QGridLayout;

class TodayCase : public QDialog {
    Q_OBJECT
public:
    explicit TodayCase(const QDate &date, QWidget *parent = nullptr);

private:
    void loadEvents(const QDate &date);
    void TodayCase::addToTimeline(const QString &year, const QString &event, const QString &eventTime, const QString &month, const QString &day, const QString &img, const QString &href, const QString &content) ;
    QLabel *label;
    QGridLayout *layout;
    HistoricalEvent *timeline;

    // 数据库检索函数
    QList<QString> retrieveEvents(const QString &month, const QString &day);
};

#endif // TODAYCASE_H
