#include "mainwindow.h"
#include <iostream>
#include <stack>
#include <vector>

unsigned openBracketCount = 0;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::canAppendOperator()
{
    if(ui->lineEdit->text().endsWith('+')) return false;
    if(ui->lineEdit->text().endsWith('-')) return false;
    if(ui->lineEdit->text().endsWith('*')) return false;
    if(ui->lineEdit->text().endsWith('/')) return false;
    if(ui->lineEdit->text().endsWith('^')) return false;
    return true;
}

void MainWindow::on_buttonZero_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("0"));
}

void MainWindow::on_buttonOne_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("1"));
}

void MainWindow::on_buttonTwo_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("2"));
}

void MainWindow::on_buttonThree_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("3"));
}

void MainWindow::on_buttonFour_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("4"));
}
void MainWindow::on_buttonFive_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("5"));
}

void MainWindow::on_buttonSix_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("6"));
}

void MainWindow::on_buttonSeven_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("7"));
}

void MainWindow::on_buttonEight_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("8"));
}

void MainWindow::on_buttonNine_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("9"));
}

void MainWindow::on_plusButton_clicked()
{
    if(canAppendOperator())
        ui->lineEdit->setText(ui->lineEdit->text().append("+"));
}

void MainWindow::on_minusButton_clicked()
{
    if(canAppendOperator())
        ui->lineEdit->setText(ui->lineEdit->text().append("-"));
}

void MainWindow::on_timesButton_clicked()
{
    if(canAppendOperator())
        ui->lineEdit->setText(ui->lineEdit->text().append("*"));
}

void MainWindow::on_divideButton_clicked()
{
    if(canAppendOperator())
        ui->lineEdit->setText(ui->lineEdit->text().append("/"));
}

void MainWindow::on_powerButton_clicked()
{
    if(canAppendOperator())
        ui->lineEdit->setText(ui->lineEdit->text().append("^"));
}

void MainWindow::on_buttonLP_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append("("));
    openBracketCount++;
}

void MainWindow::on_buttonRP_clicked()
{
    if(openBracketCount!=0)
    {
        ui->lineEdit->setText(ui->lineEdit->text().append(")"));
        openBracketCount--;
    }
}

void MainWindow::on_clcButton_clicked()
{
    ui->lineEdit->setText("");
}


// auxiliary functions for evalButton
void MainWindow::closeBrackets()
{
    for(unsigned i=openBracketCount; i>0; i--)
    {
        ui->lineEdit->setText(ui->lineEdit->text().append(")"));
    }
    openBracketCount=0;
}

void MainWindow::refreshHistory()
{
    ui->historyLabel->setText(ui->lineEdit->text().append("="));
}

QString MainWindow::binarize(QString input)
{
    QString output;
    //
    // add zeros so that unary minuses become binary
    // without chnaging the expression's value
    //
    return output;
}

// transforming the user-friendly infix string
// into a computer-friendly postfix (RPN) string
QString MainWindow::infix2RPN(QString input)
{
    QString output;
    // define stack
    // shunting yard algorithm
    return output;
}

// here comes the calculation itself
void MainWindow::on_evalButton_clicked()
{
    this->closeBrackets();
    this->refreshHistory();
}
