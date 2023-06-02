#ifndef COLECCIONABLES_H
#define COLECCIONABLES_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class Coleccionables : public QGraphicsItem
{
private:
    int tipo;
    float px,py;


public:
    Coleccionables();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Coleccionables(float _px, float _py, int _tipo);
    int getTipo() const;
};

#endif // COLECCIONABLES_H
