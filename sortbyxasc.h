#ifndef SORTBYXASC_H
#define SORTBYXASC_H

#include <QtGui>

class SortByXAsc
{
public:
    SortByXAsc();

    bool operator() (const QPoint &p1, const QPoint &p2)
    {
        const double eps = 1e-10;
        if (abs(p1.x()-p2.x()) < eps)
        {
            return (p1.y() < p2.y());
        }
        return (p1.x() < p2.x());

    }
};

#endif // SORTBYXASC_H
