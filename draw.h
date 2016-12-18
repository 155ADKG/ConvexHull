#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include "algorithms.h"

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
    INC   =  2,

    GRH = 3
};

class Draw : public QWidget
{
    Q_OBJECT
private:
    std::vector<QPoint> points;
    std::vector<QPoint> convexHull;
    typeGen typeGenerate;
    typeAlg typeAlgorithm;
    unsigned int countPoints;
    bool pushGen;
    bool pushAlg;
    int time_alg;

public:
    explicit Draw(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    QPoint generatePoint();
    void generatePoints();

    void setTypeGenerate(typeGen typeGenerate_) { typeGenerate = typeGenerate_; }
    void setTypeAlgorithm(typeAlg typeAlgorithm_){ typeAlgorithm = typeAlgorithm_; }
    void setCountPoints(unsigned int countPoints_){ countPoints = countPoints_; }
    void setPushGen(bool pushGen_){ pushGen = pushGen_; }
    void setPushAlg(bool pushAlg_){ pushAlg = pushAlg_; }

    int getTiming(){ return time_alg; }

};

#endif // DRAW_H
