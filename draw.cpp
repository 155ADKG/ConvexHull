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
        // TODO: Call algorithms / Jarvis Scan
        convexHull.clear();
        //convexHull = Algorithms::jarvisScan(points);

        //painter.drawPolygon(convexHull);
    }



    //typeGenerate


    painter.end();

    pushGen = false;
}

QPoint Draw::generatePoint()
{
    QPoint point(rand()%700,rand()%700);

    return point;
}

void Draw::generatePoints(){

    for (int i=0;i<countPoints;i++)
    {
        points.push_back(generatePoint());
    }
}
