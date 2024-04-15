#ifndef KINGHISTORY_H
#define KINGHISTORY_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class KingHistory : public QWidget {
    Q_OBJECT
public:
    explicit KingHistory(QWidget *parent = nullptr);

private slots:
    void openHistoryDynastyPage();
    void openRelationGraphPage();
    void openhistorytoday() ;

private:
    QLabel *backgroundLabel;
};

#endif // KINGHISTORY_H
