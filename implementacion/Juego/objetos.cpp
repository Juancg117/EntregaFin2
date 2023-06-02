#include "objetos.h"


int objetos::getTipo() const
{
    return tipo;
}

void objetos::setTipo(int value)
{
    tipo = value;
}

float objetos::getPx() const
{
    return px;
}

void objetos::setPx(float value)
{
    px = value;
}

float objetos::getPy() const
{
    return py;
}

void objetos::setPy(float value)
{
    py = value;
}

float objetos::getVx() const
{
    return vx;
}

void objetos::setVx(float value)
{
    vx = value;
}

float objetos::getVy() const
{
    return vy;
}

void objetos::setVy(float value)
{
    vy = value;
}

int objetos::getCont() const
{
    return cont;
}

objetos::objetos()
{

}

proyectiles * objetos::generarbala(){

    bala = new proyectiles(px,py,50,-100,3);
    return bala;
}

QRectF objetos::boundingRect() const
{
    return QRectF(0,0,40,40);
}

objetos::objetos(float _px, float _py, int _tipo)
{
        px=_px;
        py=_py;
        tipo = _tipo;
        pxini= _px;
        pyini=_py;
        setPos(px,py);

}

void objetos::advance(int phase)
{
    if(tipo==5)
    {
        if(cont==150){
            vx=-vx;
            cont=0;
        }

        else{
            px = px + vx*DT;
            cont++;
            setPos(px,py);
        }
    }

    else if(tipo==49){

        if(cont==20){
            i = i + DT;
            float theta0 = theta * cos(w*i);
            px =pxini + 90 * sin(theta0*rad);
            py =pyini + 90 * cos(theta0*rad);
            setPos(px,py);
            cont=0;
        }

        else{cont++;}

    }

    else if(tipo==6){

        if(cont==10){

            i = i + DT;
            vx=5*cos(i);
            vy=5*sin(i);
            px =px + 5*cos(i);
            py =py + 5*sin(i);
            setPos(px,py);
            cont =0;

        }

        else{cont++;}

    }
}


void objetos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect j(0,0,40,40);
    QImage puas("../juego final/puas.png");
    QImage bloque("../juego final/bloque.png");
    QImage arma("../juego final/acofre.png");
    QImage doorc("../juego final/doorc.png");
    QImage pend("../juego final/pendulo.png");
    QImage stair("../juego final/stair.png");


    if (tipo == 8){
       painter->drawImage(j,arma);
   }else if(tipo == 1 || tipo==5 || tipo==6){
       painter->drawImage(j,bloque);
   }else if(tipo == 2){
       painter->drawImage(j,stair);
   }else if(tipo == 3 ){
       painter->drawImage(j,puas);
   }else if(tipo == 49){
        painter->drawImage(j,pend);
    }else if(tipo == 7){
        painter->drawImage(j,doorc);
    }

}
