#include <QMessageBox>
#include <Qtimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QImage>
#include <QPainter>
#include <qmath.h>
#include "game.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    time(new QTimer(this)),
    size(20),
    memesOn(false),
    filename (":/images/classic.png")
{
    time->setInterval(100);
    prev = new bool[(size) * (size)];
    current = new bool[(size) * (size)];
    next = new bool[(size) * (size)];
    connect(time, SIGNAL(timeout()), this, SLOT(newField()));
    memset(prev,    false, sizeof(bool)* size * size);
    memset(current, false, sizeof(bool)* size * size);
    memset(next,    false, sizeof(bool)* size * size);
}


GameWidget::~GameWidget()
{
    delete [] prev;
    delete [] current;
    delete [] next;
}


void GameWidget::startGame()
{
    time->start();
}
void GameWidget::pauseGame()
{
    time->stop();
}
void GameWidget::about()
{
    time->stop();
    QMessageBox::information(this,
                             tr("About Application"),
                             tr("This application allows you to draw a map for John Conway's Game of Life."
                                "\nYou can draw new cells during game or you can click Pause button to freeze changing of generations."
                                "\nAlso you can adjust the speed of generation's recreation by moving the scrollbar. "
                                "\nChoose between three possible skins for alive cells which are plain square, witness and Sanya from Univer"
                                "\nEnjoy."),
                             QMessageBox::Ok);
    return;
}

void GameWidget::random()
{
    for(int i=0; i < size; i++) {
        for(int j=0; j < size; j++) {
            current[i*size+j]=qrand()%2;
        }
    }
    update();
}


int GameWidget::interval()
{
    return time->interval();
}
void GameWidget::selectSpeed(int speed)
{
    time->setInterval(1000/speed);
}

void GameWidget::SetClassicSkin()
{
    filename = ":/images/classic.png";
    memesOn=false;
}
void GameWidget::SetWitnessSkin()
{
    filename = ":/images/witness.png";
    memesOn=false;
}
void GameWidget::SetSanyaSkin()
{
    filename = ":/images/sanya.png";
    memesOn=false;
}
void GameWidget::SetMemesRush()
{
    filename = ":/images/" + QString::number(qrand()%9+1) + ".png";
    memesOn=true;
}

void GameWidget::newField()
{
    bool same1 = 1, same2 = 1;
    for(int i=0; i < size; i++) {
        for(int j=0; j < size; j++) {
            next[i*size + j] = isAlive(i, j);
            same1 = same1 && (next[i*size + j] == current[i*size + j]);
            same2 = same2 && (next[i*size + j] == prev[i*size + j]);
        }
    }
    for(int i=0; i < size; i++) {
        for(int j=0; j < size; j++) {
            prev[i*size + j] = current[i*size + j];
            current[i*size + j] = next[i*size + j];
        }
    }
    update();
    if (same1||same2) {
        QMessageBox::information(this,
                                 tr("Game is finished"),
                                 tr("End of game bacause next generations will be the same or become a loop."),
                                 QMessageBox::Ok);
        time->stop();
        return;
    }
}


bool GameWidget::isAlive(int i, int j)
{
    int neighbours = 0;
    for (int m = -1; m <= 1; m++){
        for (int n = -1; n <= 1; n++){
            if (m!=0||n!=0) neighbours += current[(i + m + size)%size * size + (size + j + n)%size];
        }
    }
    if (neighbours == 3) return true;
    else if ( (current[i*size + j] == true) && (neighbours == 2) ) return true;
    else return false;
}


void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    drawField(p);
}


void GameWidget::mousePressEvent(QMouseEvent *e)
{
    int i,j;
    i = floor(e->y() * size / (double)height()) ;
    j = floor(e->x() * size / (double)width() ) ;
    current[i*size + j] = !current[i*size + j];
    update();
}


void GameWidget::drawField(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1);

    QColor gridColor = "#81BCBA";
    gridColor.setAlpha(50);
    p.setPen(gridColor);
    p.drawRect(borders);

    double CellWidth = (double)width()/size;
    double CellHeight = (double)height()/size;

    for(double i = 0; i < width(); i += CellWidth)
        p.drawLine(i, 0, i, height());

    for(double i = 0; i < height(); i += CellHeight)
        p.drawLine(0, i, width(), i);

    QImage img(filename);
    for(int i=0; i < size; i++) {
        for(int j=0; j < size; j++) {
            if(current[i*size + j] == true) {

                qreal top  = (qreal)(CellHeight * i);
                qreal left = (qreal)(CellWidth  * j);
                QRectF r(left, top, (qreal)CellWidth, (qreal)CellHeight);
                if (memesOn) {
                    SetMemesRush();
                    img.load(filename);
                }
                p.drawImage(r, img);
         }
       }
    }
}


