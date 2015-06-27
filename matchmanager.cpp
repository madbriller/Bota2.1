#include "matchmanager.h"
#include <QMap>

bool matchManager::prepAllGamesByTeam(int teamID) {
    currentMatchSet.clear(); //Clear the current match set to make way for new records
    databaseManager* dbm = databaseManager::instance(); //get instance of database manager singleton

    QString theQuery("SELECT * FROM matches WHERE teamOne = "); //prepare the query string
    theQuery += QString::number(teamID);                           //probably better ways
    theQuery += " OR teamTwo = ";
    theQuery += QString::number(teamID) + ";";

    if (dbm->prepareAndExecQuery(theQuery) == true) { //execute query, and if successful..
        int rows = dbm->getRowCount();
        for (int ite=1;ite<=rows;ite++) { //iterate through all matches, creating a record
            QSqlRecord matchRecord = dbm->getNextRow();
            matchData currentMatch;
            currentMatch.team1ID = matchRecord.value(1).toInt();
            currentMatch.team2ID = matchRecord.value(2).toInt();
            currentMatch.winnerID = matchRecord.value(3).toInt();
            currentMatch.noOfGames = matchRecord.value(4).toInt();
            currentMatch.team1Wins = matchRecord.value(5).toInt();
            currentMatch.team1Wins = matchRecord.value(6).toInt();
            currentMatch.matchDate = QDate::fromString(matchRecord.value(7).toString());
            currentMatchSet.push_front(currentMatch); //create a record and push into storage
            return true;
        }
    }
    return false;
}

bool matchManager::prepAllGamesByVs(int team1ID, int team2ID) {

    currentMatchSet.clear(); //Clear the current match set to make way for new records
    databaseManager* dbm = databaseManager::instance(); //get instance of database manager singleton

    QString theQuery("SELECT * FROM matches WHERE (teamOne = "); //prepare the query string
    theQuery += QString::number(team1ID);   //probably better ways
    theQuery += " AND teamTwo = ";
    theQuery += QString::number(team2ID);
    theQuery += ") OR (teamOne = ";
    theQuery += QString::number(team2ID);
    theQuery += " AND teamTwo = ";
    theQuery += QString::number(team1ID);
    theQuery += ");";

    if (dbm->prepareAndExecQuery(theQuery) == true) { //execute query, and if successful..
        int rows = dbm->getRowCount();
        for (int ite=1;ite<=rows;ite++) { //iterate through all matches, creating a record
            QSqlRecord matchRecord = dbm->getNextRow();
            matchData currentMatch;
            currentMatch.team1ID = matchRecord.value(1).toInt();
            currentMatch.team2ID = matchRecord.value(2).toInt();
            currentMatch.winnerID = matchRecord.value(3).toInt();
            currentMatch.noOfGames = matchRecord.value(4).toInt();
            currentMatch.team1Wins = matchRecord.value(5).toInt();
            currentMatch.team1Wins = matchRecord.value(6).toInt();
            currentMatch.matchDate =  QDate::fromString(matchRecord.value(7).toString());
            currentMatchSet.push_front(currentMatch); //create a record and push into storage
            return true;
        }
    }
    return false;
}

int matchManager::getMatchWinByTeam(int teamID) {
    QMap<int,int> results;
    foreach(matchData currentMatch, currentMatchSet) {
        results[currentMatch.team1ID] += currentMatch.team1Wins;
        results[currentMatch.team2ID] += currentMatch.team2Wins;
    }
    return int((results[teamID] / currentMatchSet.size()) + 0.5); //0.5 for rounding

// old method, using branching rather than data
//    int matchCount, matchWinCount;
//    foreach(matchData &currentMatch, currentMatchSet) {
//        if (currentMatch.winnerID == teamID)
//            matchWinCount++;
//        matchCount++;
//    }
//    float winPercent = matchWinCount / matchCount;
//    return int(winPercent + 0.5;
}

int matchManager::getGameWinByTeam(int teamID){
    QMap<int,int> results;
    foreach(matchData currentMatch, currentMatchSet) {
        results[currentMatch.team1ID] += currentMatch.team1Wins;
        results[currentMatch.team2ID] += currentMatch.team2Wins;
    }
    return int((results[teamID] / currentMatchSet.size()) + 0.5); //0.5 for rounding

// old method, using branching rather than data
//    int gameCount, gameWinCount;
//    foreach (matchData &currentMatch, currentMatchSet){
//        if (currentMatch.team1ID == teamID) {
//            gameWinCount += currentMatch.team1Wins;
//        }
//        else if (currentMatch.team2ID == teamID) {
//            gameWinCount += currentMatch.team2Wins;
//        }
//        gameCount++;
//    }
//    float winPercent = gameWinCount / gameCount;
//    return int(winPercent + 0.5);
}

int matchManager::getBoByNoAndTeam(int bestOfCount, int teamID){
    QMap<int,int> results;
    int matchCount;
    foreach (matchData currentMatch, currentMatchSet) {
        if(currentMatch.noOfGames == bestOfCount) {
            results[currentMatch.team1ID] += currentMatch.team1Wins;
            results[currentMatch.team2ID] += currentMatch.team2Wins;
            matchCount++;
        }
    }
    return int((results[teamID] / matchCount) + 0.5); //0.5 for rounding
}

int matchManager::getTotalMatchCount(){
    return currentMatchSet.size();
}

bool matchManager::hasRecords()
{
    return !currentMatchSet.empty(); //returns inverse of empty
}

matchManager::matchManager()
{
}
