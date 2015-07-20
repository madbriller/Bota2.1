#include "addteam.h"
#include "ui_addteam.h"
#include "teammanager.h"

addTeam::addTeam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTeam)
{
    ui->setupUi(this);
}

addTeam::~addTeam()
{
    delete ui;
}

void addTeam::on_buttonAdd_clicked()
{
    teamManager *tm = teamManager::instance();
    tm->addTeam(ui->editName->text(),ui->editLocation->text(),ui->editTier->text());
    tm->updateCurrentTeamSet();
    this->close();
}

void addTeam::on_buttonCancel_clicked()
{
    this->close();
}
