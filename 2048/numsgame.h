#ifndef NUMSGAME_H
#define NUMSGAME_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <utility>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <vector>
#include <QKeyEvent>


namespace Ui {
class NumsGame;
}

class NumsGame : public QDialog
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event);

public:
    explicit NumsGame(QWidget *parent = nullptr);
    ~NumsGame();
      Ui::NumsGame *ui;

    QSqlDatabase db;
    QStringList scoreslisttoload;
    QStringList scoreslist;
    QVector<int> scoreslistnum;

    void setdatabase(QString nickname,  int score);
    void setMainBorder();
    void setinitialpos();
    QLabel * settile(int numberintile);
    std::pair<int, int> formrandpos();

    QVector<QVector<int>> numsMatrix;
    QVector< QVector<int>> oladboard;

    int score=0;
    int bscore=0;
    int oldscore;
    int diffscore=0;
    bool dontmove=0;

    void start();
    void getbestscore();
    void move_or_die();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void putOnnums();
    void reset();
    void gameOver();
    void winner();
    void ScoreAddedSayHi(int scoreadded);

private slots:
    void on_submit_clicked();

    void on_Quit_clicked();

    void on_newGame_clicked();

    void on_resetbutton_clicked();

    void on_Tryagain_clicked();

private:

};

#endif // NUMSGAME_H
