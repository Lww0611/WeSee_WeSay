// historypagedialog.h
#ifndef HISTORYPAGEDIALOG_H
#define HISTORYPAGEDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QPixmap>
#include <QTextEdit>

class HistoryPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryPageDialog(const QString& dynastyName, const QPixmap& image, const QString& history, QWidget *parent = nullptr);

private:
    QLabel *dynastyLabel;
    QLabel *imageLabel;
    QTextEdit *historyTextEdit;
};

#endif // HISTORYPAGEDIALOG_H
