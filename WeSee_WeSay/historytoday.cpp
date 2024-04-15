#include "historytoday.h"
#include "todaycase.h"
#include <QVBoxLayout>
#include <QLabel>

HistoryToday::HistoryToday(QWidget *parent) : QWidget(parent) {

    // 设置窗口大小
    setFixedSize(1500, 1000);
    setWindowTitle("History Today");
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建日历表部件
    calendarWidget = new QCalendarWidget(this);
    layout->addWidget(calendarWidget);

    // 连接日期点击信号与槽
    connect(calendarWidget, &QCalendarWidget::clicked, this, &HistoryToday::openNewPage);
}

void HistoryToday::openNewPage(const QDate &date) {
    TodayCase *todaycase = new TodayCase(date, this); // 传递日期信息给 TodayCase 对象
    todaycase->show();
}

