#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include "algorithms.h"

class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint> points;
    std::vector<QPoint> convexHull;
    unsigned int countPoints;

public:
    explicit Draw(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);

    void setGenPoints(std::vector<QPoint> points_){ points = points_; }
    void setGenCH(std::vector<QPoint> convexHull_){ convexHull = convexHull_; }

};

#endif // DRAW_H
