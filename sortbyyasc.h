#ifndef SORTBYYASC_H
#define SORTBYYASC_H

#include <QtGui>

class SortByYAsc
{
public:
    SortByYAsc();

    bool operator() (const QPointF &p1, const QPointF &p2){
        return p1.y() < p2.y();
    }
};

#endif // SORTBYYASC_H
