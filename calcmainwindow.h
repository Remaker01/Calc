#ifndef CALCMAINWINDOW_H
#define CALCMAINWINDOW_H
#include "./ui_mainwindow.h"
#include <QMainWindow>
#include <QFile>
#include <QDesktopServices>
#include <QKeyEvent>
#include <QPalette>
#include <include/Bigint.h>
namespace Ui {class MainWindow;}
/**
 * @brief The CalcMainWindow class<br>
 * 计算器主窗口
 */
class CalcMainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QString expression;
    bool autoCalculate;
    void registerSlots();
    void appendOpt(const QString &s);
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    explicit CalcMainWindow(QWidget *parent = nullptr);
    ~CalcMainWindow();

private slots:
    void on_calcButton_clicked();
    void on_expEdit_textChanged(const QString &arg1);
    void on_autoCalcBox_stateChanged(const int newState);
    void on_exitButton_clicked();
    void on_copyButton_clicked();
    void toGithub();

    void on_pushButton1_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton4_clicked();
    void on_pushButton5_clicked();
    void on_pushButton6_clicked();
    void on_pushButton7_clicked();
    void on_pushButton8_clicked();
    void on_pushButton9_clicked();
    void on_pushButton0_clicked();

    void on_plusButton_clicked();
    void on_minusButton_clicked();
    void on_mulButton_clicked();
    void on_divButton_clicked();
    void on_clearButton_clicked();

public slots:
};
#endif // CALCMAINWINDOW_H
