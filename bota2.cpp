#include "bota2.h"
#include "ui_bota2.h"
#include "addteam.h"




void Bota2::updateTeamOneInfo()
{

}

Bota2::Bota2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bota2)
{
    mm = matchManager::instance();
    tm = teamManager::instance();
    ui->setupUi(this);
    ui->comboTeamOne->insertItems(0,teamManager::instance()->getTeamNameList());
    ui->comboTeamTwo->insertItems(0,teamManager::instance()->getTeamNameList());
}

Bota2::~Bota2()
{
    delete ui;

}

void Bota2::on_comboTeamOne_currentIndexChanged(const QString &teamName)
{
    updateTeamOne(teamName);
    updateVS();
}

void Bota2::on_comboTeamTwo_currentIndexChanged(const QString &teamName)
{
    updateTeamTwo(teamName);
    updateVS();
}

void Bota2::updateTeamOne(QString teamName)
{
    int teamID = tm->getTeamID(teamName);

    ui->lblTeamOneLocation->setText(tm->getTeamLocation(teamName));
    ui->lblTeamOneTier->setText(tm->getTeamTier(teamName));

    mm->prepAllGamesByTeam(teamID);

    ui->lblTeamOneOverallGame->setText(mm->getGameWinByTeam(teamID));
    ui->lblTeamOneOverallMatch->setText(mm->getMatchWinByTeam(teamID));

    updateVS();
}

void Bota2::updateTeamTwo(QString teamName)
{
    int teamID = tm->getTeamID(teamName);

    ui->lblTeamTwoLocation->setText(tm->getTeamLocation(teamName));
    ui->lblTeamTwoTier->setText(tm->getTeamTier(teamName));

    mm->prepAllGamesByTeam(teamID);

    ui->lblTeamTwoOverallGame->setText(mm->getGameWinByTeam(teamID));
    ui->lblTeamTwoOverallMatch->setText(mm->getMatchWinByTeam(teamID));

    updateVS();
}

void Bota2::updateVS()
{
    int teamOne = tm->getTeamID(ui->comboTeamOne->currentText());
    int teamTwo = tm->getTeamID(ui->comboTeamTwo->currentText());

    int timeRange;
    switch (ui->comboVersusTime->currentIndex()) {
    case 0:
    default:
        timeRange = 0;
        break;
    case 1:
        timeRange = 7;
        break;
    case 2:
        timeRange = 14;
        break;
    case 3:
        timeRange = 28;
        break;
    case 4:
        timeRange = 168;
        break;
    }

    mm->prepAllGamesByVs(teamOne,teamTwo);

    ui->lblVSTeamOneBO1->setText(mm->getBoByNoAndTeam(1,teamOne));
    ui->lblVSTeamTwoBO1->setText(mm->getBoByNoAndTeam(1,teamTwo));
    ui->lblVSTeamOneBO2->setText(mm->getBoByNoAndTeam(2,teamOne));
    ui->lblVSTeamTwoBO2->setText(mm->getBoByNoAndTeam(2,teamTwo));
    ui->lblVSTeamOneBO3->setText(mm->getBoByNoAndTeam(3,teamOne));
    ui->lblVSTeamTwoBO3->setText(mm->getBoByNoAndTeam(3,teamTwo));
    ui->lblVSTeamOneBO5->setText(mm->getBoByNoAndTeam(5,teamOne));
    ui->lblVSTeamTwoBO5->setText(mm->getBoByNoAndTeam(5,teamTwo));
    ui->lblVSTeamOneOverall->setText(mm->getMatchWinByTeam(teamOne));
    ui->lblVSTeamTwoOverall->setText(mm->getMatchWinByTeam(teamTwo));

}

void Bota2::on_actionAdd_Quick_triggered()
{
    addTeam addTeamWindow;
    addTeamWindow.setModal(true);
    addTeamWindow.exec();

}
