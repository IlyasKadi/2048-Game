#include "welcome.h"
#include "ui_welcome.h"
#include "numsgame.h"
#include "highscores.h"

Welcome::Welcome(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}


void Welcome::on_StartGame_clicked()
{
    NumsGame newgame;
    newgame.exec();

}

void Welcome::on_HIghScores_clicked()
{
    HighScores highscoreslist;
    highscoreslist.exec();
}
