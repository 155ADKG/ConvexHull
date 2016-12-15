#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *e)
{
    const unsigned int r = 2;
    QPainter painter(this);
    painter.begin(this);

    if(pushGen){

        // TODO: erase BRB !!!
        countPoints = 1000;

        points.clear();
        generatePoints();

        // vector.clear();

        // Draw point
        for(int i=0; i<countPoints; i++){
            painter.drawEllipse(points[i].x(), points[i].y(), r, r);
        }
    }else{

        if(points.size()>0){

            // Draw point
            for(int i=0; i<countPoints; i++){
                painter.drawEllipse(points[i].x(), points[i].y(), r, r);
            }

            // Call current algorithm
            convexHull.clear();

            if(typeAlgorithm == QCK){
                convexHull = Algorithms::qhull(points);
            }else if(typeAlgorithm == INC){
                convexHull = Algorithms::incr(points);
            }else{
                convexHull = Algorithms::jarvis(points);
            }
            qDebug() << convexHull.size();

            QVector<QPoint> QConvexHull = QVector<QPoint>::fromStdVector(convexHull);
            painter.drawPolygon(QConvexHull);

        }

        //QVector<QPoint> QConvexHull = QVector<QPoint>::fromStdVector(convexHull);

        //painter.drawPolygon(QConvexHull);
        //painter.drawPolyline(convexHull.data(), static_cast<int>(convexHull.size()));
    }


    //typeGenerate


    painter.end();

    pushGen = false;
}

QPoint Draw::generatePoint()
{
    QPoint point(rand()%400,rand()%400);

    return point;
}

void Draw::generatePoints(){

    for (int i=0;i<countPoints;i++)
    {
        points.push_back(generatePoint());
    }
}
