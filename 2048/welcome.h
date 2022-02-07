#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Welcome; }
QT_END_NAMESPACE

class Welcome : public QDialog
{
    Q_OBJECT

public:
    Welcome(QWidget *parent = nullptr);
    ~Welcome();

private slots:
    void on_StartGame_clicked();

    void on_HIghScores_clicked();

private:
    Ui::Welcome *ui;
};
#endif // WELCOME_H
