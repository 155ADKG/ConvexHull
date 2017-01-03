#include "draw.h"
#include "customtypes.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *e)
{
    const unsigned int r = 4;
    QPainter painter(this);
    painter.begin(this);

    // Draw points
    for(int i=0; i<points.size(); i++){
        painter.drawEllipse(points[i].x()-r/2, points[i].y()-r/2, r, r);
    }

    // Draw ConvexHull
    if(convexHull.size()>0){

        QVector<QPoint> QConvexHull = QVector<QPoint>::fromStdVector(convexHull);
        painter.setPen(QPen(Qt::magenta, 2));
        painter.drawPolygon(QConvexHull);

    }

    painter.end();
}

