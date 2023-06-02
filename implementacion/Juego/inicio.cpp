#include "inicio.h"
#include "ui_inicio.h"

bool cont = 0;

Inicio::Inicio(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Inicio)
{
    ui->setupUi(this);

    tiempo1 = new QTimer();
    tiempo1->start(1);

    loadclose();


    QPixmap fon("../juego final/background4a.png");
    ui->fondocon_2->setPixmap(fon);

    QPixmap fon2("../juego final/fondoini.jpg");
    ui->fondocon->setPixmap(fon2);


    connect(tiempo1, &QTimer::timeout, this, &Inicio::abrir);

    connect(ui->newpj,&QPushButton::clicked,this,&Inicio::on_newbutton_clicked);
    connect(ui->loadbutton,&QPushButton::clicked,this,&Inicio::on_loadbutton_clicked);

    connect(ui->newbutton,&QPushButton::clicked,this,&Inicio::newgame);
    connect(ui->continue_2,&QPushButton::clicked,this,&Inicio::loadgame);

    connect(ui->loadBack,&QPushButton::clicked,this,&Inicio::loadclose);
    connect(ui->exit,&QPushButton::clicked,this,&Inicio::closegame);



    juego = new MainWindow();





}

Inicio::~Inicio()
{
    delete ui;
}


void Inicio::startgame(){
    if(cont==1){

       delete juego;
    }
    QWidget *parent = nullptr;
    juego = new MainWindow(parent,vidas,level,score,nombre,puntaje_maximo);
    juego->show();
    setVisible(false);
    ui->invalido->setVisible(false);
    cont = 1;

}

void Inicio::abrir(){
    if(juego->isHidden()){
        setVisible(true);
    }

}

void Inicio::closegame(){

    tiempo1->stop();
    close();

}

void Inicio::newgame(){

    ui->loadBack->setVisible(true);
    ui->Cuenta_2->setVisible(true);
    ui->incuenta->setVisible(true);
    ui->newpj->setVisible(true);
    ui->fondocon->setVisible(true);
    ui->invalido->setVisible(false);
}

void Inicio::loadgame(){

    ui->loadBack->setVisible(true);
    ui->Cuenta->setVisible(true);
    ui->incuenta->setVisible(true);
    ui->loadbutton->setVisible(true);
    ui->fondocon->setVisible(true);
    ui->invalido->setVisible(false);

}

void Inicio::loadclose(){
    ui->loadBack->setVisible(false);
    ui->Cuenta->setVisible(false);
    ui->incuenta->setVisible(false);
    ui->loadbutton->setVisible(false);
    ui->invalido->setVisible(false);
    ui->Cuenta_2->setVisible(false);
    ui->newpj->setVisible(false);
    ui->fondocon->setVisible(false);
}

void Inicio::on_loadbutton_clicked()
{
    ui->invalido->setVisible(false);
    ifstream datos;
    QString name=ui->incuenta->text();//,nivel,puntaje;
    string _nombre="../partidas/"+name.toStdString()+".txt",dato="";
    int puntaje=0, nivel=0, vida=0, cont=0, p_max=0;
    char* pEnd;
    datos.open(_nombre);
    if(datos.is_open())
    {
        qDebug()<<"cargando partida \n";
        while(!datos.eof())
            {
                getline(datos,dato);
                if(dato[0]=='/')
                {
                    cont = cont + 1;
                }
                else if(cont==1)
                {
                    nivel=strtod(dato.c_str(),&pEnd);
                }
                else if(cont==2)
                {
                    puntaje=strtod(dato.c_str(),&pEnd);
                }
                else if(cont==3)
                {
                    vida=strtod(dato.c_str(),&pEnd);
                }
                else if(cont==4)
                {
                    p_max=strtod(dato.c_str(),&pEnd);
                }
                dato="";
            }

        vidas = vida;
        score = puntaje;
        level = nivel;
        nombre = _nombre;
        puntaje_maximo=p_max;
        ui->incuenta->clear();
        datos.close();
        loadclose();
        startgame();
    }
    else
    {
        ui->invalido->setVisible(true);
        ui->incuenta->clear();
    }
    datos.close();
}


void Inicio::on_newbutton_clicked()
{
    ui->invalido->setVisible(false);
    ifstream datos;
    ofstream _datos;
    fstream datos2;
    QString name;
    name=ui->incuenta->text();
    bool se_puede=0,se_puede2=0;
    string _nombre="../partidas/"+name.toStdString()+".txt",dato="";
    datos.open(_nombre);
    if(datos.is_open()){
        ui->incuenta->clear();
        ui->invalido->setVisible(true);
    }
    else
    {
        se_puede=1;
        if(!name.isEmpty()){se_puede2=1;}
    }
    datos.close();
    if(se_puede && se_puede2){

        _datos.open(_nombre);
         qDebug()<<_datos.is_open();
        _datos<<"/\n";
        _datos<<1<<"\n";
        _datos<<"/\n";
        _datos<<0<<"\n";
        _datos<<"/\n";
        _datos<<3<<"\n";
        _datos<<"/\n";
        _datos<<0;
        _datos.close();
        ui->incuenta->clear();
        nombre=_nombre;
        //datos.close();
        se_puede=0;
        se_puede2=0;
        loadclose();
        startgame();    
    }
    //datos.close();
}

