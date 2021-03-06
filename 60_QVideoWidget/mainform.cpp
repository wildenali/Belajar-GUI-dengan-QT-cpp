#include "mainform.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>

MainForm::MainForm(QWidget *parent) : QWidget(parent) {
  player = new QMediaPlayer(this);

  this->setupUI();
}

MainForm::~MainForm() {
  delete player;
  delete label1;
  delete progressSlider;
  delete label2;
  delete volumeSlider;
  delete openButton;
  delete playButton;
  delete pauseButton;
  delete stopButton;
}


void MainForm::setupUI() {
  this->resize(250, 150);
  this->move(500, 300);
  this->setWindowTitle("Video Player");

  // membuat objek dari kelas QVideoWidget
  videoWidget = new QVideoWidget(this);

  // menghubungkan player dengan videoWidget
  player->setVideoOutput(videoWidget);

  label1 = new QLabel("Progress");
  progressSlider = new QSlider(Qt::Horizontal);
  label2 = new QLabel("Volume");
  volumeSlider = new QSlider(Qt::Horizontal);
  volumeSlider->setValue(100);

  QGridLayout *grid = new QGridLayout();
  grid->addWidget(label1, 0, 0);
  grid->addWidget(progressSlider, 0, 1);
  grid->addWidget(label2, 1, 0);
  grid->addWidget(volumeSlider, 1, 1);

  openButton = new QPushButton("Bukaaaa");
  playButton = new QPushButton("Mainkan");
  playButton->setEnabled(false);
  pauseButton = new QPushButton("oops");
  pauseButton->setEnabled(false);
  stopButton = new QPushButton("Udahan");
  stopButton->setEnabled(false);

  QHBoxLayout *hbox = new QHBoxLayout();
  hbox->addWidget(openButton);
  hbox->addWidget(playButton);
  hbox->addWidget(pauseButton);
  hbox->addWidget(stopButton);
  hbox->addStretch();

  QVBoxLayout *layout = new QVBoxLayout();
  layout->addWidget(videoWidget);
  layout->addLayout(grid);
  layout->addLayout(hbox);

  this->setLayout(layout);

  connect(progressSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_progressSlider_sliderMoved(int)));
  connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(on_volumeSlider_sliderMoved(int)));

  connect(openButton, SIGNAL(clicked()), this, SLOT(on_openButton_clicked()));
  connect(playButton, SIGNAL(clicked()), this, SLOT(on_playButton_clicked()));
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(on_pauseButton_clicked()));
  connect(stopButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()));

  connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(on_player_durationChanged(qint64)));
  connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(on_player_positionChanged(qint64)));
}

void MainForm::setPlayingMode(bool mode) {
  if (mode) {
    playButton->setEnabled(false);
    pauseButton->setEnabled(true);
    stopButton->setEnabled(true);
  } else {
    playButton->setEnabled(true);
    pauseButton->setEnabled(false);
    stopButton->setEnabled(false);
  }
}

void MainForm::on_progressSlider_sliderMoved(int position) {
  player->setPosition(position);
}

void MainForm::on_volumeSlider_sliderMoved(int position) {
  player->setVolume(position);
}

void MainForm::on_openButton_clicked() {
  QString fileName;
  fileName = QFileDialog::getOpenFileName(this, "Opennnn", QDir::currentPath(), "MP4 File (*.mp4);;FLV File (*flv)");
  if (fileName.trimmed().size() > 0) {
    player->setMedia(QUrl::fromLocalFile(fileName));
    if (player->state() == QMediaPlayer::PlayingState) {
      player->stop();
    }
    setPlayingMode(false);
  }
}

void MainForm::on_playButton_clicked() {
  player->play();
  setPlayingMode(true);
}

void MainForm::on_pauseButton_clicked() {
  player->pause();
  setPlayingMode(false);
}

void MainForm::on_stopButton_clicked() {
  player->stop();
  setPlayingMode(false);
}

void MainForm::on_player_positionChanged(qint64 position) {
  progressSlider->setValue(position);
}

void MainForm::on_player_durationChanged(qint64 position) {
  progressSlider->setMaximum(position);
}
