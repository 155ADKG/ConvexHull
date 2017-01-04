#ifndef REMOVEDUPLICATEANGLES_H
#define REMOVEDUPLICATEANGLES_H
#include "algorithms.h"

class RemoveDuplicateAngles
{

private:
    QPoint s;
    QPoint e;
public:
    RemoveDuplicateAngles(const QPoint &s_, const QPoint &e_){s = s_;e = e_;}

    bool operator() (const QPoint &p1, const QPoint &p2)
    {

        const double eps=1.0e-03;

        if (fabs(Algorithms::getTwoVectorsOrientation(s,p1,s,e) - Algorithms::getTwoVectorsOrientation(s,p2,s,e))<eps)
        {
            return (p1.x()*p1.x() + p1.y()*p1.y()) < (p2.x()*p2.x() + p2.y()*p2.y());
        }
        return false;

    }
};

#endif // REMOVEDUPLICATEANGLES_H
