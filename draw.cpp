#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent)
{

}

void Draw::paintEvent(QPaintEvent *e)
{
    const unsigned int r = 4;
    QPainter painter(this);
    painter.begin(this);

    if(pushGen){

        // TODO: erase BRB !!!
        countPoints = 10000;

        points.clear();
        generatePoints();

        // Draw point
        for(int i=0; i<countPoints; i++){
            painter.drawEllipse(points[i].x()-r/2, points[i].y()-r/2, r, r);
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

void Draw::generatePoints(){

    const int win_size = 800;

    if(typeGenerate == CLUS)
    {
        while (points.size() < countPoints)
        {
            QPoint pivot(rand()%win_size,rand()%win_size);
            points.push_back(pivot);

            for(int i=0; i<rand()%100; i++)
            {
                if(points.size()>=countPoints)
                {
                    break;
                }

                points.push_back(QPoint(pivot.x()+rand()%10,pivot.y()+rand()%5));
            }
        }
    }
    else if(typeGenerate == GRID)
    {
        for(float x=0; x<win_size; x += win_size/sqrt(countPoints))
        {
            for(float y=0; y<win_size; y += win_size/sqrt(countPoints))
            {
                points.push_back(QPoint(x,y));

                // Exception for QPoint - we work with integer..
                if (points.size() == countPoints)
                {
                    break;
                }
            }
        }
    }
    else
    {
        for (int i=0;i<countPoints;i++)
        {
            points.push_back(QPoint(rand()%win_size,rand()%win_size));
        }
    }

}
