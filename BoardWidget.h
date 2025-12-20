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
    void updateUI();

private:
    Game *m_game;
    int rows_;
    int cols_;

    QLabel *msgBox_;
    QLabel *balancesBox_;

    std::vector<QLabel*> tileLabels_;
    std::vector<QLabel*> emptyLabels_;
};

} // namespace pxl
