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
        countPoints = 100;

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

void Draw::generatePoints(){

    if(typeGenerate == CLUS)
    {
        // TODO: vector rand QPoint - example 10 points
        // TODO: for vector generate nex points in cluster
        std::vector<QPoint> clus;
        clus.clear();
        for(int i=0;i<10;i++)
        {
            clus.push_back((QPoint(rand()%800,rand()%800)));
        }

        for(int i=0;i<clus.size();i++)
        {
            points.push_back(clus[i]);
            points.push_back(QPoint(clus[i].x()+rand()%20,clus[i].y()+rand()%20));
            points.push_back(QPoint(clus[i].x()+rand()%20,clus[i].y()+rand()%20));
            points.push_back(QPoint(clus[i].x()+rand()%20,clus[i].y()+rand()%20));
            points.push_back(QPoint(clus[i].x()+rand()%20,clus[i].y()+rand()%20));
        }




    }else if(typeGenerate == GRID)
    {
        for(float x=0; x<800; x += 800.0/sqrt(countPoints))
        {
            for(float y=0; y<800; y += 800.0/sqrt(countPoints))
            {
                points.push_back(QPoint(x,y));

                // Exception for QPoint - we work with integer..
                if (points.size() == countPoints)
                    break;
            }
        }
    }
    else
    {
        for (int i=0;i<countPoints;i++)
        {
            points.push_back(QPoint(rand()%800,rand()%800));
        }
    }

}
