#include "BoardWidget.h"
#include <QGridLayout>
#include <QVBoxLayout>

namespace pxl {

BoardWidget::BoardWidget(Game *game, QWidget *parent)
    : QWidget(parent), m_game(game), m_botTimer(new QTimer(this))
{
    setWindowTitle("MonoPoly BramJ 2025");

    QVBoxLayout *root = new QVBoxLayout(this);
    QGridLayout *grid = new QGridLayout();

    // 5x5 rectangle board
    rows_ = 5;
    cols_ = 5;

    int boardSize = m_game->getBoardSize();
    int currentTile = 0;

    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {

            QLabel *lbl = new QLabel(this);
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setStyleSheet("border:1px solid black; min-width:90px; min-height:90px;");

            bool isBorder =
                   r == 0 || r == rows_-1 ||
                   c == 0 || c == cols_-1;

            if (isBorder && currentTile < boardSize) {
                lbl->setText(QString::fromStdString(m_game->tileAt(currentTile).getName()));
                tileLabels_.push_back(lbl);
                currentTile++;
            } else {
                lbl->setText("");
                emptyLabels_.push_back(lbl);
            }

            grid->addWidget(lbl, r, c);
        }
    }

    root->addLayout(grid);

    QPushButton *rollBtn = new QPushButton("Roll Dice", this);
    connect(rollBtn, &QPushButton::clicked, this, &BoardWidget::onRollClicked);
    root->addWidget(rollBtn);

    msgBox_ = new QLabel(this);
    msgBox_->setText("Welkom bij MonoPoly BramJ 2025!");
    root->addWidget(msgBox_);

    connect(m_game, &Game::boardChanged, this, &BoardWidget::updateUI);
    connect(m_game, &Game::message, msgBox_, &QLabel::setText);

    updateUI();
}

void BoardWidget::onRollClicked()
{
    if (!m_game->isCurrentPlayerHuman())
        return;

    m_game->humanRollOnce();
}

void BoardWidget::onBotTimerTimeout() {}

void BoardWidget::updateUI()
{
    int boardSize = m_game->getBoardSize();

    // reset tile names
    for (size_t i = 0; i < tileLabels_.size() && i < (size_t)boardSize; i++) {
        tileLabels_[i]->setText(QString::fromStdString(m_game->tileAt(i).getName()));
    }

    // draw players with initials instead of dots
    for (size_t p = 0; p < m_game->playerCount(); p++) {
        const Player &pl = m_game->playerAt(p);
        int pos = pl.getPos();

        if (pos < (int)tileLabels_.size()) {
            QString txt = tileLabels_[pos]->text();
            txt += "\n";

            QString initials = QString::fromStdString(pl.getName()).left(2).toUpper();
            txt += initials;

            tileLabels_[pos]->setText(txt);
        }
    }
}

} // namespace pxl
