#include "algorithms.h"
#include <QDebug>
#include "sortbyangleasc.h"
#include "removeduplicateangles.h"

std::vector<QPoint> Algorithms::graham(std::vector<QPoint> &points)
{

    //sort points by y
    sort(points.begin(),points.end(), SortByYAsc());
    QPoint q = points[0];
    QPoint x1(-800,q.y());

    points.erase(std::unique(points.begin()+1,points.end(),RemoveDuplicateAngles(q,x1)),points.end());

    sort(points.begin()+1,points.end(),SortByAngleAsc(q,x1));


    QStack<QPoint> Q;
    Q.push(q);
    Q.push(points[1]);
    QPoint brb;

    unsigned int j=2;
    while(j<points.size())
    {
        brb = Q.pop();

        if(getPointLinePosition(points[j],Q.top(),brb)==1)
        {
            Q.push(brb);
            Q.push(points[j]);
            j++;
        }

    }

    return Q.toStdVector();
}


double Algorithms::getTwoVectorsOrientation(const QPoint &p1, const QPoint &p2, const QPoint &p3, const QPoint &p4)
{
    //Vector u = p2-p1 and v = p4-p3
    const double ux = p2.x() - p1.x();
    const double uy = p2.y() - p1.y();
    const double vx = p4.x() - p3.x();
    const double vy = p4.y() - p3.y();

    const double pi =2.0*asin(1.0);
    return acos((ux*vx + uy*vy)/(sqrt(ux*ux+uy*uy)*sqrt(vx*vx+vy*vy)))*(180/pi);
}


double Algorithms::getPointLineDistance(const QPoint &p, const QPoint &p1, const QPoint &p2)
{
    double x = p.x();
    double y = p.y();
    double x1 = p1.x();
    double y1 = p1.y();
    double x2 = p2.x();
    double y2 = p2.y();

    double d = x*(y1-y2)+x1*(y2-y)+x2*(y-y1);
    d /= sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

    return d;
}

std::vector<QPoint> Algorithms::incr(std::vector<QPoint> &points)
{

    std::vector<QPoint> CH;

    //Sort points by X
    std::sort(points.begin(),points.end(),SortByXAsc());

    //points.erase(std::remove_if(points.begin(),points.end(),RemoveDuplicatePoints()),points.end());
    points.erase(std::unique(points.begin(),points.end(),RemoveDuplicatePoints()), points.end());

    //List of previous and next points of CH
    const unsigned int m=points.size();
    std::vector<unsigned int> p(m), n(m);

    //Create inital approximation of CH
    p[0] = 1;
    n[0] = 1;
    p[1] = 0;
    n[1] = 0;

    //Incremental insertion: add all points one by one
    for(unsigned int i=2;i < m;i++)
    {

//        for (unsigned int j=i+1;j<m;j++){
//            if(points[i]==points[j]){
//                points.erase(points.begin()+j);
//            }
//        }

        //Point in the left halfplane
        if(getPointLinePosition(points[i],points[p[i-1]],points[i-1])==1)
        {

            //Set path from i
            p[i] = i-1;
            n[i] = n[i-1];
        }

        //Point in the right halfplane
        else
        {

            //Set path from i
            p[i] = p[i-1];
            n[i] = i-1;
        }

        //Set path to i
        n[p[i]] = i;
        p[n[i]] = i;

        //Fix upper tangent
        while (getPointLinePosition(points[n[n[i]]],points[i],points[n[i]])==0)
        {
            p[n[n[i]]] = i;
            n[i] = n[n[i]];
        }

        //Fix lower tangent
       // qDebug()<<getPointLinePosition(points[i],points[p[i]],points[p[p[i]]]);

        while (getPointLinePosition(points[p[p[i]]],points[p[i]],points[i])==0)
        {
            n[p[p[i]]] = i;
            p[i] = p[p[i]];
        }

    }
        //Convert Circular list to the list of points
        CH.push_back(points[0]);
        int idx = n[0];
        while (idx!=0)
        {
            CH.push_back(points[idx]);
            idx = n[idx];
        }

    return CH;
}


std::vector<QPoint> Algorithms::qhull(std::vector<QPoint> points)
{
    std::vector<QPoint> ch, uh, lh;

    std::sort(points.begin(),points.end(),SortByXAsc());

    //Find q1, q3
    QPoint q1 = points[0];
    QPoint q3 = points[points.size()-1];

    //Reorder to UH, LH
    uh.push_back(q1);
    uh.push_back(q3);
    lh.push_back(q1);
    lh.push_back(q3);

    for (unsigned int i=0;i<points.size();i++)
    {
        //Add to UH
        if(getPointLinePosition(points[i],q1,q3)==1)
            uh.push_back(points[i]);

        //Add to LH
        else if(getPointLinePosition(points[i],q1,q3)==0)
            lh.push_back(points[i]);

    }

    //Process upper hull
    ch.push_back(q3);
    qh(1,0,uh,ch);

    //Process lower hull
    ch.push_back(q1);
    qh(0,1,lh,ch);

    return ch;
}

void Algorithms::qh(const int s, const int e, const std::vector<QPoint> points, std::vector<QPoint> &ch)
{
    int i_max = -1;
    double d_max = 0;

    for(unsigned int i=2;i<points.size();i++)
    {
        if(getPointLinePosition(points[i],points[s],points[e])==0)
        {
            double d = getPointLineDistance(points[i],points[s],points[e]);

            //Compare to dmax qh(s, i_max, points, ch);
            if (d > d_max)
            {
                d_max = d;
                i_max = i;
            }
        }
    }

    //Did we find any point
    if (i_max>0)
    {

        //Process first interval
        qh(s, i_max, points, ch);

        //Add furthest point to CH
        ch.push_back(points[i_max]);

        //Process second part of interval
        qh(i_max, e, points, ch);
    }
}

int Algorithms::getPointLinePosition(const QPoint &p, const QPoint &p1, const QPoint &p2)
{
    //Vector u = p2-p1 and v = p2-p
    const double ux = p2.x() - p1.x();
    const double uy = p2.y() - p1.y();
    const double vx = p.x() - p1.x();
    const double vy = p.y() - p1.y();

    //Test criterion
    const double t = ux*vy - vx*uy;

    //P is in the left halfplpane
    if (t<0)
        return 1;

    //P is in the right halfplpane
    if (t>0)
        return 0;

    //P is on the edge
    return -1;
}

std::vector<QPoint> Algorithms::jarvis(std::vector<QPoint> points)
{
    //Convex hull by jarvis
    std::vector<QPoint> ch;

    //Possible:
    sort(points.begin(),points.end(), SortByYAsc());
    QPoint q = points[0];
    sort(points.begin(),points.end(), SortByXAsc());
    QPoint s = points[0];


    //Find q,s
  //  QPoint q = min (points.begin(),points.end(), sortByYAsc());
    //QPoint s = min (points.begin(),points.end(), sortByXAsc());

    //Create initial edge
    QPoint pjj(s.x()-1,q.y());
    QPoint pj = q;

    //Add q to ch
    ch.push_back(q);

    //Construct convex hull
    do
    {
        int idx_max = -1;
        double omg_max = 0;
        double d_max = 0;

        for (unsigned int i=0;i<points.size();i++)
        {
            double omg = getTwoVectorsOrientation(pj,pjj,pj,points[i]);
            if (omg > omg_max)
            {
                omg_max = omg;
                idx_max = i;
                d_max = sqrt((points[i].x()-pj.x())*(points[i].x()-pj.x()) + (points[i].y()-pj.y())*(points[i].y()-pj.y()));
            }
            else if (omg == omg_max)
            {
                double d = sqrt((points[i].x()-pj.x())*(points[i].x()-pj.x()) + (points[i].y()-pj.y())*(points[i].y()-pj.y()));
                if(d_max < d)
                {
                    omg_max = omg;
                    idx_max = i;
                    d_max = d;
                }
            }
            //Resolve colinear points

        }
        //Add point pi to ch
        ch.push_back(points[idx_max]);

        //Assign points
        pjj = pj;
        pj = points[idx_max];
    }while(pj != q);
    return ch;
}

void Algorithms::generatePoints(std::vector<QPoint> &points, int countPoints, typeGen typeGenerate, int win_w, int win_h){

    if(typeGenerate == CLUS)
    {
        while (points.size() < countPoints)
        {
            QPoint pivot(rand()%win_w,rand()%win_h);
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
        for(float x=0; x<win_w; x += win_w/sqrt(countPoints))
        {
            for(float y=0; y<win_h; y += win_h/sqrt(countPoints))
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
            points.push_back(QPoint(rand()%win_w,rand()%win_h));
        }
    }

}
