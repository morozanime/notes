#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <complex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEdit_textChanged();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void eval(QString expr);
    QFile * page = nullptr;
};

class Range {
public:
    void reset(){
        from = 0;
        step = 0;
        to = 0;
    }
    bool init(long double from, long double step, long double to){
        if((to>from && step>0) || (to<from && step < 0)){
            this->from = from;
            this->step = from;
            this->to = from;
            return true;
        } else {
            return false;
        }
    }
    long double next(void){
        long double r = from;
        from += step;
        return r;
    }
    bool isEnd(void){
        return (step>0)?(from>=to):(from<=to);
    }
private:
    long double from = 0;
    long double step = 0;
    long double to = 0;

};

#endif // MAINWINDOW_H
