#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <list>
#include <fstream>
#include <string>
#include <QMediaPlayer>

#include "objetos.h"
#include "proyectiles.h"
#include "personaje.h"
#include "coleccionables.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(QWidget *parent,int,int,int,string,int);
    ~MainWindow();

    void onUpdate();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void onFire();
    void obtener_nivel(int);
    void pause();
    void crearmundo(int,int,int,string,int);
    void gameover();
    void reinicio();
    void gamefinish();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene,*scene2;
    list<objetos *> muros;
    Personaje *pj1;
    Personaje *pj2;
    QTimer *tiempo;
    proyectiles *bala;
    list<objetos *> cannon;
    int nivel [30][40]={{0}};
    list<proyectiles *> ammo;
    list<proyectiles *> copyammo;
    QMediaPlayer *player;
    int conti = 0;
    Coleccionables *llave;
    list<Coleccionables *> botin;
    list<Coleccionables *> copybotin;



    void Menu();
};
#endif // MAINWINDOW_H
