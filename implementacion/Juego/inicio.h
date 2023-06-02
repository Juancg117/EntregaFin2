#ifndef INICIO_H
#define INICIO_H

#include <QMainWindow>
#include "mainwindow.h"
#include <QPushButton>

#include <fstream>
#include <QString>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <QDebug>

namespace Ui {
class Inicio;
}

class Inicio : public QMainWindow
{
    Q_OBJECT

public:
    explicit Inicio(QWidget *parent = nullptr);
    ~Inicio();

    void startgame();
    void abrir();
    void closegame();
    void loadgame();
    void loadclose();
    void newgame();

private slots:
    void on_loadbutton_clicked();
    void on_newbutton_clicked();

private:
    Ui::Inicio *ui;
    MainWindow *juego;
    QTimer *tiempo1;
    int vidas=3,level=1,score=0,puntaje_maximo=0;
    string nombre;
};

#endif // INICIO_H
