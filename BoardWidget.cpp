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

    rows_ = 5;
    cols_ = 5;

    int boardSize = m_game->getBoardSize();
    int currentTile = 0;

    for (int r = 0; r < rows_; r++) {
        for (int c = 0; c < cols_; c++) {

            QLabel *lbl = new QLabel(this);
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setStyleSheet("border:1px solid black; min-width:60px; min-height:60px;");

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

    QPushButton *endBtn = new QPushButton("End Game", this);
    connect(endBtn, &QPushButton::clicked, this, &BoardWidget::onEndGameClicked);
    root->addWidget(endBtn);

    msgBox_ = new QLabel(this);
    msgBox_->setText("Welkom bij MonoPoly BramJ 2025!");
    root->addWidget(msgBox_);

    balancesBox_ = new QLabel(this);
    balancesBox_->setAlignment(Qt::AlignLeft);
    balancesBox_->setStyleSheet("border:1px solid gray; padding:5px;");
    root->addWidget(balancesBox_);

    connect(m_game, &Game::boardChanged, this, &BoardWidget::updateUI);
    connect(m_game, &Game::message, msgBox_, &QLabel::setText);

    connect(m_botTimer, &QTimer::timeout, this, &BoardWidget::onBotTimerTimeout);

    updateUI();
}

void BoardWidget::onRollClicked()
{
    if (!m_game->isCurrentPlayerHuman())
        return;

    m_game->humanRollOnce();
}

void BoardWidget::onBotTimerTimeout()
{
    if (m_game->isCurrentPlayerHuman()) {
        m_botTimer->stop();
        return;
    }

    m_game->advanceOneTurn();
}

void BoardWidget::onEndGameClicked()
{
    m_game->endGameNow();

    // close UI after 3 seconds
    QTimer::singleShot(3000, this, &QWidget::close);
}

void BoardWidget::updateUI()
{
    int boardSize = m_game->getBoardSize();

    // update tile names
    for (size_t i = 0; i < tileLabels_.size() && i < (size_t)boardSize; i++) {
        tileLabels_[i]->setText(QString::fromStdString(m_game->tileAt(i).getName()));
    }

    // clear previous player marks
    for (auto lbl : tileLabels_) {
        QString name = lbl->text().split("\n")[0];
        lbl->setText(name);
    }

    // draw players with initials
    for (size_t p = 0; p < m_game->playerCount(); p++) {
        const Player &pl = m_game->playerAt(p);
        int pos = pl.getPos();

        if (pos < (int)tileLabels_.size()) {
            QString txt = tileLabels_[pos]->text();
            txt += "\n";
            txt += QString::fromStdString(pl.getName().substr(0,2));
            tileLabels_[pos]->setText(txt);
        }
    }

    // update balances list
    QString balances;
    for (size_t i = 0; i < m_game->playerCount(); i++) {
        const Player &pl = m_game->playerAt(i);
        balances += QString::fromStdString(pl.getName())
                  + ": "
                  + QString::number(pl.getMoney())
                  + " euro\n";
    }
    balancesBox_->setText(balances);
}

} // namespace pxl
