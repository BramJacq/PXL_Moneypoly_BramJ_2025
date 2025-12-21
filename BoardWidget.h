#pragma once
#include <QWidget>     // vraag 42: useful Qt class
#include <QLabel>      // vraag 42: useful Qt class
#include <QPushButton>// vraag 42: useful Qt class
#include <QTimer>     // vraag 42: useful Qt class
#include <vector>     // vraag 36: useful container class
#include "Game.h"     // vraag 6: separate header files

namespace pxl {       // vraag 27: self-made namespace

class BoardWidget : public QWidget {
    Q_OBJECT          // vraag 43: signals/slots

public:
    explicit BoardWidget(Game *game, QWidget *parent = nullptr);
    // vraag 13: parameterized constructor
    // vraag 16: member initialization in constructors

private slots:
    void onRollClicked();       // vraag 20: useful member function
    void onBotTimerTimeout();  // vraag 20
    void updateUI();           // vraag 20
    void onEndGameClicked();   // vraag 20

private:
    Game *m_game;              // vraag 22: useful member variable
    QTimer *m_botTimer;        // vraag 32: dynamic memory allocation (new)

    int rows_;
    int cols_;

    QLabel *msgBox_;
    QLabel *balancesBox_;

    std::vector<QLabel*> tileLabels_; // vraag 36: container class
    std::vector<QLabel*> emptyLabels_;
};

} // namespace pxl
