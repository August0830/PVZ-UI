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

    connect(timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    connect(timer,&QTimer::timeout,this,&MainWindow::generate_random_Zombie);
    connect(timer,&QTimer::timeout,this,&MainWindow::check_end);

    sound ->play();
    timer->start(33);//?
    view->show();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete view;
    delete sound;
}

void MainWindow::generate_random_Zombie()
{
    static int low=4;
    static int high =8;
    static int maxtime = 20*1000/33;
    static int time = maxtime/2;
    static int counter=0;//计时器 按照一定时间间隔生成僵尸
    if(++counter>=time)
    {
        if(++low>high)
        {
            maxtime/=1.3;
            high*=2;
        }
        counter=0;
        time = qrand()%(2*maxtime/3)+maxtime/3;
        int type = qrand()%100;
        int i=qrand()%5;
        Zombie *zom;
        if(type<40)
            zom = new BasicZombie;
        else if(type<70)
            zom = new BucketZombie;
        else if(type<80)
            zom = new ConeZombie;
        else if(type<90)
            zom = new FootballZombie;
        else
            zom = new ScreenZombie;
        zom->setPos(1028,130+98*i);
        scene->addItem(zom);
    }
}

void MainWindow::check_end()
{
    static int time = 1*1000/33;
    static int counter=0;
    if(++counter>=time)
    {
        counter=0;
        const QList<QGraphicsItem*>items = scene->items();
        foreach(QGraphicsItem *item,items)
        {
            if(item->type()==Zombie::Type && item->x()<200)
            {
                scene->addPixmap(QPixmap("://image/ZombiesWon.png"))->setPos(336,92);
                scene->advance();//最后刷新
                timer->stop();//停止游戏
                return ;
            }
        }
    }
}
