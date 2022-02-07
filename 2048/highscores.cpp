#include "highscores.h"
#include "ui_highscores.h"
#include "numsgame.h"
#include "ui_numsgame.h"

HighScores::HighScores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScores)
{
    ui->setupUi(this);
     Scorelistmodel = new QStandardItemModel;
        loadscores();
}

HighScores::~HighScores()
{
    delete ui;
}

void HighScores::loadscores()
{

    NumsGame newgame;

    newgame.db =QSqlDatabase::addDatabase("QSQLITE");
    newgame.db.setDatabaseName("/Users/pc/Desktop/scores_.sqlite");
    newgame.db.open();



    QSqlQuery scores("SELECT DISTINCT * from score  order by score desc",newgame.db);


    while(scores.next())
        newgame.scoreslisttoload.append("        "+scores.value(0).toString() + "                          " + scores.value(1).toString()+"");

    for(auto e :newgame.scoreslisttoload)
    {
        QString path{""};
        QIcon icon(path);
        ui->scoreview->setModel(Scorelistmodel);
        Scorelistmodel->appendRow(new QStandardItem(QIcon(icon),e));

    }



}
