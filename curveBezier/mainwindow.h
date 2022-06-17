#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "customscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    void paintEvent(QPaintEvent *) override;

signals:
    void changeTypeBezierCurve(int);

public slots:
    void update();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    void linearCurve();
    void quadCurve();
    void cubicCurve();

private:

    Ui::MainWindow *ui;
    customScene *scene;
    QPainterPath path;

};
#endif // MAINWINDOW_H
