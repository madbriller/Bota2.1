#include "databasemanager.h"

databaseManager::databaseManager()
{
    //default constructor uses default database connection details
    mainConnection =  QSqlDatabase::addDatabase("QSQLITE");
    mainConnection.setDatabaseName("data.db3");
    mainConnection.open();
    ready = false;
}

databaseManager::~databaseManager()
{
    mainConnection.close();
}

bool databaseManager::prepareAndExecQuery(QString queryString){
    rowCount = 0;
    delete currentQuery;
    currentQuery = NULL;
    currentQuery = new QSqlQuery;
    currentQuery->prepare(queryString);
    ready = currentQuery->exec();
    if (ready == true)
        rowCount = currentQuery->size();
    return ready;
}

QSqlRecord databaseManager::getNextRow(){
    currentQuery->next();
    return currentQuery->record();
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

databaseManager* databaseManager::instance() {
    static databaseManager m_instance;
    return &m_instance;

}

int databaseManager::getRowCount() {
    return rowCount;
}
