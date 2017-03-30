#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(new GameWidget(this))
{
    ui->setupUi(this);

    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(startGame()));
    connect(ui->pauseButton, SIGNAL(clicked()), game,SLOT(pauseGame()));
    connect(ui->speedScrollbar, SIGNAL(valueChanged(int)), game, SLOT(selectSpeed(int)));
    connect(ui->helpButton, SIGNAL(clicked()), game, SLOT(about()));
    connect(ui->random, SIGNAL(clicked()), game, SLOT(random()));

    connect(ui->classic, SIGNAL(clicked()), game, SLOT(SetClassicSkin()));
    connect(ui->witness, SIGNAL(clicked()), game, SLOT(SetWitnessSkin()));
    connect(ui->sanya  , SIGNAL(clicked()), game, SLOT(SetSanyaSkin()));
    connect(ui->memes  , SIGNAL(clicked()), game, SLOT(SetMemesRush()));

    ui->gameLayout->addWidget(game);
}

MainWindow::~MainWindow()
{
    delete ui;
}

