#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "customtypes.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint> points;
    std::vector<QPoint> convexHull;
    typeGen typeGenerate;
    typeAlg typeAlgorithm;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushGen_clicked();

    void on_comboTypeGen_currentIndexChanged(int index);

    void on_pushAlg_clicked();

    void on_comboTypeAlg_currentIndexChanged(int index);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
