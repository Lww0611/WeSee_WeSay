#include "mainscreen.h"
#include "historypagedialog.h" // 包含新页面的头文件

MainScreen::MainScreen(QWidget *parent)
    : QWidget(parent), numImages(16), currentIndex(0), dragStartPosition(-1, -1)
{
    setWindowTitle("Main Screen");

    // 设置窗口大小
    setFixedSize(1500, 1000);

    // 创建背景标签用于显示背景图片
    backgroundLabel = new QLabel(this);
    backgroundLabel->setGeometry(0, 0, width(), height());

    QPixmap backgroundPixmap("D:/Desktop/history/history/picture/background.jpg"); // 背景图片路径
    backgroundLabel->setPixmap(backgroundPixmap.scaled(size())); // 缩放背景图片以适应窗口大小
    backgroundLabel->setScaledContents(true);

    // 添加透明度效果
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0.3); // 设置透明度为 0.3
    backgroundLabel->setGraphicsEffect(opacityEffect);

    // 初始化图片列表
    for (int i = 0; i < numImages; ++i) {
        QPixmap pixmap(QString("D:/Desktop/history/history/picture/image%1.jpg").arg(i + 1));
        imageList.push_back(pixmap);
    }
    imageList.push_back(QPixmap()); // 将尾节点设置为空

    // 计算标准的缩放大小
    standardSize = QSize(width() / 3, height() - 100);

    // 创建标签用于显示轮播图
    for (int i = 0; i < 3; ++i) {
        QLabel *slideshowLabel = new QLabel(this);
        slideshowLabel->setGeometry((width() / 3) * i, 0, width() / 3, height() - 100);
        slideshowLabel->setPixmap(imageList[currentIndex + i].scaled(standardSize, Qt::KeepAspectRatio));
        slideshowLabel->setAlignment(Qt::AlignCenter);
        slideshowLabels.push_back(slideshowLabel);

        // 为每张图片添加点击事件处理
        slideshowLabel->installEventFilter(this);
    }

    // 创建滑动条
    slider = new QSlider(Qt::Horizontal, this);
    slider->setGeometry(50, height() - 50, width() - 100, 20);
    slider->setMinimum(0);
    slider->setMaximum(numImages - 1);
    slider->setValue(0);

    // 设置信号槽连接
    connect(slider, &QSlider::valueChanged, this, &MainScreen::sliderValueChanged);
}

void MainScreen::showHistoryPage(int dynastyIndex)
{
    if (dynastyIndex < 0 || dynastyIndex >= numImages) {
        // 检查索引是否有效
        return;
    }

    QString dynastyName = "某个朝代"; // 替换为实际的朝代名称
    QPixmap image = imageList[dynastyIndex];
    QString history = "这个朝代的历史信息。"; // 替换为实际的历史信息

    HistoryPageDialog dialog(dynastyName, image, history, this);
    dialog.exec();
}

bool MainScreen::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            for (int i = 0; i < 3; ++i) {
                if (obj == slideshowLabels[i]) {
                    showHistoryPage(currentIndex + i);
                    return true;
                }
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void MainScreen::mousePressEvent(QMouseEvent *event)
{
    // 记录鼠标按下时的位置
    if (event->buttons() == Qt::LeftButton) {
        dragStartPosition = event->pos();
    }
}

void MainScreen::mouseMoveEvent(QMouseEvent *event)
{
    // 如果鼠标按下并且移动距离足够大，切换图片
    if ((event->buttons() & Qt::LeftButton) && dragStartPosition.x() != -1) {
        int deltaX = event->x() - dragStartPosition.x();
        // 如果移动距离超过阈值，则切换图片
        if (std::abs(deltaX) > 20) { // 将阈值设置为20
            // 根据移动的距离决定切换的图片
            if (deltaX > 0) {
                // 向右移动
                if (currentIndex + 3 < numImages) { // 添加条件判断
                    currentIndex += 3;
                } else {
                    // 如果当前图片为最后一张图片，则限制不再向右移动
                    currentIndex = numImages - 3;
                }
            } else {
                // 向左移动
                currentIndex -= 3;
                if (currentIndex < 0)
                    currentIndex = 0; // 不再允许向左移动超出范围的图片
            }
            // 更新显示的图片
            for (int i = 0; i < 3; ++i) {
                slideshowLabels[i]->setPixmap(imageList[currentIndex + i].scaled(standardSize, Qt::KeepAspectRatio)); // 缩放图片以适应标签大小
            }
            // 同步滑动条位置
            slider->setValue(currentIndex);
            // 更新鼠标拖动起始位置
            dragStartPosition = event->pos();
        }
    }
}

void MainScreen::mouseReleaseEvent(QMouseEvent *event)
{
    // 清除鼠标按下时的位置
    dragStartPosition = QPoint(-1, -1);
}

void MainScreen::resizeEvent(QResizeEvent *event)
{
    // 调整背景图片大小
    backgroundLabel->setGeometry(0, 0, width(), height());

    // 计算缩放后的图片大小
    standardSize = QSize(width() / 3, height() - 100);

    // 调整轮播图标签大小和位置
    for (int i = 0; i < 3; ++i) {
        slideshowLabels[i]->setGeometry((width() / 3) * i, 0, width() / 3, height() - 100);
        slideshowLabels[i]->setPixmap(imageList[currentIndex + i].scaled(standardSize, Qt::KeepAspectRatio)); // 缩放图片以适应标签大小
    }

    // 调整滑动条位置
    slider->setGeometry(50, height() - 50, width() - 100, 20);
}

void MainScreen::sliderValueChanged(int value)
{
    currentIndex = value;

    // 创建一个新的队列来存储要展示的图片
    QQueue<QPixmap> slideshowQueue;

    // 将要展示的图片入队
    for (int i = 0; i < 3; ++i) {
        int index = currentIndex + i;
        if (index < numImages) {
            slideshowQueue.enqueue(imageList[index]);
        }
    }

    // 更新显示的图片
    for (int i = 0; i < 3; ++i) {
        if (!slideshowQueue.isEmpty()) {
            slideshowLabels[i]->setPixmap(slideshowQueue.dequeue().scaled(standardSize, Qt::KeepAspectRatio));
        }
    }

    // 启用或禁用滑动条
    slider->setEnabled(currentIndex + 3 < numImages);
}
