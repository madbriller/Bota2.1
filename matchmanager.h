#ifndef MATCHMANAGER_H
#define MATCHMANAGER_H
#include "databasemanager.h"
#include <Qstring>
#include <QDate>


struct matchData{
    QDate matchDate;
    int team1ID;
    int team2ID;
    int noOfGames;
    int team1Wins;
    int team2Wins;
    int winnerID;


};

class matchManager
{
    QVector<matchData> currentMatchSet;

public:
    matchManager();
    void prepAllGamesByTeam(int teamID);
    void prepAllGamesByVs(int team1ID, int team2ID);
    int getMatchWinByTeam(int teamID); //returns as a percentage
    int getGameWinByTeam(int teamID); //returns as a percentage
    int getBoByNoAndTeam(int bestOfCount, int teamID); //returns as a percentage
    int getMatchCountByTeam(int teamID);
    int getTotalMatchCount();


};

#endif // MATCHMANAGER_H
