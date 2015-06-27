#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "QtSQL/QtSQL"

class databaseManager
{
private:
    QSqlDatabase mainConnection;
    QSqlQuery* currentQuery;
    bool ready;
    int rowCount;
public:
    int getRowCount();
    static databaseManager* instance();
    bool isReady();
    ~databaseManager();
    bool prepareAndExecQuery(QString queryString);
    QSqlQuery* getRefActiveQuery();
    QSqlRecord getNextRow();
    bool isQueryActive();
protected:
    databaseManager();
    databaseManager(const databaseManager&);
    databaseManager operator= (const databaseManager&);

};

#endif // DATABASEMANAGER_H
