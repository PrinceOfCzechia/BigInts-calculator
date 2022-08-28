#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool canAppendOperator();

private slots:
    // buttons to add characters
    void on_buttonZero_clicked();
    void on_buttonOne_clicked();
    void on_buttonTwo_clicked();
    void on_buttonThree_clicked();
    void on_buttonFour_clicked();
    void on_buttonFive_clicked();
    void on_buttonSix_clicked();
    void on_buttonSeven_clicked();
    void on_buttonEight_clicked();
    void on_buttonNine_clicked();
    void on_plusButton_clicked();
    void on_minusButton_clicked();
    void on_timesButton_clicked();
    void on_divideButton_clicked();
    void on_powerButton_clicked();
    void on_buttonLP_clicked();
    void on_buttonRP_clicked();

    // clear the line
    void on_clcButton_clicked();

    // evaluate input
    void on_evalButton_clicked();

private:
    Ui::MainWindow *ui;
    // auxiliary functions for input evalutaion
    void closeBrackets();
    void refreshHistory();
    bool isUnaryMinus(char minus);
    QString binarize(QString input);
    QString addTimes(QString ipnut);
    QString infix2RPN(QString input);
};
#endif // MAINWINDOW_H
