// An example for the access of Microsoft SQL Server using ODBC driver and Qt SQL core library.

#include <iostream>

#include <QtCore>
#include <QtSql/QSqlQuery>

#define DB_TYPE      "QODBC"
#define DB_HOST      "192.168.2.120"
#define DB_PORT      1433
#define DB_NAME      "MSSQL"   // Data Source Name (DSN) define in odbc.ini
#define DB_USER      "william"
#define DB_PASSWORD  "1234"

using namespace std;

int main(int argc, char*argv[])
{
    cout << "Hello Qt DB SQL Test!" << endl;

    QCoreApplication app(argc, argv);

    /* Add the plug-in libraries searching path */
    #if 0
    //QCoreApplication::addLibraryPath(".");
    QCoreApplication::addLibraryPath("/usr/lib64/plugins");
    QCoreApplication::addLibraryPath("/usr/lib64");
    #elif 0
    QStringList strList;

    //strList.push_back(".");
    strList.push_back("/usr/lib64/plugins");
    strList.push_back("/usr/lib64");

    QCoreApplication::setLibraryPaths(strList);
    #endif

    // List all added path for searching libraries or plugins.
    QStringList listLibPath = app.libraryPaths();
    #ifdef DEBUG
    qDebug() << listLibPath;
    #endif

    QSqlDatabase db = QSqlDatabase::addDatabase(DB_TYPE);

    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASSWORD);

    bool ok = db.open();

    if (ok)
    {
       qDebug() << DB_NAME << "DB open Success!";

       // Check if there have tables in the current designated database.
       QStringList tables = db.tables();

       if (tables.empty() == false)
       {
          #ifdef DEBUG
          qDebug() << "Table list: \n" << tables;
          #endif

          QSqlQuery query;   // QSqlQuery query("SQL statement");
          bool resultSqlExec = false;

          ////////// Construct SQL statement.

          /*============================ Query MS SQL Server Version */
          resultSqlExec = query.exec("SELECT @@version");   // query the MS SQL Server version
          qDebug() << "SELECT @@version - Result: " << resultSqlExec;

          while (query.next())
          {
             QString version = query.value(0).toString();
             qDebug () << "The MS SQL Server version: \n" << version;
          }


          /*============================ Create Table */
          resultSqlExec = query.exec("CREATE TABLE person (id int PRIMARY KEY, "
                                     "firstname VARCHAR(20), lastname VARCHAR(20))");
          qDebug() << "create table \"person\" - Result: " << resultSqlExec;


          /*============================ Drop Table */
          resultSqlExec = query.exec("DROP TABLE person");
          qDebug() << "drop table person - Result: " << resultSqlExec;


          /*============================ Query All Tables */
          int num = 1;

          resultSqlExec = query.exec("SELECT * FROM INFORMATION_SCHEMA.Tables");
          qDebug() << "create table customers - Result: " << resultSqlExec;

          while (query.next())
          {
             QString tablename = query.value(2).toString();
             qDebug () << "No. " << num << " - " << tablename;

             num++;
          }
       }
       else
       {
          #ifdef DEBUG
          qDebug() << "No tables in current DB!";
          #endif

          db.close();  // close the opened DB connection.

          goto EXIT;
       }

       db.close();  // close the opened DB connection.
    }  // if(ok)
    else
      cout << "Fail to open " << DB_TYPE << " DB!" << endl;

EXIT:

    return app.exec();
}

