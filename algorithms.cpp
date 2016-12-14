#include "algorithms.h"
#include "sortbyxasc.h"
#include "sortbyyasc.h"

double Algorithms::getTwoVectorsOrientation(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4)
{
    //Vector u = p2-p1 and v = p4-p3
    const double ux = p2.x() - p1.x();
    const double uy = p2.y() - p1.y();
    const double vx = p4.x() - p3.x();
    const double vy = p4.y() - p3.y();

    const double pi = atan(1.0);


    return acos((ux*vx + uy*vy)/(sqrt(ux*ux+uy*uy)*sqrt(vx*vx+vy*vy)))*(180/pi);

}

double Algorithms::getPointLineDistance(const QPointF &p, const QPointF &p1, const QPointF &p2){

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

int Algorithms::getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2)
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

vecQPoint Algorithms::jarvisScan(vecQPoint points)
{
    // Convex hull by Jarvis Scan
    vecQPoint ch;

    // Find points q,s
    /*
    qSort(points.begin(),points.end(),SortByYAsc());
    QPointF q = points[0];
    qSort(points.begin(),points.end(),SortByXAsc());
    QPointF s = points[0];
    */
    QVector<qreal> x;
    QVector<qreal> y;

    for (int i=0;i<points.size();i++){
        x.push_back(points[i].x());
        y.push_back(points[i].y());
    }

    qSort(x.begin(),x.end());
    qreal s = x[0];

    qSort(y.begin(),y.end());
    qreal q_tmp = y[0];
    QPointF q(0, q_tmp);

    // QPointF q = qMin(y.begin(),y.end());;
    // QPointF s = qMax(x.begin(),x.end());


    // Create initial edge
    QPointF pjj(s,q.y());
    QPointF pj = q;

    // Add q to Convec hull
    ch.push_back(pj);

    // Constract Convex Hull
    do{
        int idx_max = -1;
        double omg_max = 0;
        // double dist_max = 0;

        for(int i=0; i<points.size();i++){
            double omg = getTwoVectorsOrientation(pj,pjj,pj,points[i]);
            if(omg > omg_max){
                omg_max = omg;
                idx_max = i;
            }
            // TODO: For omg == omg_max, after d > dist_max
        }

        // Add point with max omega to Convex hull
        ch.push_back(points[idx_max]);

        // Assign points
        pjj = pj;
        pj  = points[idx_max];

    }while(pj != q);


    return ch;

}

void Algorithms::qHull(const vecQPoint &points){

    vecQPoint ch, uh, lh;
    std::sort(points.begin(), points.end(), SortByXAsc());

    // Find q1, q3
    QPointF q1 = points[0];
    QPointF q3 = points[points.size()-1];

    // Reordet to UH (Upper Hull), LH (Lower Hull)
    uh.push_back(q1);
    uh.push_back(q3);

    lh.push_back(q1);
    lh.push_back(q3);

    for (int i=0; i<points.size(); i++){

        // Add to UH
        if(getPointLinePosition(points[i], q1, q3) == 1)
        {
            uh.push_back(points[i]);
        }

        // Add to LH
        else if(getPointLinePosition(points[i], q1, q3) == 0)
        {
            lh.push_back(points[i]);
        }

    }

    ch.push_back(q3);
    qh(1, 0, uh, ch);
    ch.push_back(q1);
    qh(0,1,lh,ch);

}

void Algorithms::qh(const int s, const int e, const vecQPoint points, vecQPoint &ch){
    int i_max = -1;
    double d_max = 0;

    // Process all points
    for (int i=0; i<points.size(); i++){

        // Is a point in the right half-plane?
        if(getPointLinePosition(points[i], points[s], points[e]) == 1)
        {
            // Compute distance
            double d = getPointLineDistance(points[i], points[s], points[e]);

            // Compare to max
            if (d > d_max){
                d_max = d;
                i_max = i;
            }
        }

    }

    // Did we find any point
    if (i_max > 0){

        // Process first part of interval
        qh(s,i_max,points,ch);

        // Add furthest point to CH
        ch.push_back(points[i_max]);

        // Process second part of interval
        qh(i_max,e ,points,ch);
    }
}

vecQPoint Algorithms::incr(vecQPoint points){

    vecQPoint CH;
    const unsigned int m = points.size();

    // Sort points by X
    std::sort(points.begin(), points.end(), SortByXAsc());

    // Lists of next and previos points of CH
    std::vector<unsigned int> p(m),n(m);

    // Create initial approximation of CH
    p[0] = 1;
    n[0] = 1;
    p[1] = 0;
    n[1] = 0;

    // Incremental insertion: add all points one by one
    for(int i=0;i<m;i++)
    {
        // Point in the left halfplane
        if(getPointLinePosition(points[i],points[p[i-1]],points[i-1]) == 1)
        {
            // Join point and its previous/next vertices
            p[i] = i-1;
            n[i] = n[i-1];
        }

        // Point in the right halfplane
        else
        {
            // Join point and its previous/next vertices
            p[i] = p[i-1];
            n[i] = i-1;
        }

        // Set path to i
        n[p[i]] = i;
        p[n[i]] = i;

        // Fix upper tangent
        while(getPointLinePosition(points[n[n[i]]], points[i], points[n[i]]) < 1)
        {
            p[n[n[i]]] = i;
            n[i] = n[n[i]];
        }

        // Fix lower points
        while(getPointLinePosition(points[p[p[i]]], points[p[i]], points[i]) == 1)
        {
            n[p[p[i]]] = i;
            p[i] = p[p[i]];
        }

        // Convert Circular list to the list of points
        CH.push_back(points[0]);
        int idx = n[0];
        while (idx != 0)
        {
            CH.push_back(points[idx]);
            idx = n[idx];
        }

        return CH;
    }
}
