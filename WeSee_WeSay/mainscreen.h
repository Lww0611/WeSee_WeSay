#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QQueue>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include <vector>
#include "historypagedialog.h"

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void sliderValueChanged(int value);
    void showHistoryPage(int dynastyIndex);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QLabel *backgroundLabel;
    std::vector<QLabel*> slideshowLabels;
    std::vector<QPixmap> imageList;
    QSlider *slider;
    QSize standardSize;
    int numImages;
    int currentIndex;
    QPoint dragStartPosition;
};

#endif // MAINSCREEN_H
