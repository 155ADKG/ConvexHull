#ifndef SORTBYANGLEASC_H
#define SORTBYANGLEASC_H
#include "algorithms.h"

class SortByAngleAsc
{
private:
    QPoint s;
    QPoint e;
public:
    SortByAngleAsc(const QPoint &s_, const QPoint &e_){s = s_; e = e_;}


    bool operator() (const QPoint &p1, const QPoint &p2)
    {

        return (Algorithms::getTwoVectorsOrientation(s,p1,s,e) < Algorithms::getTwoVectorsOrientation(s,p2,s,e));

    }
};

#endif // SORTBYANGLEASC_H
