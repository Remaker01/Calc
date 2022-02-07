#ifndef CALCMAINWINDOW_H
#define CALCMAINWINDOW_H
#include "./ui_mainwindow.h"
#include <QMainWindow>
#include <QPushButton>
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
    string expression;
    bool autoCalculate;
public:
    CalcMainWindow(QWidget *parent = nullptr);
    ~CalcMainWindow();

private slots:
    void on_calcButton_clicked();
    void on_expEdit_textChanged(const QString &arg1);
    void on_autoCalcBox_stateChanged(int newState);
    void on_exitButton_clicked();
    void on_copyButton_clicked();

public slots:
};
#endif // CALCMAINWINDOW_H
