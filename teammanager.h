#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H
#include <QString>

struct teamData{
    QString teamName;
    QString teamLocation;
    int teamTier;
};

class teamManager
{
public:
    bool addTeam(QString teamName, QString teamLocation, int teamTier);
    bool prepTeamByID(int teamID);
    bool prepTeamByName(QString teamName);
    QString getCurrentTeamName();
    QString getCurrentTeamLocation();
    int getCurrentTeamTier();
    int getCurrentTeamID();
    int fetchIdByTeamName(); //does not overwrite current team set, just incase neccesary
    bool removeTeamByName(QString teamName);
    bool removeTeamByID(int teamID);
    bool hasTeam();
    teamManager();
};

#endif // TEAMMANAGER_H
