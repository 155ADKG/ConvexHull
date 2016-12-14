#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>

typedef QVector<QPointF> vecQPoint;

enum typeGen
{
    RAND   =  0,
    GRID  =   1,
    CLUS   =  2
};

enum typeAlg
{
    JAR   =  0,
    QCK  =   1,
    INC   =  2
};

class Algorithms
{
public:
    Algorithms(){};
    static double getTwoVectorsOrientation(const QPointF &p1, const QPointF &p2, const QPointF &p3, const QPointF &p4);
    static double getPointLineDistance(const QPointF &p, const QPointF &p1, const QPointF &p2);
    static int getPointLinePosition(const QPointF &p, const QPointF &p1, const QPointF &p2);

    static vecQPoint jarvisScan(vecQPoint points);
    static void qHull(const vecQPoint &points);
    static vecQPoint incr(vecQPoint points);

private:
    static void qh(const int s, const int e, const vecQPoint points, vecQPoint &ch);
};

#endif // ALGORITHMS_H
