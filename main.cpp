# include <iostream>
# include <string>
# include <cstring>
# include <conio.h>
# include <stdio.h>

# include "crs.h"
# include "sqlite3.h"


using namespace std;

void create_database(){

    // function for creating required database. database has two tables "users" and "cars".

    char* err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("database.db", &db);

    int response = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS users(uid VARCHAR(20), pwd VARCHAR(20));", NULL, NULL, &err);

    if(response != SQLITE_OK){
        cout << "ERROR... " << err;
    }

    response = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS cars(name VARCHAR(20), price INT, status varchar(20));", NULL, NULL, &err);

    if(response != SQLITE_OK){
        cout << "ERROR... " << err;
    }

}


int main(){

    create_database();

    sys syst;
    syst.show_menu();

    return 0;
}
