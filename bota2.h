#ifndef BOTA2_H
#define BOTA2_H

#include <QMainWindow>
#include "matchmanager.h"
#include "teammanager.h"

namespace Ui {
class Bota2;
}

class Bota2 : public QMainWindow
{
    Q_OBJECT

public:
    void updateTeamOneInfo();
    void updateTeamTwoInfo();
    void updateVSInfo();
    explicit Bota2(QWidget *parent = 0);
    ~Bota2();

private slots:
    void on_comboTeamOne_currentIndexChanged(const QString &arg1);
    void on_comboTeamTwo_currentIndexChanged(const QString &arg1);
private:
    matchManager* mm;
    teamManager* tm;
    void updateTeamOne(QString teamName);
    void updateTeamTwo(QString teamName);
    void updateVS();
    Ui::Bota2 *ui;
};

#endif // BOTA2_H
