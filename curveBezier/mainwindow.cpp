#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // установим пользовательский интерфейс

    this->setWindowTitle("Bezier Curve"); // установим название приложения
    this->resize(700,700);   // устанавливаем размеры окна приложения
    this->setFixedSize(700,700); // фиксируем

    scene = new customScene(this);   // инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов

    ui->graphicsView->resize(600,600);  // устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // устанавливаем графическую сцену в graphicsView

    scene->setSceneRect(0,0,500,500); // устанавливаем размер сцены
    scene->addRect(QRect(0,0,500,500)); // на сцену добавим прямоугольник, чтобы видеть границы сцены

    connect(scene, SIGNAL(drawBezierCurve()), this, SLOT(update()));
    connect(scene, SIGNAL(updateBezierCurve()), this, SLOT(update()));

    connect(this, SIGNAL(changeTypeBezierCurve(int)), scene, SLOT(changeSettingsBezierCurve(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::linearCurve()
{
    QPointF pTemp;

    for (double t = 0; t < 1; t += 0.01)
    {
        pTemp = (1-t) * scene->points[0]->pos() + t * scene->points[1]->pos();
        path.lineTo(pTemp);
    }
}

void MainWindow::quadCurve()
{
    QPointF pTemp;

    for (double t = 0; t < 1; t+=0.01)
    {
        pTemp = pow((1-t),2)*scene->points[0]->pos() + 2 * (1 - t) * t * scene->points[1]->pos() + t * t * scene->points[2]->pos();
        path.lineTo(pTemp);
    }
}

void MainWindow::cubicCurve()
{
    QPointF pTemp;

    for (double t = 0; t < 1; t+=0.01)
    {
        pTemp = pow((1-t),3)*scene->points[0]->pos() + 3 * t * pow((1-t),2)*scene->points[1]->pos() +  3 * t * t * pow((1-t),1)*scene->points[2]->pos() + pow(t,3)*scene->points[3]->pos();
        path.lineTo(pTemp);
    }
}

void MainWindow::update()
{

    for (int i = 0; i < scene->limitPoints - 1; ++i)
    {
        scene->lines.push_back(scene->addLine(QLine(scene->points[i]->pos().x(),scene->points[i]->pos().y(),scene->points[i + 1]->pos().x(), scene->points[i + 1]->pos().y())));
        scene->lines[i]->setPen(QPen(Qt::red));
    }

    // очистим контейнер
    path.clear();

    path.moveTo(scene->points[0]->pos());

    switch (ui->comboBox->currentIndex())
    {
        case 0:
            linearCurve();
            break;
        case 1:
            quadCurve();
            break;
        case 2:
            cubicCurve();
    }

    scene->path = scene->addPath(path);

//        painter->end();

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int countPoints = 0;

    switch (index)
    {
        case 0:
            countPoints = 2;
            break;
        case 1:
            countPoints = 3;
            break;
        case 2:
            countPoints = 4;
    }

    emit changeTypeBezierCurve(countPoints);
}

