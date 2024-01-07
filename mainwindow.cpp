#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBTNs = {{Qt::Key_0, ui->btnNum0},
                 {Qt::Key_1, ui->btnNum1},
                 {Qt::Key_2, ui->btnNum2},
                 {Qt::Key_3, ui->btnNum3},
                 {Qt::Key_4, ui->btnNum4},
                 {Qt::Key_5, ui->btnNum5},
                 {Qt::Key_6, ui->btnNum6},
                 {Qt::Key_7, ui->btnNum7},
                 {Qt::Key_8, ui->btnNum8},
                 {Qt::Key_9, ui->btnNum9},
                };
    foreach (auto btn, digitBTNs) {
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
    }
//    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumclicked()));
//    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumclicked()));

    connect(ui->jiahao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->jianhao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->chenghao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->chuhao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->daoshu,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->baifenhao,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->genhao,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->pingfang,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->sin,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->cos,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->tan,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if (operands.size() == 2 && opcodes.size() > 0 ) {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands. pop_front();
        //取操作符
        QString op = opcodes.front();
        opcodes. pop_front();
        if (op == "+") {
            result = operand1 + operand2;
        } else if (op == "-") {
            result = operand1 - operand2;
        } else if (op == "×") {
            result = operand1 * operand2;
        } else if (op == "/") {
            result = operand1 / operand2;
        }

        operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("calculation is in progress: opeands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    else{
        ui->statusbar->showMessage(QString("opeands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    return QString::number(result);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand!="")
    {
        double result=operand.toDouble();
        operand="";
        QString op = qobject_cast<QPushButton *>(sender())->text();
        if (op == "%")
            result /= 100.0;
        else if (op == "1/x")
            result = 1 / result;
        else if (op == "x^2")
            result *= result;
        else if (op == "√")
            result = sqrt(result);
        else if(op=="sin"){
            result = std::sin(result*3.141592654/180);
        }
        else if(op=="cos"){
            result = std::cos(result*3.141592654/180);
        }
        else if(op=="tan"){
            result = std::tan(result*3.141592654/180);
        }
        ui->display->setText(QString :: number(result));
    }
}

void MainWindow::btnNumclicked()
{
    QString digit=qobject_cast<QPushButton *>(sender())->text();
    if(digit=="0"&&operand=="0")
        digit="";
    if(digit!="0"&&operand=="0")
        operand="";
    operand+=digit;
    ui->display->setText(operand);
}




void MainWindow::on_xiaoshudian_clicked()
{
    if(!operand.contains("."))
        operand+=qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);

}


void MainWindow::on_shanchu_clicked()
{
    operand=operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_cleanAll_clicked()
{
    operand.clear();
    operands.clear();
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode=qobject_cast<QPushButton *>(sender())->text();
    if(operand!="")
    {
        operands.push_back(operand);
        operand="";

        opcodes.push_back(opcode);
        QString result=calculation();
        ui->display->setText(result);
    }
}

void MainWindow::on_denghao_clicked()
{
    if(operand!="")
    {
        operands.push_back(operand);
        operand="";
    }
    QString result=calculation();
    ui->display->setText(result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnkey,digitBTNs.keys())
    {
        if (event->key() == btnkey)
            digitBTNs[btnkey]->animateClick();
    }
    /*
    if (event->key() == Qt :: Key_0)
        ui->btnNum0->animateClick(100);
    else if (event->key() == Qt :: Key_1)
        ui->btnNum1->animateClick(100);*/
}




void MainWindow::on_zhengfu_clicked()
{
    if (!operand.isEmpty())
    {
        double currentOperand = operand.toDouble();
        currentOperand *= -1;
        operand = QString::number(currentOperand);
        ui->display->setText(operand);
    }
}


void MainWindow::on_qingchu_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_sin_clicked()
{

}


void MainWindow::on_cos_clicked()
{

}


void MainWindow::on_tan_clicked()
{

}


void MainWindow::on_PI_clicked()
{

}

