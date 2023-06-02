#ifndef OBJETOS_H
#define OBJETOS_H
#include <QGraphicsItem>
#include <QPainter>
#include "proyectiles.h"
#include <math.h>
using namespace std;
#define DT 0.08
#define G 10
#define pi 3.1416
#define rad (2*pi/360)

class objetos : public QGraphicsItem
{
private:
    int tipo;
    float px,py,vx=10,vy;
    proyectiles *bala;
    int cont = 0;
    float theta = 90; // angulo
    float w = sqrt(G/1); //gravedad por logingitud
    float i = 1;
    float pyini,pxini;
public:
    objetos();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    objetos(float _px, float _py, int _tipo);
    void advance(int phase);
    int getTipo() const;
    void setTipo(int value);
    proyectiles * generarbala();
    float getPx() const;
    void setPx(float value);
    float getPy() const;
    void setPy(float value);
    float getVx() const;
    void setVx(float value);
    float getVy() const;
    void setVy(float value);
    int getCont() const;
};

#endif // OBJETOS_H
