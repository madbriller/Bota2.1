#include "teammanager.h"

teamManager::teamManager()
{
    updateCurrentTeamSet();
}

teamManager* teamManager::instance() {
    static teamManager m_instance;
    return &m_instance;

}

bool teamManager::addTeam(QString teamName, QString teamLocation, QString teamTier){
    databaseManager* dbm = databaseManager::instance();
    bool success = false;
    if (findTeam(teamName).teamID == -1) {
        QString theQuery("INSERT INTO teams (teamName,teamTier,teamLocation) VALUES ('");
        theQuery += teamName + "','";
        theQuery += teamTier + "','";
        theQuery += teamLocation + "');";
        success = dbm->prepareAndExecQuery(theQuery);
        updateCurrentTeamSet();
    }
    return success;
}

teamData teamManager::noTeam() {
    teamData noTeam;
    noTeam.teamLocation = "noTeam";
    noTeam.teamName = "noTeam";
    noTeam.teamID = -1;
    noTeam.teamTier = -1;
    return noTeam;
}

teamData teamManager::findTeam(int teamID) {
    foreach(teamData currentTeam, currentTeamSet) {
        if (currentTeam.teamID == teamID) return currentTeam;
    }
    return noTeam();
}

teamData teamManager::findTeam(QString teamName) {
    foreach(teamData currentTeam, currentTeamSet) {
        if (currentTeam.teamName == teamName) return currentTeam;
    }
    return noTeam();
}

QStringList teamManager::getTeamNameList() {
    QStringList teamNameList;
    foreach (teamData currentTeam, currentTeamSet) {
        teamNameList.push_back(currentTeam.teamName);
    }
    return teamNameList;
}

QString teamManager::getTeamName(int teamID) {
    return findTeam(teamID).teamName;
}

QString teamManager::getTeamLocation(int teamID) {
    return findTeam(teamID).teamLocation;
}

QString teamManager::getTeamLocation(QString teamName) {
    return findTeam(teamName).teamLocation;
}

QString teamManager::getTeamTier(int teamID) {
    return QString::number(findTeam(teamID).teamTier);
}

QString teamManager::getTeamTier(QString teamName) {
    return QString::number(findTeam(teamName).teamTier);
}

int teamManager::getTeamID(QString teamName) {
    return findTeam(teamName).teamID;
}


bool teamManager::removeTeam(QString teamName) {
    databaseManager* dbm = databaseManager::instance();

    QString theQuery("REMOVE FROM teams WHERE teamName = '");
    theQuery += teamName +"';";
    bool success = dbm->prepareAndExecQuery(theQuery);

    updateCurrentTeamSet();
    return success;


}

bool teamManager::removeTeam(int teamID) {
    databaseManager* dbm = databaseManager::instance();

    QString theQuery("REMOVE FROM teams WHERE teamID = ");
    theQuery += teamID +";";
    bool success = dbm->prepareAndExecQuery(theQuery);

    updateCurrentTeamSet();
    return success;

}

void teamManager::updateCurrentTeamSet() {
    databaseManager* dbm = databaseManager::instance();

    currentTeamSet.clear();

    QString theQuery("SELECT * FROM teams");
    dbm->prepareAndExecQuery(theQuery);

    while(dbm->next()){
        QSqlRecord teamRecord = dbm->getCurrentRecord();
        teamData currentTeam;
        currentTeam.teamID = teamRecord.value(0).toInt();
        currentTeam.teamName = teamRecord.value(1).toString();
        currentTeam.teamTier = teamRecord.value(2).toInt();
        currentTeam.teamLocation = teamRecord.value(3).toString();
        currentTeamSet.push_back(currentTeam);
   }
}
