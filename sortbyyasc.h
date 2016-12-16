#ifndef SORTBYYASC_H
#define SORTBYYASC_H

#include <QtGui>

class SortByYAsc
{
public:
    SortByYAsc();

    bool operator() (const QPoint p1, const QPoint p2)
    {
        const double eps = 1e-10;
        if (abs(p1.y()-p2.y()) < eps)
        {
            return (p1.x() < p2.x());
        }
        return (p1.y() < p2.y());
    }
};

#endif // SORTBYYASC_H
