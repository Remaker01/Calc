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
extern bool isOpt(char ch);
extern Biginteger calcExpression(const string &exp);

CalcMainWindow::CalcMainWindow(QWidget *parent): QMainWindow(parent),
            ui(new Ui::MainWindow),autoCalculate(false) {
    ui->setupUi(this);
    ui->autoCalcBox->setTristate(false);
    ui->expEdit->setMaxLength(1<<15);
    registerSlots();
}

void CalcMainWindow::registerSlots() {
    connect(ui->actionExit,&QAction::triggered,this,&CalcMainWindow::on_exitButton_clicked);
    connect(ui->actionCopy,&QAction::triggered,this,&CalcMainWindow::on_copyButton_clicked);
    connect(ui->actionAbout,&QAction::triggered,this,[this]() {
        QMessageBox info(QMessageBox::Information,"关于","简易计算器\n"
                                   "支持大整数运算的计算器\n\n"
                                   "界面框架:Qt5.12\n"
                                   "环境:QT Creator5+CMake3.21+MinGW8.1\n"
                                   "作者邮箱:latexreal@163.com\n"
                                   "版本号:1.0 Beta  1.0.220210");
        info.addButton("确定",QMessageBox::AcceptRole);
        QPushButton *gitButton = info.addButton("访问项目GitHub",QMessageBox::ActionRole);
        connect(gitButton,&QPushButton::clicked,this,&CalcMainWindow::toGithub);
        info.exec();
    });
    connect(ui->actionHelp,&QAction::triggered,this,[]() {
        return QDesktopServices::openUrl(QUrl::fromLocalFile("README.htm"));
    });
}

void CalcMainWindow::appendOpt(const QString &s) {
    int len = expression.length();
#ifndef NDEBUG
    assert(s.length() == 1);
#endif
    if(len > 0) {
        if(expression[len - 1].isDigit()) {
            expression += s;
            ui->expEdit->setText(expression);
        }
        else if(isOpt(expression[len - 1].toLatin1())) {
            expression[len - 1] = s[0];
            ui->expEdit->setText(expression);
        }
    }
}

CalcMainWindow::~CalcMainWindow() {
    delete ui;
}

SLOT_FUNCS
void CalcMainWindow::on_calcButton_clicked() {
    try {
        if(ui->expEdit->text().isEmpty())
            ui->resTextEdit->clear();
        else {
            Biginteger res(calcExpression(expression.toStdString()));
            ui->resTextEdit->document()->setPlainText(res.toString().c_str());
        }
    } catch (NumberFormatException &e) {
        ui->resTextEdit->document()->setPlainText("算式中含有非法字符");
    } catch (std::exception &e) {
        ui->resTextEdit->document()->setPlainText(e.what());
    }
}

void CalcMainWindow::on_expEdit_textChanged(const QString &arg1) {
    expression = arg1;
    if(autoCalculate)  on_calcButton_clicked();
}

void CalcMainWindow::on_autoCalcBox_stateChanged(const int newState){
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
void CalcMainWindow::toGithub() {QDesktopServices::openUrl(QUrl("https://github.com/Remaker01/Calc"));}

void CalcMainWindow::on_pushButton1_clicked() {
    expression += "1";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton2_clicked() {
    expression += "2";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton3_clicked() {
    expression += "3";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton4_clicked() {
    expression += "4";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton5_clicked() {
    expression += "5";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton6_clicked() {
    expression += "6";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton7_clicked() {
    expression += "7";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton8_clicked() {
    expression += "8";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton_9_clicked() {
    expression += "9";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_pushButton0_clicked() {
    expression += "0";
    ui->expEdit->setText(expression);
}
void CalcMainWindow::on_plusButton_clicked()  {appendOpt("+");}
void CalcMainWindow::on_minusButton_clicked() {appendOpt("-");}
void CalcMainWindow::on_mulButton_clicked() {appendOpt("*");}
void CalcMainWindow::on_pushButton_clicked() {appendOpt("/");}

void CalcMainWindow::on_clearButton_clicked() {ui->expEdit->clear();}
