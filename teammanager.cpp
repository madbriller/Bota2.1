#include "teammanager.h"

teamManager::teamManager()
{
}

bool teamManager::addTeam(QString teamName, QString teamLocation, int teamTier){
    databaseManager* dbm = databaseManager::instance();

    QString theQuery("INSERT INTO teams VALUES (");
    theQuery += teamName + ",";
    theQuery += teamTier + ",";
    theQuery += teamLocation + ");";
    return dbm->prepareAndExecQuery(theQuery);
}

bool teamManager::prepTeamByID(int teamID) {
    databaseManager* dbm = databaseManager::instance(); //get instance of database manager singleton

    QString theQuery("SELECT * FROM teams WHERE teamID = ");
    theQuery += QString::number(teamID) + ";";

    if (dbm->prepareAndExecQuery(theQuery) == true) {
        QSqlRecord teamRecord = dbm->getNextRow();
        currentTeam.teamID = teamRecord.value(0).toInt();
        currentTeam.teamName = teamRecord.value(1).toString();
        currentTeam.teamTier = teamRecord.value(2).toInt();
        currentTeam.teamLocation = teamRecord.value(3).toString();
        return true;
    }
    return false;
}

bool teamManager::prepTeamByName(QString teamName) {
    databaseManager* dbm = databaseManager::instance(); //get instance of database manager singleton

    QString theQuery("SELECT * FROM teams WHERE teamName = '");
    theQuery += teamName + "';";

    if (dbm->prepareAndExecQuery(theQuery) == true) {
        QSqlRecord teamRecord = dbm->getNextRow();
        currentTeam.teamID = teamRecord.value(0).toInt();
        currentTeam.teamName = teamRecord.value(1).toString();
        currentTeam.teamTier = teamRecord.value(2).toInt();
        currentTeam.teamLocation = teamRecord.value(3).toString();
        return true;
    }
    return false;
}

QString teamManager::getCurrentTeamName(){
    return currentTeam.teamName;
}

QString teamManager::getCurrentTeamLocation(){
    return currentTeam.teamLocation;
}

int teamManager::getCurrentTeamTier(){
    return currentTeam.teamTier;
}

int teamManager::getCurrentTeamID(){
    return currentTeam.teamID;
}

int teamManager::fetchIdByTeamName(QString teamName){
    databaseManager* dbm = databaseManager::instance();

    QString theQuery("SELECT * FROM teams WHERE teamName = '");
    theQuery += teamName + "';";
    if(dbm->prepareAndExecQuery(theQuery)) {
        QSqlRecord teamRecord = dbm->getNextRow();
        return teamRecord.value(0).toInt();
    }
    return -1;
}

bool teamManager::removeTeamByName(QString teamName) {
    databaseManager* dbm = databaseManager::instance();

    QString theQuery("REMOVE FROM teams WHERE teamName = '");
    theQuery += teamName +"';";

    return dbm->prepareAndExecQuery(theQuery);

}

bool teamManager::removeTeamByID(int teamID) {
    databaseManager* dbm = databaseManager::instance();

    QString theQuery("REMOVE FROM teams WHERE teamID = ");
    theQuery += teamID +";";

    return dbm->prepareAndExecQuery(theQuery);

}
