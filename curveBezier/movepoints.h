#ifndef MOVEPOINTS_H
#define MOVEPOINTS_H

#include <QObject>
#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <vector>

class movePoints : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit movePoints(QObject *parent = nullptr);
    ~movePoints();

signals:
    void updateBezierCurve();

public:
    void setText(int number);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsTextItem * text;

};

#endif // MOVEPOINTS_H
