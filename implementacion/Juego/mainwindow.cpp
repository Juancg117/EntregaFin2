#include "mainwindow.h"
#include "ui_mainwindow.h"
int i=0,f=0,f2=0,i2=0;
int inix,iniy;
int v=0,a,dis = 0,tim=0;
bool multi=0;
bool ps = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){}


MainWindow::MainWindow(QWidget *parent,int vidas,int level ,int score, string name, int p_max)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap fondo("../juego final/background4b.png");
    fondo.scaled(500,500);
    ui->graphicsView->setBackgroundBrush(fondo);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,0,0);

    ui->graphicsView->scale(0.5,0.5);

    tiempo = new QTimer();
    tiempo->start(5);

//    player = new QMediaPlayer;
//    // ...
//    player->setMedia(QUrl::fromLocalFile("../juego final/mario.mp3"));
//    player->setVolume(25);
//    player->play();

    connect(tiempo, &QTimer::timeout, this, &MainWindow::onUpdate);
    connect(tiempo, &QTimer::timeout, this, &MainWindow::onFire);
    connect(ui->Back_Menu,&QPushButton::clicked,this,&MainWindow::Menu);
    connect(ui->pause,&QPushButton::clicked,this,&MainWindow::pause);
    connect(ui->reset,&QPushButton::clicked,this,&MainWindow::reinicio);



    crearmundo(vidas,level,score,name,p_max);


    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->centerOn(pj1);
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::onUpdate(){
    scene->advance();
    if(pj1->getPx()==800)
    {
        scene->setSceneRect(800,0,0,0);
        ui->graphicsView->setScene(scene);
    }

    v=v+1;

    if(v==50)
    {
        tim++;
        ui->lcdNumber_3->display(tim);
        v=0;
    }

    ui->Lvidas->display(pj1->getVidas());
    ui->lcdNumber_2->display(pj1->getPuntaje());
    ui->lcdNumber_4->display(pj1->getPuntaje_maximo());



//========================= colosiones Jugador 1============================================================================================

    QList<QGraphicsItem *> colisiones = scene->collidingItems(pj1); //bloques
    if(!colisiones.isEmpty())
    {
        objetos *muros5 = dynamic_cast<objetos *>(colisiones[0]);
        if(muros5){
            for(int i=0;i<colisiones.size();i++)
            {
                objetos *muros3 = dynamic_cast<objetos *>(colisiones[i]);
                if(!muros3){
                    continue;
                }
                if( (muros3->getTipo()==3 || muros3->getTipo()==49) && pj1->getVidas()>=0)
                {
                    pj1->setPx(inix);
                    pj1->setPy(iniy);
                    pj1->setVidas(pj1->getVidas()-1);
                    qDebug()<<"Pinchos"<<pj1->getVidas();
                if(pj1->getVidas()==0){scene->removeItem(pj1);scene->removeItem(pj2);gameover();}
                break;
                }

                else if(muros3->getTipo()==2)
                {
                    pj1->setAy(0);
                    pj1->setVx(0);
                }

                else if(muros3->getTipo()==7){
                    if( (pj1->getNivel()==1 && pj1->getLlaves()==2) || (pj1->getNivel()==2 && pj1->getLlaves()==3) || (pj1->getNivel()==3 && pj1->getLlaves()==5) )
                    {
                       if(pj1->getNivel()==3){

                            pj1->setPuntaje(pj1->getPuntaje()+2000-(tim*5)+(100*pj1->getVidas()));
                            if(pj1->getPuntaje()>pj1->getPuntaje_maximo())
                            {
                                pj1->setPuntaje_maximo(pj1->getPuntaje());
                            }
                            gamefinish();

                       }

                        else{
                            qDebug()<<"pasando de nivel";
                            pj1->setNivel(pj1->getNivel()+1);
                            pj1->setPuntaje(pj1->getPuntaje()+2000-(tim*5)+(100*pj1->getVidas()));

                            cannon.clear();

                            botin.clear();
                            scene->removeItem(pj1);
                            scene->removeItem(pj2);
                            multi=0;

                            ofstream archivo;
                            archivo.open(pj1->getNombre());

                            QString hola = QString::fromStdString(pj1->getNombre());
                            qDebug()<<"nivel: "<< archivo.is_open();

                            archivo<<"/\n";
                            archivo.flush();
                            archivo<<pj1->getNivel()<<"\n";
                            archivo.flush();
                            archivo<<"/\n";
                            archivo.flush();
                            archivo<<pj1->getPuntaje()<<"\n";
                            archivo.flush();
                            archivo<<"/\n";
                            archivo.flush();
                            archivo<<pj1->getVidas()<<"\n";
                            archivo.flush();
                            archivo<<"/\n";
                            archivo.flush();
                            archivo<<pj1->getPuntaje_maximo();
                            archivo.flush();
                            archivo.close();
                            crearmundo(pj1->getVidas(),pj1->getNivel(),pj1->getPuntaje(),pj1->getNombre(),pj1->getPuntaje_maximo());
                        }
                    }
                }

                else if(muros3->getTipo()==1 || muros3->getTipo()==5 || muros3->getTipo()==6)
                {
                                                    //izquierda
                    if( (pj1->getPx()+19>muros3->getPx()+40)&&(pj1->getPx() < (muros3->getPx()+40)) && (pj1->getPy() > muros3->getPy()) )
                    {
                        pj1->setVy(-0.1*pj1->getVy());
                        pj1->setAy(-0.1*pj1->getAy());
                        pj1->setVx(0);
                        pj1->setPx(pj1->getPx()+3);
                    }
                                                    //derecha
                    else if( (pj1->getPx()+19>muros3->getPx())&&(pj1->getPx() < muros3->getPx()) && (pj1->getPy() > muros3->getPy()) )
                    {
                        pj1->setVy(-0.1*pj1->getVy());
                        pj1->setAy(-0.1*pj1->getAy());
                        pj1->setVx(0*pj1->getVx());
                        pj1->setPx(pj1->getPx()-3);
                    }

                    else if( (pj1->getPy() > muros3->getPy()) && (pj1->getPy() < muros3->getPy()+40) && (pj1->getPy()+19 > muros3->getPy()) && pj1->getVy() > 0 )
                    {
                        pj1->setPy(pj1->getPy()+5);
                        pj1->setVx(0);
                    }
                    else
                    {
                        if(muros3->getTipo()==5 || muros3->getTipo()==6)
                        {
                            pj1->setVx(i+muros3->getVx());

                        }

                        if(muros3->getTipo()==6){
                            if(f==1){pj1->setVy(-20);}

                            else{pj1->setVy(muros3->getVy()-4);}
                        }

                        else
                        {
                            pj1->setVy(-0.1*pj1->getVy());
                            pj1->setAy(-0.1*pj1->getAy());
                        }
                    }
                }
            }
        }
    }
    else
    {
        pj1->setAy(10);
    }

//=====================================================================================================================

//======================== colisones Jugador 2=============================================================================================

    if(multi==1)
    {

    QList<QGraphicsItem *> colisiones2 = scene->collidingItems(pj2); //bloques
    if(!colisiones2.isEmpty())
    {
        objetos *muros4 = dynamic_cast<objetos *>(colisiones2[0]);
        if(muros4)
        {
            for(int i=0;i<colisiones2.size();i++)
            {
                objetos *muros2 = dynamic_cast<objetos *>(colisiones2[i]);
                if(!muros2){
                                    continue;
                                }
                if( (muros2->getTipo()==3 || muros2->getTipo()==49) && pj1->getVidas()>=0)
                {
                    pj2->setPx(inix);
                    pj2->setPy(iniy);
                    pj1->setVidas(pj1->getVidas()-1);
                    qDebug()<<"Pinchos"<<pj1->getVidas();
                    if(pj1->getVidas()==0){scene->removeItem(pj1);scene->removeItem(pj2);gameover();}
                    break;
                }

                else if(muros2->getTipo()==2)
                {
                    pj2->setAy(0);
                    pj2->setVx(0);
                }

                else if(muros2->getTipo()==1 || muros2->getTipo()==5 || muros2->getTipo()==6)
                {
                                                    //izquierda
                    if( (pj2->getPx()+19>muros2->getPx()+40)&&(pj2->getPx() < (muros2->getPx()+40)) && (pj2->getPy() > muros2->getPy()) )
                    {
                        pj2->setVy(-0.1*pj2->getVy());
                        pj2->setAy(-0.1*pj2->getAy());
                        pj2->setVx(0);
                        pj2->setPx(pj2->getPx()+3);
                    }
                                                    //derecha
                    else if( (pj2->getPx()+19>muros2->getPx())&&(pj2->getPx() < muros2->getPx()) && (pj2->getPy() > muros2->getPy()) )
                    {
                        pj2->setVy(-0.1*pj2->getVy());
                        pj2->setAy(-0.1*pj2->getAy());
                        pj2->setVx(0*pj2->getVx());
                        pj2->setPx(pj2->getPx()-3);
                    }

                    else if( (pj2->getPy() > muros2->getPy()) && (pj2->getPy() < muros2->getPy()+40) && (pj2->getPy()+19 > muros2->getPy()) && pj2->getVy() > 0 )
                    {
                        pj2->setPy(pj2->getPy()+5);
                        pj2->setVx(0);
                    }
                    else
                    {
                        if(muros2->getTipo()==5 || muros2->getTipo()==6)
                        {
                            pj2->setVx(i+muros2->getVx());
                        }


                        if(muros2->getTipo()==6)
                        {
                            if(f2==1){pj2->setVy(-20);}

                            else{pj2->setVy(muros2->getVy()-4);}
                        }

                        else
                        {
                            pj2->setVy(-0.1*pj2->getVy());
                            pj2->setAy(-0.1*pj2->getAy());
                        }
                    }
                }
            }
        }
    }
    else
    {
        pj2->setAy(10);
    }
    }

//=====================================================================================================================

//============================ colisiones proyectiles ====================================================================

    copyammo = ammo;
    proyectiles *bu;
    for(list<proyectiles *>::iterator n=copyammo.begin();n!=copyammo.end();n++){
      bu= *n;
      QList<QGraphicsItem *> colisionesbala = scene->collidingItems(bu);
      if(!colisionesbala.isEmpty()){


          objetos *muros = dynamic_cast<objetos *>(colisionesbala[0]);
          if(muros){
              if(muros->getTipo()==1){
                  scene->removeItem(bu);
                  for(list<proyectiles *>::iterator non=ammo.begin();non!=ammo.end();non++){
                      if(bu==*non ){delete *non;ammo.remove(*non);break;}
                  }

              }

              else{

              }
          }

          else{
              Personaje *personajes = dynamic_cast<Personaje *>(colisionesbala[0]);
              if(personajes){
                  scene->removeItem(bu);
                  personajes->setPx(inix);
                  personajes->setPy(iniy);
                  pj1->setVidas(pj1->getVidas()-1);

                  for(list<proyectiles *>::iterator non=ammo.begin();non!=ammo.end();non++){
                      if(bu==*non ){ammo.remove(*non);break;}
                  }

                  if(pj1->getVidas()==0){scene->removeItem(pj1);scene->removeItem(pj2);gameover();}


              }

          }

      }
    }
//=====================================================================================================================

//======================== Colisiones Coleccionables ====================================================================================

    copybotin = botin;
    Coleccionables *bot;
    for(list<Coleccionables *>::iterator n=copybotin.begin();n!=copybotin.end();n++)
    {
      bot = *n;
      QList<QGraphicsItem *> colisionesbotin = scene->collidingItems(bot);
      if(!colisionesbotin.isEmpty())
      {
          objetos *muros = dynamic_cast<objetos *>(colisionesbotin[0]);
          if(muros)
          {
              if(muros->getTipo()==1)
              {
                  scene->removeItem(bot);
                  for(list<Coleccionables *>::iterator non=botin.begin();non!=botin.end();non++)
                  {
                      if(bot==*non ){botin.remove(*non);break;}
                  }
              }
          }
          else
          {
              Personaje *personajes = dynamic_cast<Personaje *>(colisionesbotin[0]);
              if(personajes)
              {
                  scene->removeItem(bot);
                  if(bot->getTipo()==4)
                  {
                    pj1->setLlaves(pj1->getLlaves()+1);
                    pj1->setPuntaje(pj1->getPuntaje()+500);
                    qDebug()<<"numero de llaves: "<<pj1->getLlaves();
                  }

                  else if(bot->getTipo()==50)
                  {
                      qDebug()<<"puntaje +100";
                      pj1->setPuntaje(pj1->getPuntaje()+100);
                  }

                  else if(bot->getTipo()==51)
                  {
                      qDebug()<<"vida +1";
                      pj1->setVidas(pj1->getVidas()+1);
                  }


                  for(list<Coleccionables *>::iterator non=botin.begin();non!=botin.end();non++)
                  {
                      if(bot==*non ){botin.remove(*non);break;}
                  }

                  if(pj1->getVidas()==0){scene->removeItem(pj1);}
              }
          }
      }
    }

//=========================================================================================================================

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

//========================Controles Jugador 1==============================================================================

                if(event->key() == Qt::Key_A){
                    pj1->setVx(-30);
                }else if(event->key() == Qt::Key_D){
                    pj1->setVx(30);
                }else if(event->key() == Qt::Key_W){
                   QList<QGraphicsItem *> colisionesp = scene->collidingItems(pj1);
                    if(!colisionesp.isEmpty()){

                        f=1;
                        pj1->setVy(-40);
                    }
                 }
//=====================================================================================================================

//========================Controles Jugador 2==============================================================================

                if(event->key() == Qt::Key_J){
                    pj2->setVx(-30);
                }else if(event->key() == Qt::Key_L){
                    pj2->setVx(30);
                }else if(event->key() == Qt::Key_I){
                   QList<QGraphicsItem *> colisiones2p = scene->collidingItems(pj2);
                    if(!colisiones2p.isEmpty()){
                        f2=1;
                        pj2->setVy(-40);
                    }
                }


//=====================================================================================================================
                if(event->key() == Qt::Key_P){
                   pause();

                }

                if(event->key() == Qt::Key_T){

                    if(multi==0){
                        pj2 = new Personaje(inix+40,iniy,0,0,0,0,0,0,"0",0);
                        scene->addItem(pj2);
                        multi=1;
                    }

                }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

//===============================Control Jugador 1=====================================================================================

        //qDebug()<<"Presione un tecla: "<<event->key();
        if(event->key() == Qt::Key_A){
            pj1->setVx(0);
            i=0;
        }else if(event->key() == Qt::Key_D){
            pj1->setVx(0);
        }else if(event->key() == Qt::Key_W){
            f=0;
        }

//=====================================================================================================================

//===============================Control Jugador 2=======================================================================

        //qDebug()<<"Presione un tecla: "<<event->key();
        if(event->key() == Qt::Key_J){
            pj2->setVx(0);
            i2=0;
        }else if(event->key() == Qt::Key_L){
            pj2->setVx(0);
        }else if(event->key() == Qt::Key_I){
            f2=0;
        }
//=====================================================================================================================

}

void MainWindow::onFire(){
    objetos *p;
    if(dis==150){

        for(list<objetos *>::iterator n=cannon.begin();n!=cannon.end();n++){
            p= *n;
            bala = p->generarbala();
            ammo.push_back(bala);
            scene->addItem(ammo.back());
            dis = 0;
        }
    }
    else{dis++;}
}

void MainWindow:: obtener_nivel(int num_nivel)
{
    int cont=0,fila=0,largo=0;
    ifstream sis;
    string datos="";
    sis.open("../niveles.txt");
    while(!sis.eof())
    {
        getline(sis,datos);
        if(datos[0]=='/')
        {
            cont = cont + 1;
            if(cont>num_nivel)
            {
                break;
            }
        }
        if(cont==num_nivel && datos[0]!='/')
        {
            largo=datos.size();
            for(int columna=0,i=0;i<=largo;columna++)
            {
                nivel[fila][columna]=datos[i]-'0';
                i=i+2;
            }
            fila = fila + 1;
        }
        datos="";
    }
    sis.close();
}

void MainWindow:: Menu()
{

    delete pj1;
    delete pj2;
    delete player;
    delete tiempo;
    close();
}

void MainWindow::gameover(){
    tiempo->stop();
    pj1->setVidas(3);
    if(pj1->getPuntaje()>pj1->getPuntaje_maximo())
    {
        pj1->setPuntaje_maximo(pj1->getPuntaje());
    }
    pj1->setPuntaje(0);
    pj1->setNivel(1);

    ofstream archivo;
    archivo.open(pj1->getNombre());
    archivo<<"/\n";
    archivo<<pj1->getNivel()<<"\n";
    archivo<<"/\n";
    archivo<<pj1->getPuntaje()<<"\n";
    archivo<<"/\n";
    archivo<<pj1->getVidas()<<"\n";
    archivo<<"/\n";
    archivo<<pj1->getPuntaje_maximo();
    archivo.close();
    //actualizar archivo de texto


    ui->label_4->setVisible(true);
    ui->label_3->setVisible(true);
    ui->reset->setVisible(true);
    ui->Back_Menu->setVisible(true);
}

void MainWindow::gamefinish(){
    tiempo->stop();
    pj1->setVidas(3);
    pj1->setPuntaje(0);
    pj1->setNivel(1);

    ofstream archivo;
    archivo.open(pj1->getNombre());
    archivo<<"/\n";
    archivo<<pj1->getNivel()<<"\n";
    archivo<<"/\n";
    archivo<<pj1->getPuntaje()<<"\n";
    archivo<<"/\n";
    archivo<<pj1->getVidas()<<"\n";
    archivo<<"/\n";
    archivo<<pj1->getPuntaje_maximo();
    archivo.close();
    //actualizar archivo de texto (incluir puntaje maximo)


    ui->label_5->setVisible(true);
    ui->label_3->setVisible(true);
    ui->reset->setVisible(true);
    ui->Back_Menu->setVisible(true);
}

void MainWindow::reinicio(){

    crearmundo(pj1->getVidas(),pj1->getNivel(),pj1->getPuntaje(),pj1->getNombre(),pj1->getPuntaje_maximo());


}

void MainWindow::pause(){

    if(ps==0){
        tiempo->stop();ps=1;
        ui->label->setVisible(true);
        ui->Back_Menu->setVisible(true);
        ui->label_3->setVisible(true);
    }

    else{
        tiempo->start(10);ps=0;
        ui->label->setVisible(false);
        ui->Back_Menu->setVisible(false);
        ui->label_3->setVisible(false);
    }


}

void MainWindow::crearmundo(int vidas,int level,int score,string name,int p_max){

    if(conti==1){
        scene->destroyed();
        auto it3=muros.begin();
        delete pj1;
        delete pj2;
        while(it3!=muros.end()){delete *it3;it3++;}
        auto it1=cannon.begin();
        while(it1!=cannon.end()){delete *it1;it1++;}
        auto it2=botin.begin();
        while(it2!=botin.end()){delete *it2;it2++;}
    }
    tim=0;
    tiempo->start(5);
    scene = new QGraphicsScene(this);
    ui->label->setVisible(false);
    ui->Back_Menu->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->reset->setVisible(false);
    ui->label_5->setVisible(false);

    muros.clear();
    cannon.clear();
    botin.clear();

    qDebug()<<"nivel actual: "<<level;

    int x , y = 0;
    obtener_nivel(level);
    for(int i=0; i<30 ; i++){ //alto
        y=i*40;
        for(int j=0; j<40 ; j++){ //ancho
            x=j*40;

            if(nivel[i][j]!=0){
               if(nivel[i][j]==9){

                    pj1 = new Personaje(x,y,0,0,0,vidas,level,score,name,p_max);
                    scene->addItem(pj1);
                    scene->setSceneRect(pj1->getPx(),pj1->getPy(),0,0);
                    scene->foregroundBrush();
                    ui->graphicsView->setScene(scene);
                    inix = x;
                    iniy = y;

               }
               else if(nivel[i][j]==8){
                    cannon.push_back(new objetos(x,y,nivel[i][j]));
                    scene->addItem(cannon.back());

               }

               else if(nivel[i][j]==4 || nivel[i][j]==51){
                   botin.push_back(new Coleccionables(x,y,nivel[i][j]));
                   scene->addItem(botin.back());

               }

               else if(nivel[i][j]==50){
                   botin.push_back(new Coleccionables(x,y,nivel[i][j]));
                   scene->addItem(botin.back());

               }

               else{

                   muros.push_back(new objetos(x,y,nivel[i][j]));
                   scene->addItem(muros.back());
               }
            }
        }

    }
    scene->setSceneRect(pj1->getPx(),pj1->getPy(),0,0);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->ensureVisible(muros.back());

}
