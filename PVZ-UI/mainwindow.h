#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QSound>
#include "shop.h"
#include "card.h"
#include "button.h"
#include "shovel.h"
#include "map.h"
#include "mower.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generate_random_Zombie();
    void check_end();
private:
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QSound* sound;
};
#endif // MAINWINDOW_H
