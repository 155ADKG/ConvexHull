#ifndef REMOVEDUPLICATEPOINTS_H
#define REMOVEDUPLICATEPOINTS_H
#include <QtGui>

class RemoveDuplicatePoints
{
public:
    RemoveDuplicatePoints();

    bool operator() (const QPoint &p1, const QPoint &p2)
    {

        if (p1.x()==p2.x() && p1.y()==p2.y())
        {
            return true;
        }
        return false;

    }
};

#endif // REMOVEDUPLICATEPOINTS_H
