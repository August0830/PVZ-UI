#include "shop.h"
#include <QDebug>
Shop::Shop()
{
    sun_deposit=200;
    counter=0;
    time = int(7.0*1000/33);
    Card* card=nullptr;
    for(int i=0;i<Card::name.size();++i)
    {
        card = new Card(Card::name[i]);
        card->setParentItem(this);//绑定父类
        card->setPos(-157+65*i,-2);
    }
    QList<QGraphicsItem*> child = this->childItems();
    //show the plant choice
}

void Shop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-270, -45, 540, 90), QPixmap("://image/Shop.png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(QRectF(-255, 18, 65, 22), Qt::AlignCenter, QString::number(sun_deposit));
    //记得换成阳光数
    painter->drawPoint(-220, 0);
}
QRectF Shop::boundingRect() const
{
    return QRectF(-270, -45, 540, 90);
}
void Shop::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(++counter>=time)
    {
        counter=0;
        scene()->addItem(new Sun);
    }
}

void Shop::addPlant(QString s, QPointF pos)
{
    QList<QGraphicsItem *>items = scene()->items(pos);//获取该位置上对象
    foreach (QGraphicsItem *item,items)
    {
        if(item->type()==Plant::Type) //如果已经有植物 不能再种
            return;
    }

    Plant *plant = nullptr;
    int index = Card::map[s];
    switch(index)
    {
        case 0:
            plant = new Sunflower;break;
        case 1:
            plant =new PeaShooter;break;
        case 2:
            plant = new DoubleShooter;break;
        case 3:
            plant = new FrozenShooter;break;
        case 4:
            plant = new Nut;break;
        case 5:
            plant = new PotatoMine;break;
        case 6:
            plant = new CherryBomb;break;

    }
    plant->setPos(pos);
    int price = Card::price[index];
    int sun = sun_deposit;
    sun -= price;
    sun_deposit = sun_deposit-price;

    scene()->addItem(plant);
    QList<QGraphicsItem*> child = this->childItems();
    foreach(QGraphicsItem *item,child)
    {
        Card *card = qgraphicsitem_cast<Card*>(item);
        if(card->text==s)
            card->counter=0;
    }
    counter=0;
}

