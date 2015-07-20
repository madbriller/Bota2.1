#include "matchmanager.h"
#include <QMap>

matchManager::matchManager()
{
}

matchManager* matchManager::instance() {
    static matchManager m_instance;
    return &m_instance;

}

bool matchManager::prepAllGamesByTeam(int teamID) {
    currentMatchSet.clear(); //Clear the current match set to make way for new records
    databaseManager* dbm = databaseManager::instance(); //get instance of database manager singleton

    QString theQuery("SELECT * FROM matches WHERE teamOne = "); //prepare the query string
    theQuery += QString::number(teamID);                           //probably better ways
    theQuery += " OR teamTwo = ";
    theQuery += QString::number(teamID) + ";";

    if (dbm->prepareAndExecQuery(theQuery) == true) { //execute query, and if successful..
       while(dbm->next()) { //iterate through all matches, creating a record
            QSqlRecord matchRecord = dbm->getCurrentRecord();
            matchData currentMatch;
            currentMatch.team1ID = matchRecord.value(1).toInt();
            currentMatch.team2ID = matchRecord.value(2).toInt();
            currentMatch.winnerID = matchRecord.value(3).toInt();
            currentMatch.noOfGames = matchRecord.value(4).toInt();
            currentMatch.team1Wins = matchRecord.value(5).toInt();
            currentMatch.team2Wins = matchRecord.value(6).toInt();
            currentMatch.matchDate = QDate::fromString(matchRecord.value(7).toString());
            currentMatchSet.push_front(currentMatch); //create a record and push into storage
        }
       return true;
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
        while(dbm->next()) { //iterate through all matches, creating a record
            QSqlRecord matchRecord = dbm->getCurrentRecord();
            matchData currentMatch;
            currentMatch.team1ID = matchRecord.value(1).toInt();
            currentMatch.team2ID = matchRecord.value(2).toInt();
            currentMatch.winnerID = matchRecord.value(3).toInt();
            currentMatch.noOfGames = matchRecord.value(4).toInt();
            currentMatch.team1Wins = matchRecord.value(5).toInt();
            currentMatch.team1Wins = matchRecord.value(6).toInt();
            currentMatch.matchDate =  QDate::fromString(matchRecord.value(7).toString());
            currentMatchSet.push_front(currentMatch); //create a record and push into storage 
        }
        return true;
    }
    return false;
}

QString matchManager::getMatchWinByTeam(int teamID) { //returns wins as a function of overall matches played
    QMap<int,float> results;
    if (currentMatchSet.size() == 0) return "N/A";
    foreach(matchData currentMatch, currentMatchSet) {
        results[currentMatch.winnerID]+=1;
    }
    float percent = (results[teamID] / currentMatchSet.size()) *100;
    QString ret = QString::number(percent);
    ret.truncate(5);
    ret += "%";
    return ret;

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

QString matchManager::getGameWinByTeam(int teamID){ //returns wins as a function of overall single games played
    QMap<int,float> results;
    int gameCount = 0;
    foreach(matchData currentMatch, currentMatchSet) {
        results[currentMatch.team1ID] += currentMatch.team1Wins;
        results[currentMatch.team2ID] += currentMatch.team2Wins;
        gameCount += currentMatch.team1Wins + currentMatch.team2Wins;
    }
    if (gameCount == 0) return "N/A";
    float percent = (results[teamID] / gameCount) * 100;
    QString ret = QString::number(percent);
    ret.truncate(5);
    ret += "%";
    return ret;

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

QString matchManager::getBoByNoAndTeam(int bestOfCount, int teamID){
    QMap<int,float> results;
    int matchCount=0;
    foreach (matchData currentMatch, currentMatchSet) {
        if(currentMatch.noOfGames == bestOfCount) {
          //  QDate currentMatchDate = QDate::fromString(currentMatch.matchDate);
            results[currentMatch.winnerID] += 1;
            matchCount++;
        }
    }
    if (matchCount == 0) return "N/A";
    float percent = (results[teamID] / matchCount) * 100;
    QString ret = QString::number(percent);
    ret.truncate(5);
    ret += "%";
    return ret;
}

int matchManager::getTotalMatchCount(){
    return currentMatchSet.size();
}

bool matchManager::hasRecords()
{
    return !currentMatchSet.empty(); //returns inverse of empty
}

