#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QMainWindow>

namespace Ui {
class TicTacToe;
}

class TicTacToe : public QMainWindow
{   int turn;
    QString myState;
    QString myStateT;
    int V;
    Q_OBJECT

public:
    explicit TicTacToe(QMainWindow *parent = 0);
    ~TicTacToe();

private:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void clearState();

    QString checkWin();
    int MinMax();
    void Min();
    void Max();
    Ui::TicTacToe *ui;
    QRect rects[9];
    QLine lines[8];
};

#endif // TICTACTOE_H
