#ifndef PLANT_H
#define PLANT_H
#include<QGraphicsScene>
#include<QGraphicsItem>
#include<QPainter>
#include<QMovie>

class Plant:public QGraphicsItem
{
public:
    int life;
    int state;
    enum{Type = UserType+1};
    Plant();
    ~Plant() override;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const override;
    void setMovie(QString path);
protected:
    QMovie *movie;//动画效果
    int attack;
    int counter;
    int time;
};

#endif // PLANT_H
