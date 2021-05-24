#ifndef SUN_H
#define SUN_H
#include "other.h"

class Sun:public Other
{
public:
    Sun();
    Sun(QPointF pos);
    ~Sun() override;
    QRectF boundingRect()  const override;//
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
    //打印
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void advance(int phase) override;
private:
    QMovie *movie;//下落的动画
    QPointF dest;
    int counter;
    int time;
    qreal speed;//下落速度
};

#endif // SUN_H
