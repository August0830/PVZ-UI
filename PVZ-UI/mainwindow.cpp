#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600);//
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Shop* shop = new Shop;
    shop->setPos(520,45);
    scene->addItem(shop);
    view = new QGraphicsView(scene,this);
    view->resize(902,602);
    view->setRenderHints(QPainter::Antialiasing);

    view->setBackgroundBrush(QPixmap("://image/Background.jpg"));//导入背景图片 记得j将图片加入qt资源
    view->setCacheMode(QGraphicsView::CacheBackground);//保存图片
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);//只更新被更新的部分

    //timer->start(33);//?
    view->show();

}

MainWindow::~MainWindow()
{
    delete timer;
    delete scene;
    delete view;
}

