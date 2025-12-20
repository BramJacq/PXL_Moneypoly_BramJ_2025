#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <vector>
#include "Game.h"

namespace pxl {

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(Game *game, QWidget *parent = nullptr);

private slots:
    void onRollClicked();
    void onBotTimerTimeout();
    void updateUI();

private:
    Game *m_game;
    QTimer *m_botTimer;

    // UI MEMBERS WE USED IN .CPP
    int rows_;
    int cols_;

    QLabel *msgBox_;

    std::vector<QLabel*> tileLabels_;   // ONLY border tiles
    std::vector<QLabel*> emptyLabels_;  // center tiles

};

} // namespace pxl
