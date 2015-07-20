#include "databasemanager.h"

databaseManager::databaseManager()
{
    //default constructor uses default database connection details
    mainConnection =  QSqlDatabase::addDatabase("QSQLITE");
    mainConnection.setDatabaseName("data.db3");
    mainConnection.open();
    ready = false; //ready determines whether there is a query currently being stored
                   //not a description of connection status, possible ambiguity
}

databaseManager* databaseManager::instance() {
    static databaseManager m_instance;
    return &m_instance;

}

databaseManager::~databaseManager()
{
    mainConnection.close();
}

bool databaseManager::prepareAndExecQuery(QString queryString){
    delete currentQuery;
    currentQuery = NULL;
    currentQuery = new QSqlQuery(mainConnection);
    ready = currentQuery->exec(queryString);
    return ready;
}

QSqlRecord databaseManager::getCurrentRecord()
{
    return currentQuery->record();
}

bool databaseManager::next(){
    return currentQuery->next();
}

bool databaseManager::isQueryActive(){
    if (currentQuery != NULL) {
        return currentQuery->isActive();
    }
    return false;
}

bool databaseManager::isReady(){
    return ready;
}

