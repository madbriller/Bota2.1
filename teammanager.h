#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H
#include "databasemanager.h"
#include <QString>

struct teamData{
    int teamID;
    QString teamName;
    QString teamLocation;
    int teamTier;
};

class teamManager
{
    teamData currentTeam;
public:
    bool addTeam(QString teamName, QString teamLocation, int teamTier);
    bool prepTeamByID(int teamID);
    bool prepTeamByName(QString teamName);

    QString getCurrentTeamName();
    QString getCurrentTeamLocation();
    int getCurrentTeamTier();
    int getCurrentTeamID();

    int fetchIdByTeamName(QString teamName); //does not overwrite current team set, just incase neccesary

    bool removeTeamByName(QString teamName);
    bool removeTeamByID(int teamID);

    teamManager();
};

#endif // TEAMMANAGER_H
