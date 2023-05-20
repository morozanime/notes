#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QList>
#include <QString>
#include <QRegularExpression>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
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

    ui->lineEditPrec0->setText(QString::number(prec0));
    ui->checkBox->setChecked(modeHex);
    ui_update();
    calculate();
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

void MainWindow::calculate(void) {
    QStringList s = ui->plainTextEdit->toPlainText().split(QRegularExpression("[\r\n]"), Qt::SplitBehaviorFlags::KeepEmptyParts);
    QStringList results;
    ClearVariables();
    ClearFunctions();
    for(int i = 0; i < s.length(); i++) {
        if(s.value(i).startsWith("//")) {
            results.append(s.value(i));
//            ui->plainTextEdit_2->appendPlainText(s.value(i));
            continue;
        }
        QString varName = "";
        QString funcName = "";
        QString oLine = "";
        QString resultNumber;
        QString expr = s.value(i).replace(QRegularExpression("[ \t]+"), "");
        if(!expr.isEmpty()){
            QRegularExpression rx = QRegularExpression("^([a-zA-Z_]+[a-zA-Z0-9_]*)=(.*)$");
            QRegularExpression rxF = QRegularExpression("^([a-zA-Z_]+[a-zA-Z0-9_]*):=(.*)$");
            QRegularExpressionMatch rxm = rx.match(expr);
            QRegularExpressionMatch rxFm = rxF.match(expr);
            if(rxm.hasMatch()) {
                varName = rxm.captured(1);
                expr = rxm.captured(2);
            } else if(rxFm.hasMatch()) {
                funcName = rxFm.captured(1);
                expr = rxFm.captured(2);
                SetFunction(funcName, expr);
            }
            std::complex<long double> res;
            if(funcName.length() > 0) {
                oLine = "function " + funcName + " = " + expr;
            } else {
                if(ldcalc(&res, expr.toLocal8Bit().data())) {
                    std::stringstream ss;
                    if(varName.length() > 0) {
                        SetVariable(varName.toLatin1().data(), res);
                    }
                    if(fabsl(res.imag()) > 0.0L) {
                        ss << "(";
                        if(modeHex) {
                            ss << "0x" << QString("%1").arg((uint64_t)res.real(), prec0, 16, QChar('0')).toStdString();
                        } else {
                            ss << std::setprecision(prec0 + 1) << res.real();
                        }
                        if(res.imag() >= 0)
                            ss << "+";
                        if(modeHex) {
                            ss << " 0x" << QString("%1").arg((uint64_t)res.imag(), prec0, 16, QChar('0')).toStdString();
                        } else {
                            ss << std::setprecision(prec0 + 1) << res.imag();
                        }
                        ss << "j)";
                    } else {
                        if(modeHex){
                            ss << "0x" << QString("%1").arg((uint64_t)res.real(), prec0, 16, QChar('0')).toStdString();
                        } else {
                            ss << std::setprecision(prec0 + 1) << res.real();
                        }
                    }
                    if(!varName.isEmpty()) {
                        oLine = varName + " = ";
                    } else if(funcName.length() > 0) {
                        oLine = varName + " := ";
                    }
                    resultNumber = QString::fromStdString(ss.str());
                    oLine += resultNumber;
                } else {
                    oLine = "?";
                }
            }
        }
        results.append(oLine);
    }
    ui->plainTextEdit_2->clear();
    for(int i = 0; i < results.length(); i++) {
        ui->plainTextEdit_2->appendPlainText(results.value(i));
    }
}


void MainWindow::on_plainTextEdit_textChanged()
{
    calculate();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    modeHex = (ui->checkBox->checkState() == Qt::Checked);
    ui_update();
    calculate();
}


void MainWindow::on_lineEditPrec0_editingFinished()
{
    prec0 = ui->lineEditPrec0->text().toInt();
    calculate();
}

void MainWindow::ui_update(void) {
}
