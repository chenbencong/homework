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
    connect(ui->PI, SIGNAL(clicked()), this, SLOT(btnNumclicked()));

    connect(ui->jiahao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->jianhao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->chenghao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->chuhao,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->XY,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->mod,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->daoshu,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->baifenhao,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->genhao,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->pingfang,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->sin,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->cos,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->tan,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->ln,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->log,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->TenX,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->Abs,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->Fac,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));



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
        }else if(op=="x^y"){
            result = qPow(operand1, operand2);
        }else if(op=="mod"){
            result = fmod(operand1,operand2);
        }
        if(result!=0)
        operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("calculation is in progress: opeands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    else{
        ui->statusbar->showMessage(QString("opeands is %1,opcodes is %2").arg(operands.size()).arg(opcodes.size()));
    }

    if(operands.size()==1&&opcodes.size()==2){
        QString opcode = opcodes.front();
        double operand = operands.front().toDouble();
        operands.pop_front();
        opcodes. pop_front();
        if(opcode=="-"){
        result-=operand;
        }else if(opcode=="+"){
        result+=operand;
        }
        operands.push_back(QString::number(result));
    }

    return QString::number(result);
}

void MainWindow::btnUnaryOperatorClicked()
{
    double result;
    if(operands.size() == 1||operand!="")
    {
        QString text=ui->display->text();
        if(text==""){
            result = operands.front().toDouble();
            operands.pop_front();
        }else{
            result = text.toDouble();
        }
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
            result = qSin(qDegreesToRadians(result));
        }
        else if(op=="cos"){
            if (result == 90.0) {
                result=0;
            }else
                result = qCos(qDegreesToRadians(result));
        }
        else if(op=="tan"){
            result = qTan(qDegreesToRadians(result));
        }
        else if(op=="ln"){
            result = qLn(result);
        }
        else if(op=="log"){
            result = qLn(result) / qLn(10);
        }
        else if(op=="10^x"){
            result = qPow(10, result);
        }
        else if(op=="|x|"){
            if(result<0)
                result=-result;
        }
        else if(op=="n!"){
            int value=1;
            for (int i = 1; i <= result; i++) {
                value *= i;
            }
            result=value;
        }
        operands.push_back(QString::number(result));
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
    if(digit=="PI"){
        digit="";
        operand="3.1415926";
    }

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
    opcode.clear();
    opcodes.clear();
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode=qobject_cast<QPushButton *>(sender())->text();
    if(operand!="")
    {
        operands.push_back(operand);
        operand="";
    }
    opcodes.push_back(opcode);
    ui->display->setText(opcode);
    QString result=calculation();
    ui->display->setText(result);

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
    double currentOperand = ui->display->text().toDouble();
    currentOperand *= -1;
    operand = QString::number(currentOperand);
    ui->display->setText(operand);
}


void MainWindow::on_qingchu_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


