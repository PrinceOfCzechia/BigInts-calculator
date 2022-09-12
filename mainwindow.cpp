#include <iostream>
#include "mainwindow.h"
#include "eval.cpp"
#include <QMessageBox>

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
}

void MainWindow::on_buttonRP_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text().append(")"));
}

void MainWindow::on_clcButton_clicked()
{
    ui->lineEdit->setText("");
}

void MainWindow::on_additionalButton_clicked()
{
    QMessageBox::information(this, "MainWindow", "text");
}


// auxiliary functions for evalButton
void MainWindow::closeBrackets()
{
    QString temp;
    unsigned lb = 0;
    unsigned rb = 0;
    for(QChar c: ui->lineEdit->text())
    {
        if(c=='(') lb++;
        if(c==')') rb++;
    }
    int balance = lb - rb;
    if(balance>0)
    {
        for(int i=0; i<balance; i++)
        {
            temp+=")";
        }
        ui->lineEdit->setText(ui->lineEdit->text()+temp);
    }
    else
    {
        for(int i=0; i>balance; i--)
        {
            temp+="(";
        }
        ui->lineEdit->setText(temp+ui->lineEdit->text());
    }

}

void MainWindow::refreshHistory()
{
    ui->historyLabel->setText(ui->lineEdit->text().append("="));
}

// here comes the calculation itself
void MainWindow::on_evalButton_clicked()
{
    // measures before computing the result
    this->refreshHistory();
    this->closeBrackets();
    try{
        // getting the input from lineEdit, making it work with unary operators
        string input = firstUnary(this->ui->lineEdit->text().toStdString());
        string binaryInput = unaryPrep(input);
        std::cout << binaryInput << std::endl;
        // tokenization
        vector<string> tokens = tokenize(binaryInput);
        for(string s:tokens)
            std::cout<<"token: " << s << std::endl;
        // rearranging tokens to reverse polish (postfix) order
        vector<string> RPN = ::infix2RPN(tokens, opMap);
        for(string s:RPN)
            std::cout << s;
        std::cout<<std::endl;
        // evaluating the RPN tokens
        string result = evalRPN(RPN);
        this->ui->lineEdit->setText(QString::fromStdString(result));
    }
    catch(EvalException &e)
    {
        this->ui->lineEdit->setText(e.what());
    }
    catch(...)
    {
        this->ui->lineEdit->setText("ERROR: unknown error");
    }
}
