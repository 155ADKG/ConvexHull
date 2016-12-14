#ifndef DRAW_H
#define DRAW_H

#include <QWidget>
#include "algorithms.h"

class Draw : public QWidget
{
    Q_OBJECT
private:
    vecQPoint points;
    vecQPoint convexHull;
    typeGen typeGenerate;
    typeAlg typeAlgorithm;
    unsigned int countPoints;
    bool pushGen;

public:
    explicit Draw(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    QPointF generatePoint();
    void generatePoints();

    void setTypeGenerate(typeGen typeGenerate_) { typeGenerate = typeGenerate_; }
    void setTypeAlgorithm(typeAlg typeAlgorithm_){ typeAlgorithm = typeAlgorithm_; }
    void setCountPoints(unsigned int countPoints_){ countPoints = countPoints_; }
    void setPushGen(bool pushGen_){ pushGen = pushGen_; }


};

#endif // DRAW_H
