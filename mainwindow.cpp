#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QList>
#include <QString>
#include <QRegularExpression>
#include <iostream>
#include <sstream>
#include "ccalc/ldcalc.h"

#include "ccalc/num.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    page = new QFile("notes.txt");
    if(page->open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->plainTextEdit->setPlainText(page->readAll());
        page->close();
    }
}

MainWindow::~MainWindow()
{
    page = new QFile("notes.txt");
    if(page->open(QIODevice::WriteOnly|QIODevice::Text)){
        page->write(ui->plainTextEdit->toPlainText().toLocal8Bit());
        page->close();
    }
    delete ui;
}

void MainWindow::on_plainTextEdit_textChanged()
{
    QStringList s = ui->plainTextEdit->toPlainText().split(QRegularExpression("[\r\n]"),Qt::SplitBehaviorFlags::KeepEmptyParts);
//    QList<Range> ranges;
    ui->plainTextEdit_2->clear();
    ClearVariables();
    ClearFunctions();
    for(int i = 0; i < s.length(); i++){
        QString expr = s[i].replace(QRegularExpression("[ \t]+"), "");
        QString varName = "";
        QString funcName = "";
        QString oLine = "";
        if(!expr.isEmpty()){
            QRegularExpression rx = QRegularExpression("^([a-zA-Z_]+[a-zA-Z0-9_]*)=(.*)$");
            QRegularExpression rxF = QRegularExpression("^([a-zA-Z_]+[a-zA-Z0-9_]*):=(.*)$");
            QRegularExpressionMatch rxm = rx.match(expr);
            QRegularExpressionMatch rxFm = rxF.match(expr);
            if(rxm.hasMatch()){
                varName = rxm.captured(1);
                expr = rxm.captured(2);
            }else if(rxFm.hasMatch()){
                funcName = rxFm.captured(1);
                expr = rxFm.captured(2);
                SetFunction(funcName, expr);
            }
            std::complex<long double> res;
            if(funcName.length() > 0){
                oLine = "function " + funcName + " = " + expr;
            }else if(ldcalc(&res, expr.toLocal8Bit().data())) {
                std::stringstream ss;
                if(varName.length() > 0) {
                    SetVariable(varName.toLatin1().data(), res);
                    ss << varName.toStdString() << " = ";
                } else if(funcName.length() > 0) {
                    ss << funcName.toStdString() << " := ";
                }
                if(fabsl(res.imag()) > 0.0L) {
                    ss << "(";
                    if(ui->checkBox->isChecked()){
                        ss << "0x" << QString("%1").arg((uint64_t)res.real(),0,16).toStdString();
                    } else {
                        ss << res.real();
                    }
                    if(res.imag() >= 0)
                        ss << "+";
                    if(ui->checkBox->isChecked()){
                        ss << "0x" << QString("%1").arg((uint64_t)res.imag(),0,16).toStdString();
                    } else {
                        ss << res.imag();
                    }
                    ss << "j)";
                } else {
                    if(ui->checkBox->isChecked()){
                        ss << "0x" << QString("%1").arg((uint64_t)res.real(),0,16).toStdString();
                    } else {
                        ss << res.real();
                    }
                }
                oLine = QString::fromStdString(ss.str());
            } else {
                ui->plainTextEdit_2->appendPlainText("?");
                break;
            }
        }
        ui->plainTextEdit_2->appendPlainText(oLine);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    on_plainTextEdit_textChanged();
}

