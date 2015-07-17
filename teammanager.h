#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H
#include "databasemanager.h"
#include <QString>
#include <QStringList>

struct teamData{
    int teamID;
    QString teamName;
    QString teamLocation;
    int teamTier;
};

class teamManager
{
    QVector<teamData> currentTeamSet;
    teamData findTeam(QString teamName);
    teamData findTeam(int teamID);
    teamData noTeam();
public:
    bool addTeam(QString teamName, QString teamLocation, int teamTier);

    QStringList getTeamNameList();
    QString getTeamName(int teamID);
    QString getTeamLocation(int teamID);
    QString getTeamLocation(QString teamName);
    int getTeamTier(int teamID);
    int getTeamTier(QString teamName);
    int getTeamID(QString teamName);


    bool removeTeam(QString teamName);
    bool removeTeam(int teamID);

    void updateCurrentTeamSet();
    teamManager();
};

#endif // TEAMMANAGER_H
