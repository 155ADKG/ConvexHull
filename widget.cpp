#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushGen_clicked()
{
    // Check int value
    QString text = ui->lineCount->text();
    bool check_int;
    int value = text.toInt(&check_int);
    if(!check_int){value=0;}

    // Clear points and CH
    points.clear();
    convexHull.clear();

    // Generate points
    Algorithms::generatePoints(points, value, typeGenerate, this->width()-200, this->height()-80);

    ui->canvas->setGenPoints(points);
    ui->canvas->setGenCH(convexHull);

    repaint();
}

void Widget::on_comboTypeGen_currentIndexChanged(int index)
{
    typeGenerate = static_cast<typeGen>(index);
}

void Widget::on_pushAlg_clicked()
{
    convexHull.clear();

    // Call algorithm with timing
    QTime myTimer;
    myTimer.start();

    // Choose current algorithm
    if(typeAlgorithm == QCK){
        convexHull = Algorithms::qhull(points);
    }else if(typeAlgorithm == INC){
        convexHull = Algorithms::incr(points);
    }else if(typeAlgorithm == GRH){
        convexHull = Algorithms::graham(points);
    }else{
        convexHull = Algorithms::jarvis(points);
    }

    // Draw time of algorithms
    ui->label_timing->setText(QString::number(myTimer.elapsed())+" ms");

    // Set CH for class draw
    ui->canvas->setGenCH(convexHull);

    repaint();

}

void Widget::on_comboTypeAlg_currentIndexChanged(int index)
{
    typeAlgorithm = static_cast<typeAlg>(index);
}
