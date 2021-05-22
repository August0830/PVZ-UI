#include "card.h"
#include "shop.h"
#include <QGraphicsSceneMouseEvent>
//初始化类通用的表格和哈希表
const QMap<QString,int>Card::map = {{"Sunflower",0},{"PeaShooter",1},{"DoubleShooter",2}
                                    ,{"FrozenShooter",3},{"Nut",4},{"TallNut",5}
                                    ,{"PotatoMine",6},{"CherryBomb",7}};
//{"Garlic",8}
const QVector<QString>Card::name = {"Sunflower","PeaShooter","DoubleShooter",
                                   "FrozenShooter","Nut","TallNut","PotatoMine",
                                   "CherryBomb"};
const QVector<int>Card::price={50,100,150,150,50,100,25,50};
const QVector<int>Card::cool = {227,227,606,606,606,606,227,606};
Card::Card(QString s)
{
    text=s;
    counter=0;
}
QRectF Card::boundingRect() const
{
    return QRectF(-50,-30,100,60);
}
void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   Q_UNUSED(option)
   Q_UNUSED(widget) //不使用此参数
   painter->scale(0.6,0.58);
   painter->drawPixmap(QRect(-50,-70,100,140),QPixmap("://image/Card.png"));
   painter->drawPixmap(QRect(-35,-42,70,70),QPixmap("://image/"+text+".png"));
   QFont font;
   font.setPointSizeF(15);//设置字号
   painter->setFont(font);
   painter->drawText(-30,60,QString().sprintf("%3d",price[map[text]]));
   if(counter<cool[map[text]])
   {
       QBrush brush(QColor(0,0,0,200));
       painter->setBrush(brush);//涂黑卡片表示在冷却
       painter->drawRect(QRectF(-48,-68,98,132*(1-qreal(counter)/cool[map[text]])));//除法转成double
   }
}
void Card::advance(int phase)
{
    if(!phase)
        return ;
    update();//更新
    if(counter<cool[map[text]])
        counter++;
}
void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    if(counter<cool[map[text]])
        event->setAccepted(false);
    Shop* shop=qgraphicsitem_cast<Shop*>(parentItem());
            //场景视图Item类转换 实例化转换的函数
    if(price[map[text]]>shop->sun_deposit)//无法购买 忽略点击事件
        event->setAccepted(false);
    setCursor(Qt::ArrowCursor);//保持对象的形状?
}

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(QLineF(event->screenPos(),event->buttonDownScreenPos(Qt::LeftButton)).length()<
            QApplication::startDragDistance())
        return ;//拖拽的距离要明显一些
    QDrag* drag=new QDrag(event->widget());
    QMimeData *mime = new QMimeData;//多媒体数据类
    QImage image(";//image/"+text+".png");
    mime->setText(text);
    mime->setImageData(image);
    drag->setMimeData(mime);
    drag->setPixmap(QPixmap::fromImage(image));
    drag->setHotSpot(QPoint(35,35));//定位
    drag->exec();
    setCursor(Qt::ArrowCursor);
}
void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    setCursor(Qt::ArrowCursor);
}
