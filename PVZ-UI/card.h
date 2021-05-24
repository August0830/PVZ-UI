#ifndef CARD_H
#define CARD_H
#include "other.h"

class Card:public Other
{
public:
    int counter;//冷却的计时器
    QString text;
    Card(QString s);
    const static QMap<QString,int> map;//每种植物对应的编号 static表示所有card共用
    const static QVector<QString> name;//每种植物的名字
    const static QVector<int> price;//购买的价格
    const static QVector<int> cool;//

    QRectF boundingRect()  const override;//
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    //打印
    void advance(int phase) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CARD_H
