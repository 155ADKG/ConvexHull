#ifndef SORTBYYASC_H
#define SORTBYYASC_H

#include <QtGui>

class SortByYAsc
{
public:
    SortByYAsc();

    bool operator() (const QPoint p1, const QPoint p2)
    {
        return p1.x() < p2.x();
    }
};

#endif // SORTBYYASC_H
