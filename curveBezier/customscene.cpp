#include "customscene.h"

customScene::customScene(QObject *parent)
    :  QGraphicsScene()
{
}

customScene::~customScene()
{

}

void customScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */

    if (points.size() < limitPoints && event->scenePos().x() <= 494 && event->scenePos().x() >= 6 && event->scenePos().y() <= 494 && event->scenePos().y() >= 6)
    {
        points.push_back(new movePoints());

        int size = points.size();
        connect(points[size - 1], SIGNAL(updateBezierCurve()), this, SLOT(update()));

        this->addItem(points[size - 1]);

    //    points = this->addEllipse(QRect(-3,-3,6,6), QPen(Qt::green),  QBrush(Qt::green));
        points[size - 1]->setPos(event->scenePos());
        points[size - 1]->setText(size);

//        qDebug() << points[size - 1]->pos();
//        qDebug() << event->scenePos();

        if (size == limitPoints)
        {
            emit drawBezierCurve();
        }
    }

}

void customScene::update()
{
    if (points.size() == limitPoints)
    {
        for (int i = 0; i < lines.size(); ++i )
        {
           removeItem(lines[i]);
        }
        lines.clear();

        removeItem(path);

        emit updateBezierCurve();

    }
}

void customScene::changeSettingsBezierCurve(int countPoints)
{
    // удаляем прошлую Кривую Безье
    for (int i = 0; i < lines.size(); ++i )
    {
       removeItem(lines[i]); // удаляем линии, соединяющие точки
    }

    for (int i = 0; i < points.size(); ++i )
    {
       removeItem(points[i]); // удаляем точки
    }

    if (points.size() == limitPoints)
    {
        removeItem(path); // удаляем саму кривую
    }


    points.clear();
    lines.clear();
//    lines.resize(countPoints - 1);

    // устанавливаем новый лимит количества точек
    limitPoints = countPoints;
}
