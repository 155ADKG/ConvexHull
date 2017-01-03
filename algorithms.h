#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QtGui>
#include "sortbyxasc.h"
#include "sortbyyasc.h"
#include "sortdouble.h"
#include "removeduplicatepoints.h"
#include "customtypes.h"



class Algorithms
{

private:
    typeAlg typeAlgorithm;
    void setTypeAlgorithm(typeAlg typeAlgorithm_){ typeAlgorithm = typeAlgorithm_; }

public:
    Algorithms(){};

    static std::vector<QPoint> jarvis(std::vector<QPoint> points);

    static double getTwoVectorsOrientation(const QPoint &p1, const QPoint &p2, const QPoint &p3, const QPoint &p4);

    static double getPointLineDistance(const QPoint &p, const QPoint &p1, const QPoint &p2);

    static std::vector<QPoint> qhull(std::vector<QPoint> points);

    static int getPointLinePosition(const QPoint &p, const QPoint &p1, const QPoint &p2);

    static std::vector<QPoint> incr(std::vector<QPoint> &points);

    static std::vector<QPoint> graham(std::vector<QPoint> &points);

    static void generatePoints(std::vector<QPoint> &points, int countPoints, typeGen typeGenerate, const int win_w, const int win_h);

private:
    static void qh(const int s, const int e, const std::vector<QPoint> points, std::vector<QPoint> &ch);
    static QPoint generatePoint();

};

#endif // ALGORITHMS_H
