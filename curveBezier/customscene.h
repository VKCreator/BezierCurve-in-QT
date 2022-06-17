#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include "movepoints.h"

class customScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit customScene(QObject *parent = 0);
    ~customScene();

signals:
    void drawBezierCurve();
    void updateBezierCurve();

private:
     void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void update();
    void changeSettingsBezierCurve(int);

public:
     std::vector<movePoints*> points; // вектор точек
     std::vector<QGraphicsLineItem*> lines; // вектор линий
     QGraphicsPathItem* path; // контейнер для рисования
     int limitPoints = 2;

};
#endif // CUSTOMSCENE_H
