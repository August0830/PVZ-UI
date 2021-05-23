#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));
    sound = new QSound(":/image/Grazy Dave.wav");
    sound->setLoops(QSound::Infinite);

    timer = new QTimer;

    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600);//
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    Shop* shop = new Shop;
    shop->setPos(520,45);
    scene->addItem(shop);

    Shovel* shovel = new Shovel;
    shovel->setPos(830,40);
    scene->addItem(shovel);

    Button *button=new Button(sound,timer);
    button->setPos(950,40);
    scene->addItem(button);

    Map *map = new Map;
    map->setPos(618,326);
    scene->addItem(map);

    for(int i=0;i<5;++i)
    {
        Mower *mower = new Mower;
        mower->setPos(210,130+98*i);
        scene->addItem(mower);
    }

    view = new QGraphicsView(scene,this);
    view->resize(902,602);
    view->setRenderHints(QPainter::Antialiasing);

    view->setBackgroundBrush(QPixmap("://image/Background.jpg"));//导入背景图片 记得j将图片加入qt资源
    view->setCacheMode(QGraphicsView::CacheBackground);//保存图片
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);//只更新被更新的部分

    sound ->play();
    timer->start(33);//?
    view->show();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::generate_random_Zombie()
{
    /*static int low=4;
    static int high =8;
    static int maxtime = 20*1000/33;
    static int time = maxtime/2;
    static int counter=0;//计时器 按照一定时间间隔生成僵尸*？*/
}
