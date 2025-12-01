#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <vector>
#include "Game.h"

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

namespace pxl {

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(Game *game, QWidget *parent = nullptr);
    ~BoardWidget() override;

private slots:
    void onRollClicked();
    void onBotTimerTimeout();
    void updateUI();

private:
    Game *m_game;
    QGridLayout *m_grid;
    std::vector<QLabel*> m_tiles;
    QLabel *m_status;
    QPushButton *m_rollBtn;
    QTimer *m_botTimer;

    size_t m_cols;
    size_t m_rows;

    // helper to map perimeter index -> grid (row,col)
    void indexToGridPos(size_t index, int &row, int &col) const;

    void buildGrid(size_t cols, size_t rows);
};

} // namespace pxl
