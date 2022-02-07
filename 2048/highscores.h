#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class HighScores;
}

class HighScores : public QDialog
{
    Q_OBJECT

public:
    explicit HighScores(QWidget *parent = nullptr);
    ~HighScores();
    QStandardItemModel *Scorelistmodel= nullptr;
    void loadscores();

private:
    Ui::HighScores *ui;
};

#endif // HIGHSCORES_H
