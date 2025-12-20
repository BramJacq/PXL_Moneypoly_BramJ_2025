#include "BoardWidget.h"
#include <QGridLayout>
#include <QVBoxLayout>

namespace pxl {

BoardWidget::BoardWidget(Game *game, QWidget *parent)
    : QWidget(parent), m_game(game)
{
    setWindowTitle("MonoPoly BramJ 2025");

    QVBoxLayout *root = new QVBoxLayout(this);
    QGridLayout *grid = new QGridLayout();

    rows_ = 5;
    cols_ = 5;

    int boardSize = m_game->getBoardSize();
    int currentTile = 0;

    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {
            QLabel *lbl = new QLabel(this);
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setStyleSheet("border:1px solid black; min-width:90px; min-height:90px;");

            bool isBorder = r == 0 || r == rows_-1 || c == 0 || c == cols_-1;

            if (isBorder && currentTile < boardSize) {
                lbl->setText(QString::fromStdString(m_game->tileAt(currentTile).getName()));
                tileLabels_.push_back(lbl);
                currentTile++;
            } else {
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
    root->addWidget(msgBox_);

    balancesBox_ = new QLabel(this);
    root->addWidget(balancesBox_);

    connect(m_game, &Game::boardChanged, this, &BoardWidget::updateUI);
    connect(m_game, &Game::message, msgBox_, &QLabel::setText);

    updateUI();
}

void BoardWidget::onRollClicked()
{
    if (m_game->isCurrentPlayerHuman())
        m_game->humanRollOnce();
}

void BoardWidget::updateUI()
{
    int boardSize = m_game->getBoardSize();

    for (size_t i = 0; i < tileLabels_.size() && i < (size_t)boardSize; i++) {
        tileLabels_[i]->setText(QString::fromStdString(m_game->tileAt(i).getName()));
    }

    for (size_t p = 0; p < m_game->playerCount(); p++) {
        const Player &pl = m_game->playerAt(p);
        if (!pl.isAlive()) continue;

        int pos = pl.getPos();
        if (pos < (int)tileLabels_.size()) {
            QString txt = tileLabels_[pos]->text();
            txt += "\n" + QString::fromStdString(pl.getName()).left(2).toUpper();
            tileLabels_[pos]->setText(txt);
        }
    }

    QString balances;
    for (size_t i = 0; i < m_game->playerCount(); ++i) {
        const Player &p = m_game->playerAt(i);
        balances += QString::fromStdString(p.getName()) +
                    ": " + QString::number(p.getMoney()) + " €\n";
    }
    balancesBox_->setText(balances);
}

} // namespace pxl
