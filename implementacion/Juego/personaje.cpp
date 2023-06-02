#include "personaje.h"


int Personaje::getVidas() const
{
    return vidas;
}

void Personaje::setVidas(int value)
{
    vidas = value;
}

int Personaje::getPuntaje() const
{
    return puntaje;
}

void Personaje::setPuntaje(int value)
{
    puntaje = value;
}

int Personaje::getNivel() const
{
    return nivel;
}

void Personaje::setNivel(int value)
{
    nivel = value;
}

float Personaje::getVx() const
{
    return vx;
}

void Personaje::setVx(float value)
{
    vx = value;
}

float Personaje::getVy() const
{
    return vy;
}

void Personaje::setVy(float value)
{
    vy = value;
}

float Personaje::getAy() const
{
    return ay;
}

void Personaje::setAy(float value)
{
    ay = value;
}

float Personaje::getPx() const
{
    return px;
}

void Personaje::setPx(float value)
{
    px = value;
}

float Personaje::getPy() const
{
    return py;
}

void Personaje::setPy(float value)
{
    py = value;
}

int Personaje::getLlaves() const
{
    return llaves;
}

void Personaje::setLlaves(int value)
{
    llaves = value;
}

std::string Personaje::getNombre() const
{
    return nombre;
}

void Personaje::setNombre(const std::string &value)
{
    nombre = value;
}

int Personaje::getPuntaje_maximo() const
{
    return puntaje_maximo;
}

void Personaje::setPuntaje_maximo(int value)
{
    puntaje_maximo = value;
}

Personaje::Personaje()
{
    
}

Personaje::Personaje(float _px, float _py, float _vx, float _vy, float _ax,int _vidas,int _nivel, int _puntaje, std::string _nombre,int p_max)
{
    px=_px;
    py=_py;
    vx=_vx;
    vy=_vy;
    ax=_ax;
    vidas=_vidas;
    nivel=_nivel;
    puntaje=_puntaje;
    nombre=_nombre;
    puntaje_maximo=p_max;
    setPos(px,py);
}


void Personaje::advance(int phase)
{
    vx = vx + ax*DT;
    vy = vy + ay*DT;

    px = px + vx*DT + 0.5*ax*DT*DT;
    py = py + vy*DT + 0.5*ay*DT*DT;
    setPos(px,py);
}



QRectF Personaje::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage player("../juego final/barril.png");

    painter->setBrush(player);
    //painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}

