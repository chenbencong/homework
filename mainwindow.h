#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString operand;
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int, QPushButton *>digitBTNs;
    QString calculation(bool *ok=NULL);

private slots:
    void btnNumclicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();

    void on_xiaoshudian_clicked();

    void on_shanchu_clicked();

    void on_cleanAll_clicked();

    void on_denghao_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

    void on_zhengfu_clicked();

    void on_qingchu_clicked();

    void on_sin_clicked();

    void on_cos_clicked();

    void on_tan_clicked();

    void on_PI_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
