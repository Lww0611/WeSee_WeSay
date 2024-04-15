// historypagedialog.cpp
#include "historypagedialog.h"
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>

HistoryPageDialog::HistoryPageDialog(const QString& dynastyName, const QPixmap& image, const QString& history, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("History Page");

    QVBoxLayout *layout = new QVBoxLayout(this);

    // 创建朝代标签
    dynastyLabel = new QLabel(dynastyName, this);
    QFont titleFont = dynastyLabel->font();
    titleFont.setPointSize(20);
    dynastyLabel->setFont(titleFont);
    layout->addWidget(dynastyLabel);

    // 创建朝代图片标签
    imageLabel = new QLabel(this);
    imageLabel->setPixmap(image);
    layout->addWidget(imageLabel);

    // 创建朝代历史信息文本框
    historyTextEdit = new QTextEdit(this);
    historyTextEdit->setReadOnly(true);
    historyTextEdit->setText(history);
    layout->addWidget(historyTextEdit);
}
