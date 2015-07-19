#include "bota2.h"
#include "ui_bota2.h"



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

    ui->lblTeamOneOverallGame->setText(mm->getGameWinByTeam(teamID) + "%");
    ui->lblTeamOneOverallMatch->setText(mm->getMatchWinByTeam(teamID) + "%");
}

void Bota2::updateTeamTwo(QString teamName)
{
    int teamID = tm->getTeamID(teamName);

    ui->lblTeamTwoLocation->setText(tm->getTeamLocation(teamName));
    ui->lblTeamTwoTier->setText(tm->getTeamTier(teamName));

    mm->prepAllGamesByTeam(teamID);

    ui->lblTeamTwoOverallGame->setText(mm->getGameWinByTeam(teamID) + "%");
    ui->lblTeamTwoOverallMatch->setText(mm->getMatchWinByTeam(teamID) + "%");
}

void Bota2::updateVS()
{

}
