#include "movepoints.h"

movePoints::movePoints(QObject *parent)
    : QObject{parent}, QGraphicsItem()
{
    // нумерация точки
    text = new QGraphicsTextItem(this);

}

movePoints::~movePoints()
{

}

QRectF movePoints::boundingRect() const
{
    return QRectF (-5,-5,10,10);
}

void movePoints::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawEllipse(-5,-5,10,10);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void movePoints::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    if (event->scenePos().x() <= 494 && event->scenePos().x() >= 6 && event->scenePos().y() <= 494 && event->scenePos().y() >= 6)
    {
        this->setPos(mapToScene(event->pos()));
        emit updateBezierCurve(); // испускаем сигнал, означающий изменение положения точки
    }
}

void movePoints::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void movePoints::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

void movePoints::setText(int number)
{
    text->setPlainText(QString::number(number));
}
