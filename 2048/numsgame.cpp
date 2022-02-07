#include "numsgame.h"
#include "ui_numsgame.h"
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QMessageBox>



NumsGame::NumsGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumsGame)
{
    ui->setupUi(this);
    start();
}

void NumsGame::start()
{
    this->setFixedSize(this->geometry().width(),this->geometry().height());
    getbestscore();
    setMainBorder();
}



NumsGame::~NumsGame()
{
    delete ui;
}

 void NumsGame::getbestscore()
 {
     db =QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("/Users/pc/Desktop/scores_.sqlite");
     db.open();
     QSqlQuery scores("SELECT * from score ",db);

     while(scores.next())
         scoreslist.append(scores.value(1).toString()+"");


   for(QString e: scoreslist)
        scoreslistnum.push_back(e.toInt());

      ui->BEST_SCORE_N->setText(QString::number(scoreslistnum[scoreslistnum.size()-1]));


 }


//Design of tile based on each number
QLabel * NumsGame:: settile(int numberintile)
{

       QString labelNum = QString::number(numberintile);
       QLabel *tile = new QLabel(labelNum);
       tile->setAlignment(Qt::AlignCenter);


        switch (numberintile) {
        case 2: {

            tile->setStyleSheet("background: rgb(238,228,218);" "color: rgb(119,110,101);" "font: bold; border-radius: 10px; font: 22pt;");

            break;
        }
        case 4: {
           tile->setStyleSheet("background: rgb(237,224,200);" "color: rgb(119,110,101);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 8: {
           tile->setStyleSheet("background: rgb(242,177,121);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 16: {
            tile->setStyleSheet("background: rgb(245,150,100);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 32: {
            tile->setStyleSheet("background: rgb(245,125,95);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 64: {
            tile->setStyleSheet("background: rgb(245,95,60);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 128: {
            tile->setStyleSheet("background: rgb(237,207,114);" "color: rgb(255,255,255);" "font: bold;" "border-radius: 10px; font: 22pt;");
            break;
        }
        case 256: {
            tile->setStyleSheet("background: rgb(237,204,97);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 512: {
            tile->setStyleSheet("background: rgb(237,204,97);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 1024: {
            tile->setStyleSheet("background: rgb(237,204,97);" "color: rgb(255,255,255);" "font: bold; border-radius: 10px; font: 22pt;");
            break;
        }
        case 2048: {
            QGraphicsDropShadowEffect *dse = new QGraphicsDropShadowEffect();
            dse->setColor(Qt::yellow);
            dse->setBlurRadius(50);
            dse->setOffset(-1);
            tile->setGraphicsEffect(dse);
            tile->setStyleSheet("background: rgb(237,204,97);"  "color: rgb(255,255,255); font: bold;" "border-radius: 10px; font: 22pt;");
            break;
        }
        default: {
             tile = new QLabel();
            tile->setStyleSheet("background: rgb(205,192,180);" "border-radius: 10px;" "color: rgb(119,110,101);");




            break;
        }

}
return tile;



}
void NumsGame::putOnnums()
{

    for(int i=0; i<4 ;i++)
    {
        for(int j=0; j<4 ;j++)
        {
            ui->gridboard->addWidget(settile(0),i,j);
        }
    }


    for(int i=0; i<4 ;i++)
    {
        for(int j=0; j<4 ;j++)
        {
            if(numsMatrix[i][j]!=0)
            ui->gridboard->addWidget(settile(numsMatrix[i][j]),i,j);
        }
    }

}
//Forming a random position
std::pair<int, int> NumsGame::formrandpos()
{
    int randi = rand() % 4;
    int randj = rand() % 4;
     return std::make_pair(randj, randi);
}

//Setting up two first tiles to start with
void NumsGame::setinitialpos()
{
        auto [rndi,rndj]=formrandpos();
        auto [rndi_,rndj_]=formrandpos();


      numsMatrix[rndi][rndj]=2;
      numsMatrix[rndi_][rndj_]=2;

     ui->gridboard->addWidget(settile(2),rndi,rndi);
     ui->gridboard->addWidget(settile(2),rndi_,rndj_);



}
//Setting up base view
void NumsGame::setMainBorder()
{
    numsMatrix.resize(4);
    for (int i = 0; i < 4; i++)
        numsMatrix[i].resize(4);
    for (int i = 0; i < 4; i++)
         for (int j = 0; j < 4;j++)
            numsMatrix[i][j]=0;

    ui->gameoverlabel->hide();
    ui->winner->hide();
    ui->Tryagain->hide();
    ui->newGame->hide();
    ui->Quit->hide();
    ui->lastScore->hide();
    ui->youreScore->hide();
    ui->nicknamelabel->hide();
    ui->Nickname->hide();
    ui->submit->hide();

for (int i = 0; i < 4; ++i) {
   for (int j = 0; j < 4; ++j) {

        QLabel *label = new QLabel();

         label->setStyleSheet("background: rgb(205,192,180);" "border-radius: 10px;" "color: rgb(119,110,101);" );

         label->setAlignment(Qt::AlignCenter);
         ui->gridboard->addWidget(label,i,j);

   }

}
 setinitialpos();
}
void NumsGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
   {
        if(dontmove==0)
       {
            case Qt::Key_Up:
           {
                moveUp();
                ui->resetbutton->setEnabled(1);
                break;
           }
           case Qt::Key_Left:
           {
                moveLeft();
                ui->resetbutton->setEnabled(1);
                break;

            }
            case Qt::Key_Right:
           {
                moveRight();
                ui->resetbutton->setEnabled(1);
                break;

           }
            case Qt::Key_Down:
           {
                moveDown();
                ui->resetbutton->setEnabled(1);
                break;
           }
       }

   }
}

void NumsGame::moveUp()
{
    oldscore=score;
    diffscore=0;
    oladboard=numsMatrix;


    //this is a space remover phase

    for (int j = 0; j < 4; j++)
    {
        for (int i = 1; i < 4; i++)
        {
                 if (numsMatrix[i][j] != 0)
                {
                     for(int k=0;k<i;k++)
                     {
                       if (numsMatrix[k][j] == 0)
                      {
                        numsMatrix[k][j]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                      }
                  }
             }
        }
    }

 //this is the sum phase (and so on concerning other dorections)
    for (int j = 0; j < 4; j++)
   {

          for (int i = 1; i < 4; i++)
        {

                 if (numsMatrix[i][j] != 0)
                {
                     if(numsMatrix[i-1][j] == numsMatrix[i][j] )
                    {
                         numsMatrix[i-1][j]=numsMatrix[i][j]*2;
                         score+=numsMatrix[i-1][j];
                         numsMatrix[i][j]=0;

                     }


                }
        }

    }
    //this is another space remover phase (and the same for other dorections)

    for (int j = 0; j < 4; j++)
      {

          for (int i = 1; i < 4; i++)
        {

                 if (numsMatrix[i][j] != 0)
                {
                     for(int k=0;k<i;k++)
                     {
                         if (numsMatrix[k][j] == 0)
                         {
                              numsMatrix[k][j]=numsMatrix[i][j];
                              numsMatrix[i][j]=0;
                         }


                     }


                 }
         }
      }

    putOnnums();
    move_or_die();
    diffscore=score-oldscore;
    if(diffscore >0 ){ ScoreAddedSayHi(diffscore);};


}



void NumsGame::moveDown()
{
    oldscore=score;
    diffscore=0;
    oladboard=numsMatrix;

    for(int j=0;j<4;j++)
    {
        for(int i=2;i>=0;i--)
        {
            if(numsMatrix[i][j]!=0)
            {
                for(int k=3;k>i;k--)
                {
                    if(numsMatrix[k][j]==0)
                    {
                        numsMatrix[k][j]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                    }
                }
            }
        }
    }

    for(int j=0;j<4;j++)
    {
        for(int i=2;i>=0;i--)
        {
            if(numsMatrix[i][j]!=0)
            {
               if(numsMatrix[i+1][j]==numsMatrix[i][j])
                {
                   numsMatrix[i+1][j]=numsMatrix[i][j]*2;
                   score+=numsMatrix[i+1][j];
                   numsMatrix[i][j]=0;
                }
           }
         }
     }

    for(int j=0;j<4;j++)
    {
        for(int i=2;i>=0;i--)
        {
            if(numsMatrix[i][j]!=0)
            {
                for(int k=3;k>i;k--)
                {
                    if(numsMatrix[k][j]==0)
                    {
                        numsMatrix[k][j]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                    }
                }
            }
        }
    }


    putOnnums();
    move_or_die();
    diffscore=score-oldscore;
    if(diffscore >0 ){ ScoreAddedSayHi(diffscore);};

}


void NumsGame::moveRight()
{
   oldscore=score;
   diffscore=0;
   oladboard=numsMatrix;

    for(int i=0;i<4;i++)
    {
        for(int j=2;j>=0;j--)
        {
            if(numsMatrix[i][j]!=0)
            {
               for(int k=3;k>j;k--)
                {
                    if(numsMatrix[i][k]==0)
                    {
                        numsMatrix[i][k]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                    }

                }
            }
        }
    }

    for(int i=0;i<4;i++)
    {
        for(int j=2;j>=0;j--)
        {
            if(numsMatrix[i][j]!=0)
            {
               if(numsMatrix[i][j+1]==numsMatrix[i][j] )
               {
                   numsMatrix[i][j+1]=numsMatrix[i][j]*2;
                   score+=numsMatrix[i][j+1];
                   numsMatrix[i][j]=0;
               }
            }
        }
    }

    for(int i=0;i<4;i++)
    {
        for(int j=2;j>=0;j--)
        {
            if(numsMatrix[i][j]!=0)
            {
                for(int k=3;k>j;k--)
                {
                    if(numsMatrix[i][k]==0)
                    {
                        numsMatrix[i][k]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                    }
                }
            }
        }
    }


    putOnnums();
    move_or_die();
    diffscore=score-oldscore;
    if(diffscore >0 ){ ScoreAddedSayHi(diffscore);};


}
void NumsGame::moveLeft()
{

    oldscore=score;
    diffscore=0;
    oladboard=numsMatrix;

    for(int i=0;i<4;i++)
    {
        for(int j=1;j<4;j++)
        {
            if(numsMatrix[i][j]!=0)
            {
                for(int k=0;k<j;k++)
                {
                    if(numsMatrix[i][k]==0)
                    {
                        numsMatrix[i][k]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                    }
                }
            }
        }
    }

    for(int i=0;i<4;i++)
    {
        for(int j=1;j<4;j++)
        {
            if(numsMatrix[i][j]!=0)
            {
                if(numsMatrix[i][j-1]==numsMatrix[i][j] )
                {
                    numsMatrix[i][j-1]=numsMatrix[i][j]*2;
                    score+=numsMatrix[i][j-1];
                    numsMatrix[i][j]=0;
                }
            }
        }
  }

    for(int i=0;i<4;i++)
    {
        for(int j=1;j<4;j++)
        {
            if(numsMatrix[i][j]==0)
            {
                for(int k=0;k<j;k++)
                {
                    if(numsMatrix[i][k]==0)
                    {
                        numsMatrix[i][k]=numsMatrix[i][j];
                        numsMatrix[i][j]=0;
                    }
                }
            }
        }
    }

    putOnnums();
    move_or_die();
    diffscore=score-oldscore;
    if(diffscore >0 ){ ScoreAddedSayHi(diffscore);};

}
void NumsGame:: move_or_die()
{
    int c=0;

    //No_Tile_Left loop check
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4;j++)
        {
            if( numsMatrix[i][j]==0)
           {
              c++;
           }
        }
    }


    //No_Sum_possible_ loop check by cols
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3;j++)
        {
            if( numsMatrix[i][j]== numsMatrix[i][j+1])
           {
              c++;
           }
        }
    }
    //No_Sum_possible_ loop check by rows
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3;i++)
        {
            if( numsMatrix[i][j]== numsMatrix[i+1][j])
           {
              c++;
           }
        }
    }


    //Win loop check
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4;j++)
        {
            if( numsMatrix[i][j]==2048)
           {
              winner();
             dontmove=1;
           }
        }
    }

    //condition that check if next move is possible :
    if( oladboard!=numsMatrix) //movement possible
    {
       //updating score:
        ui->Score_N->setText(QString::number(score));
        if(ui->BEST_SCORE_N->text().toInt()<=score)
        {
            bscore=score;
             ui->BEST_SCORE_N->setText(QString::number(score));
        }


        //making a rand free position
        std:: pair<int, int> randpos =formrandpos();
        do {
            randpos =formrandpos();

        } while (numsMatrix[randpos.first][randpos.second] != 0);



        //to add a new tile in it:
        numsMatrix[randpos.first][randpos.second]=2 ;
        ui->gridboard->addWidget(settile(2),randpos.first,randpos.second);

    }
    else if(oladboard==numsMatrix && c==0) // movement impossible you're dead +_+
    {
        gameOver();
        dontmove=1;

    }
    // otherwise do nothing (won't add a tile)


}
void NumsGame::ScoreAddedSayHi(int i)
{
    ui->scoreadded->setText("+"+QString::number(i));
    ui->scoreadded->show();
    QTimer::singleShot(500, ui->scoreadded, &QLabel::hide);

}

void NumsGame::reset()
{
    score=0;
   for(int i=0; i<4 ;i++)
   {
       for(int j=0; j<4 ;j++)
       {

                ui->gridboard->addWidget(settile(0),i,j);
       }
   }
   numsMatrix.resize(4);
   for (int i = 0; i < 4; i++)
       numsMatrix[i].resize(4);
   for (int i = 0; i < 4; i++)
       for (int j = 0; j < 4;j++)
           numsMatrix[i][j]=0;


   setinitialpos();

   ui->resetbutton->setEnabled(0);

   ui->gameoverlabel->hide();
   ui->gameoverlabel->setEnabled(0);

   ui->Score_N->setText("0");
   ui->scoreadded->setEnabled(0);

   ui->Tryagain->hide();
   ui->Tryagain->setEnabled(0);

   ui->newGame->hide();
   ui->newGame->setEnabled(0);

   ui->winner->hide();
   ui->winner->setEnabled(0);

   ui->Quit->hide();
   ui->Quit->setEnabled(0);

   ui->lastScore->hide();
   ui->lastScore->setEnabled(0);

   ui->youreScore->hide();
   ui->youreScore->setEnabled(0);

   ui->nicknamelabel->hide();
   ui->nicknamelabel->setEnabled(0);

   ui->Nickname->hide();
   ui->Nickname->setEnabled(0);

   ui->submit->hide();
   ui->submit->setEnabled(0);

      dontmove=0;


}
void NumsGame::gameOver()
{
    ui->gameoverlabel->setEnabled(1);
    ui->gameoverlabel->show();

    ui->gameoverlabel->setEnabled(1);
    ui->gameoverlabel->show();

    ui->Tryagain->show();
    ui->Tryagain->setEnabled(1);

    ui->lastScore->setText(QString::number(score));
    ui->lastScore->show();
    ui->lastScore->setEnabled(1);

    ui->youreScore->show();
    ui->youreScore->setEnabled(1);

    ui->nicknamelabel->show();
    ui->nicknamelabel->setEnabled(1);

    ui->Nickname->show();
    ui->Nickname->setEnabled(1);

    ui->submit->show();
    ui->submit->setEnabled(1);

}


void NumsGame::winner()
{
    ui->newGame->show();
    ui->newGame->setEnabled(1);

    ui->Quit->setEnabled(1);
    ui->Quit->show();

    ui->winner->show();
    ui->winner->setEnabled(1);


    ui->lastScore->setText(QString::number(score));
    ui->lastScore->setEnabled(1);
    ui->lastScore->show();

    ui->youreScore->show();
    ui->youreScore->setEnabled(1);

    ui->nicknamelabel->show();
    ui->nicknamelabel->setEnabled(1);

    ui->Nickname->setEnabled(1);
    ui->Nickname->show();

    ui->submit->show();
    ui->submit->setEnabled(1);


}

void NumsGame::setdatabase(QString nickname,  int score)
{
    db =QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("/Users/pc/Desktop/scores_.sqlite");
    db.open();

      QSqlQuery query(db);


    QString create {"CREATE TABLE IF NOT EXISTS score (name VARCHAR(80), score int)"};
    if(!query.exec(create))
    {
        QMessageBox::critical(this,"info","could not create table");

    }


    QString insert {"INSERT INTO score values ('%1','%2')"};
    if(!query.exec(insert.arg(nickname).arg(score)))
    {
        QMessageBox::critical(this,"info","insert not create table");
    }


}




void NumsGame::on_submit_clicked()
{


   setdatabase(ui->Nickname->text(),score);

   reset();
   ui->Nickname->setText("");

}

void NumsGame::on_Quit_clicked()
{
    close();
}

void NumsGame::on_newGame_clicked()
{
    reset();


}

void NumsGame::on_resetbutton_clicked()
{
    reset();

}

void NumsGame::on_Tryagain_clicked()
{
    reset();

}
