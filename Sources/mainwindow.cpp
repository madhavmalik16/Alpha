#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);  //Central Widget is the central image that is shown in window


    slider = new QSlider(this);   //for showing the progress of video played
    bar = new QProgressBar(this);

    slider->setOrientation(Qt::Horizontal);

    ui->statusBar->addPermanentWidget(slider);
    ui->statusBar->addPermanentWidget(bar);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);


    connect(player,&QMediaPlayer::durationChanged,bar,&QProgressBar::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,bar,&QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this,"Open a File","","Video File (*.*)");  //Opening a File
    on_actionStop_triggered();   //Stoping the File that is opened

    player->setMedia(QUrl::fromLocalFile(filename));  //setting the current media
    on_actionPlay_triggered();  //Playing the File
}

void MainWindow::on_actionPlay_triggered()
{
    player->play();
    ui->statusBar->showMessage("Playing");
}

void MainWindow::on_actionPause_triggered()
{
    player->pause();
    ui->statusBar->showMessage("Paused");
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();   //close the file
    ui->statusBar->showMessage("Stopped");
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}
