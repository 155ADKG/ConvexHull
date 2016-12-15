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
        if(check_int)
            ui->canvas->setCountPoints(value);
        // TODO: else QMessageError
        else
            ui->canvas->setCountPoints(0);

        // Set pushGen clicked
        ui->canvas->setPushGen(true);

        repaint();
}

void Widget::on_comboTypeGen_currentIndexChanged(int index)
{
    typeGen idx = static_cast<typeGen>(index);
    ui->canvas->setTypeGenerate(idx);
}

void Widget::on_pushAlg_clicked()
{
    // Set pushGen clicked
    ui->canvas->setPushAlg(true);

    repaint();
}

void Widget::on_comboTypeAlg_currentIndexChanged(int index)
{
    typeAlg type = static_cast<typeAlg>(index);
    ui->canvas->setTypeAlgorithm(type);
}
