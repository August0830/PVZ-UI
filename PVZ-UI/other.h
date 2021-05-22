#ifndef OTHER_H
#define OTHER_H
#include <QtWidgets>
#include <QGraphicsItem>
#include <QPainter>

class Other:public QGraphicsItem
{
public:
    enum {Type = UserType+3};//qt 自定义数据type
    Other();
    int type() const override;
};

#endif // OTHER_H
