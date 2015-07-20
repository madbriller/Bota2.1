#ifndef MATCHMANAGER_H
#define MATCHMANAGER_H
#include "databasemanager.h"
#include <Qstring>
#include <QDate>

//gotta add dated functions

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
    static matchManager* instance();
    bool prepAllGamesByTeam(int teamID);
    bool prepAllGamesByVs(int team1ID, int team2ID);

    QString getMatchWinByTeam(int teamID); //returns as a percentage
    QString getGameWinByTeam(int teamID); //returns as a percentage
    QString getBoByNoAndTeam(int bestOfCount, int teamID); //returns as a percentage, takes 0 to not consider bestOfCount
    QString getDatedMatchWinByTeam(int teamID, int timeRange); //returns as a percentage, takes timeRange in days

    int getTotalMatchCount();

    bool hasRecords();
protected:
    matchManager();
    matchManager(const matchManager&);
    matchManager operator= (const matchManager&);
};

#endif // MATCHMANAGER_H
