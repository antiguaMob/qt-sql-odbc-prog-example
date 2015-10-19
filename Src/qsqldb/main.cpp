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
          qDebug() << tables;
          #endif

          // Construct a SQL statement.
          QSqlQuery query("select @@version");

          while( query.next() )
          {
             QString version = query.value(0).toString();

             qDebug () << version;
          }
       }
       else
       {
          #ifdef DEBUG
          qDebug() << "No tables in current DB!";
          #endif

          goto EXIT;
       }
    }  // if(ok)
    else
      cout << "Fail to open " << DB_TYPE << " DB!" << endl;

EXIT:

    return app.exec();
}

