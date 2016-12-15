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

        if(pushAlg == true && points.size()>0){

            // Draw points
            for(int i=0; i<countPoints; i++){
                painter.drawEllipse(points[i].x(), points[i].y(), r, r);
            }

            convexHull.clear();

            // Call current algorithm with timing
            QTime myTimer;
            myTimer.start();

            if(typeAlgorithm == QCK){
                convexHull = Algorithms::qhull(points);
            }else if(typeAlgorithm == INC){
                convexHull = Algorithms::incr(points);
            }else{
                convexHull = Algorithms::jarvis(points);
            }

            time_alg = myTimer.elapsed();

            QVector<QPoint> QConvexHull = QVector<QPoint>::fromStdVector(convexHull);
            painter.drawPolygon(QConvexHull);

        }

    }

    painter.end();

    pushGen = false;
    pushAlg = false;
}

QPoint Draw::generatePoint()
{
    QPoint point(rand()%800,rand()%800);

    return point;
}

void Draw::generatePoints(){

    for (int i=0;i<countPoints;i++)
    {
        points.push_back(generatePoint());
    }
}
