#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <string>

#define DT 0.08

class Personaje : public QGraphicsItem
{
private:
    int vidas;
    int puntaje;
    int puntaje_maximo;
    float px,py,vx,vy,ax;
    float ay = 10;
    int nivel;
    int llaves = 0;
    int medallones;
    std::string nombre;

public:
    Personaje();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Personaje(float _px, float _py, float _vx, float _vy, float _ax,int _vidas, int _nivel, int _puntaje, std::string,int);
    void advance(int phase);
    int getVidas() const;
    void setVidas(int value);
    int getPuntaje() const;
    void setPuntaje(int value);
    int getNivel() const;
    void setNivel(int value);
    float getVx() const;
    void setVx(float value);
    float getVy() const;
    void setVy(float value);
    float getAy() const;
    void setAy(float value);
    float getPx() const;
    void setPx(float value);
    float getPy() const;
    void setPy(float value);
    int getLlaves() const;
    void setLlaves(int value);
    std::string getNombre() const;
    void setNombre(const std::string &value);
    int getPuntaje_maximo() const;
    void setPuntaje_maximo(int value);
};


#endif // PERSONAJE_H
