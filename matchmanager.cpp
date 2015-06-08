#include "matchmanager.h"

void matchManager::prepAllGamesByTeam(int teamID) {
    currentMatchSet.clear(); //Clear the current match set to make way for new records
    databaseManager* dbm = databaseManager::instance(); //get instance of database manager singleton

    QString theQuery("SELECT * FROM matches WHERE teamOne = "); //prepare the query string
    theQuery += string(itoa(teamID));                           //probably better ways
    theQuery += " OR teamTwo = ";
    theQuery += string(itoa(teamID));

    if (dbm->prepareAndExecQuery(theQuery) == true) { //execute query, and if successful..
        int rows = dbm->getRowCount();
        for (int ite=1;ite<=rows;ite++) { //iterate through all matches creating
            QSqlRecord matchRecord = dbm->getNextRow();
            matchData currentMatch;
            currentMatch.matchDate =  QDate::fromString(query.value(7).toString());
            currentMatch.team1ID = matchRecord.value(1);
            currentMatch.team2ID = matchRecord.value(2);
            currentMatch.winnerID = matchRecord.value(3);
            currentMatch.noOfGames = matchRecord.value(4);
            currentMatch.team1Wins = matchRecord.value(5);
            currentMatch.team1Wins = matchRecord.value(6);
            currentMatchSet.push_front(currentMatch); //create a record and push into storage
        }
    }

}

matchManager::matchManager()
{
}
