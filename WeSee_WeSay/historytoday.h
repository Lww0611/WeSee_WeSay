#ifndef HISTORYTODAY_H
#define HISTORYTODAY_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>

class HistoryToday : public QWidget {
    Q_OBJECT
public:
    explicit HistoryToday(QWidget *parent = nullptr);

private slots:
    void openNewPage(const QDate &date);

private:
    QCalendarWidget *calendarWidget;
};

#endif // HISTORYTODAY_H

