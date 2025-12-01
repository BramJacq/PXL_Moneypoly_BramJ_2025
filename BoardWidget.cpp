#include "BoardWidget.h"
#include <QVBoxLayout>
#include <QFont>
#include <QString>
#include <QThread>

using namespace pxl;

BoardWidget::BoardWidget(Game *game, QWidget *parent)
    : QWidget(parent), m_game(game), m_grid(nullptr), m_status(nullptr),
    m_rollBtn(nullptr), m_botTimer(nullptr), m_cols(7), m_rows(5)
{
    setWindowTitle("PXL Monopoly - Bram (blue) & bots (grey)");
    resize(900, 700);

    auto v = new QVBoxLayout(this);
    m_grid = new QGridLayout();
    v->addLayout(m_grid);

    m_status = new QLabel("Welcome to PXL Monopoly!");
    v->addWidget(m_status);

    m_rollBtn = new QPushButton("Roll (Bram) - click to start human turn");
    v->addWidget(m_rollBtn);

    // Timer used to auto-step bots every 350ms
    m_botTimer = new QTimer(this);
    m_botTimer->setInterval(350);
    connect(m_botTimer, &QTimer::timeout, this, &BoardWidget::onBotTimerTimeout);

    // Build the visual grid (perimeter + empty center)
    buildGrid(m_cols, m_rows);

    // connect button
    connect(m_rollBtn, &QPushButton::clicked, this, &BoardWidget::onRollClicked);

    // connect game change signal
    connect(m_game, &Game::boardChanged, this, &BoardWidget::updateUI);

    updateUI();
}

BoardWidget::~BoardWidget() = default;

void BoardWidget::buildGrid(size_t cols, size_t rows) {
    // clear any existing widgets in layout (if re-built)
    QLayoutItem *child;
    while ((child = m_grid->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // create labels for full rectangular grid but only perimeter are tiles
    m_tiles.clear();
    size_t totalCells = cols * rows;
    m_tiles.resize(totalCells, nullptr);

    QFont font;
    font.setPointSize(12);

    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            QLabel *lbl = new QLabel;
            lbl->setAlignment(Qt::AlignCenter);
            lbl->setFont(font);
            lbl->setMinimumSize(100, 80);
            // style center area different
            if (r > 0 && r + 1 < (int)rows && c > 0 && c + 1 < (int)cols) {
                lbl->setText(""); // empty center
                lbl->setStyleSheet("background: #222; border: 1px solid #222;"); // black center
            } else {
                // perimeter tile placeholder
                lbl->setText("Tile");
                lbl->setStyleSheet("background: white; border: 1px solid #444; color: black;");
            }
            m_tiles[r * cols + c] = lbl;
            m_grid->addWidget(lbl, (int)r, (int)c);
        }
    }
}

void BoardWidget::indexToGridPos(size_t index, int &row, int &col) const {
    // convert a perimeter index to (row,col) on the cols x rows grid clockwise
    // order used in Game::initPerimeterBoard was: top row L->R, right col top+1->bottom-1, bottom row R->L, left col bottom-1->top+1
    size_t cols = m_cols;
    size_t rows = m_rows;

    size_t topCount = cols;
    size_t rightCount = (rows > 2) ? (rows - 2) : 0;
    size_t bottomCount = cols;
    size_t leftCount = (rows > 2) ? (rows - 2) : 0;
    size_t perimeter = topCount + rightCount + bottomCount + leftCount;

    if (perimeter == 0) { row = 0; col = 0; return; }

    index = index % perimeter;

    if (index < topCount) {
        row = 0;
        col = (int)index;
        return;
    }
    index -= topCount;

    if (index < rightCount) {
        row = (int)(1 + index);
        col = (int)(cols - 1);
        return;
    }
    index -= rightCount;

    if (index < bottomCount) {
        row = (int)(rows - 1);
        col = (int)(cols - 1 - index);
        return;
    }
    index -= bottomCount;

    // left side
    row = (int)(rows - 1 - index);
    col = 0;
}

void BoardWidget::onRollClicked() {
    // Only allow clicking if current player is human
    if (!m_game->isCurrentPlayerHuman()) {
        // If it's not human's turn, ignore click
        return;
    }

    // disable button while human+bots sequence runs
    m_rollBtn->setEnabled(false);

    // Human does one roll and move
    m_game->humanRollOnce();

    // start bot timer - it will call advanceOneTurn repeatedly until it's human's turn again
    m_botTimer->start();
}

void BoardWidget::onBotTimerTimeout() {
    // If current player is human now, stop timer and re-enable button
    if (m_game->isCurrentPlayerHuman()) {
        m_botTimer->stop();
        m_rollBtn->setEnabled(true);
        return;
    }

    // otherwise ask game to advance one bot turn
    m_game->advanceOneTurn();

    // UI updates are triggered by Game::boardChanged signal -> updateUI slot runs
}

void BoardWidget::updateUI() {
    // fill perimeter tiles with names
    size_t cols = m_cols;
    size_t rows = m_rows;

    // set names for perimeter tiles using Game.tileAt()
    size_t perimeterCount = 0;
    if (cols >= 1 && rows >= 1) {
        size_t topCount = cols;
        size_t rightCount = (rows > 2) ? (rows - 2) : 0;
        size_t bottomCount = cols;
        size_t leftCount = (rows > 2) ? (rows - 2) : 0;
        perimeterCount = topCount + rightCount + bottomCount + leftCount;
    }

    // default clear all perimeter labels and style
    for (size_t idx = 0; idx < perimeterCount; ++idx) {
        int r, c;
        indexToGridPos(idx, r, c);
        QLabel *lbl = m_tiles[r * cols + c];
        if (lbl) {
            lbl->setText(QString::fromStdString(m_game->tileAt(idx).getName()));
            lbl->setStyleSheet("background: white; border: 1px solid #444; color: black;");
        }
    }

    // Clear players overlays: we will reapply
    // (If multiple players on same tile, names emojis appended)
    // Place players
    for (size_t pIdx = 0; pIdx < m_game->playerCount(); ++pIdx) {
        const Player &p = m_game->playerAt(pIdx);
        unsigned char pos = p.getPos();
        if (pos < perimeterCount) {
            int r, c;
            indexToGridPos(pos, r, c);
            QLabel *lbl = m_tiles[r * cols + c];
            if (lbl) {
                QString cur = lbl->text();
                QString emoji = p.isHuman() ? QStringLiteral(" 🧑‍🎓") : QStringLiteral(" 🤖");
                // colour the tile based on human or bot presence (human priority)
                if (p.isHuman()) {
                    lbl->setStyleSheet("background: #e6f0ff; border: 2px solid #1a73e8; color: black;");
                } else {
                    lbl->setStyleSheet("background: #f4f4f4; border: 1px solid #888; color: black;");
                }
                lbl->setText(cur + emoji + QString(" ") + QString::fromStdString(p.getName()));
            }
        }
    }

    // status: show money and whose turn it is
    QString status;
    for (size_t i = 0; i < m_game->playerCount(); ++i) {
        const Player &p = m_game->playerAt(i);
        status += QString::fromStdString(p.getName()) + ": " + QString::number(p.getMoney()) + "  ";
    }
    // indicate whose turn
    if (m_game->playerCount() > 0) {
        bool currentHuman = m_game->isCurrentPlayerHuman();
        status += currentHuman ? " | Current: Human" : " | Current: Bot";
    }
    m_status->setText(status);
}
