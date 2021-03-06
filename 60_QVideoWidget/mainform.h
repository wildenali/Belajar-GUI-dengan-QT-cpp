#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QVideoWidget>

class MainForm: public QWidget{
  Q_OBJECT
private:
  QMediaPlayer *player;
  QVideoWidget *videoWidget;
  QLabel *label1;
  QSlider *progressSlider;
  QLabel *label2;
  QSlider *volumeSlider;
  QPushButton *openButton;
  QPushButton *playButton;
  QPushButton *pauseButton;
  QPushButton *stopButton;
  void setPlayingMode(bool mode);

private slots:
  void on_progressSlider_sliderMoved(int position);
  void on_volumeSlider_sliderMoved(int position);
  void on_openButton_clicked();
  void on_playButton_clicked();
  void on_pauseButton_clicked();
  void on_stopButton_clicked();
  void on_player_positionChanged(qint64 position);
  void on_player_durationChanged(qint64 position);

public:
  explicit MainForm(QWidget *parent);
  ~MainForm();
  void setupUI();
};

#endif
