#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QColor>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);

public slots:
    void startGame();
    void pauseGame();
    void about();
    void random();

    int interval();
    void selectSpeed(int speed);
    void SetClassicSkin();
    void SetWitnessSkin();
    void SetSanyaSkin();
    void SetMemesRush();

private slots:
    void drawField(QPainter &p);
    void newField();

private:
    QTimer* time;
    bool* prev;
    bool* current;
    bool* next;
    bool memesOn;
    int size;
    QString filename;
    bool isAlive(int i, int j);
};

#endif // GAME_H
