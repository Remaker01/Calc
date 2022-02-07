#include "calcMainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QClipboard>
#ifndef NDEBUG
#include <QDebug>
#endif
#ifndef SLOT_FUNCS
#define SLOT_FUNCS
#endif
extern Biginteger calcExpression(const string &exp);
CalcMainWindow::CalcMainWindow(QWidget *parent): QMainWindow(parent),
            ui(new Ui::MainWindow),autoCalculate(false) {
    ui->setupUi(this);
    ui->autoCalcBox->setTristate(false);
    connect(ui->actionExit,&QAction::triggered,this,&CalcMainWindow::on_exitButton_clicked);
    connect(ui->actionCopy,&QAction::triggered,this,&CalcMainWindow::on_copyButton_clicked);
    connect(ui->actionAbout,&QAction::triggered,this,[this]() {
        QMessageBox::information(this,"关于","简易计算器\n"
                                           "支持大整数运算的计算器\n\n"
                                           "界面框架:Qt5.12\n"
                                           "环境:QT Creator5+CMake3.21+MinGW8.1\n"
                                           "作者邮箱:latexreal@163.com\n"
                                           "版本号1.0 Alpha  1.0.220207");
    });
}

CalcMainWindow::~CalcMainWindow() {
    delete ui;
}

SLOT_FUNCS
void CalcMainWindow::on_calcButton_clicked() {
    try {
        Biginteger res(calcExpression(expression));
        ui->resTextEdit->document()->setPlainText(res.toString().c_str());
    } catch (std::exception &e) {
        ui->resTextEdit->document()->setPlainText(e.what());
    }
}

void CalcMainWindow::on_expEdit_textChanged(const QString &arg1) {
    expression = arg1.toUtf8().data();
    if(autoCalculate)  on_calcButton_clicked();
}

void CalcMainWindow::on_autoCalcBox_stateChanged(int newState){
    if(newState == Qt::Checked)
        autoCalculate = true;
    else
        autoCalculate = false;
}

void CalcMainWindow::on_exitButton_clicked() {
    QMessageBox box(QMessageBox::Question,"退出确认","确认退出?");
    QPushButton *Yes = box.addButton("是",QMessageBox::AcceptRole);
    box.addButton("否",QMessageBox::RejectRole);
    connect(Yes,&QPushButton::clicked,this,&QMainWindow::close);
    box.exec();
}


void CalcMainWindow::on_copyButton_clicked() {
    QString source = ui->resTextEdit->toPlainText();
    if(source.length() > 0&&source[0].isDigit()) {
        QClipboard *board = QApplication::clipboard();
        board->setText(source);
        QMessageBox::information(this,"信息","已复制");
    }
    else {
        QMessageBox::warning(this,"信息","复制失败");
    }
}
