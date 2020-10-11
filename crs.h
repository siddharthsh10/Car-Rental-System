# include <iostream>
# include <string>
# include <cstring>
# include <stdlib.h>
# include <conio.h>
# include <stdio.h>
# include <iomanip>

# include "sqlite3.h"

using namespace std;


class database {
public:
    void show_cars_db() {

        cout << endl << endl << endl;

        cout << "******************* CARS DATABASE *******************" << endl << endl;

        sqlite3* dbs;
        sqlite3_stmt* stmt;
        sqlite3_open("carsdatabase.db", &dbs);

        sqlite3_prepare_v2(dbs, "select name, price, type, status from carsTable", -1, &stmt, 0);

        const unsigned char* name;
        const unsigned char* type;
        const unsigned char* status;
        int price;
        int sno=0;


        while(sqlite3_step(stmt) != SQLITE_DONE){

            name = sqlite3_column_text(stmt, 0);
            price = sqlite3_column_int(stmt, 1);
            type = sqlite3_column_text(stmt, 2);
            status = sqlite3_column_text(stmt, 3);

            cout << "** sno: " << sno+1 <<"     ";
            cout << "** name: " << name <<"     ";
            cout << "** price: " << price <<"     ";
            cout << "** type: " << type <<"      ";
            cout << "** status: " << status << endl;
        }

        cout << endl << "DISPLAY COMPLETE..." << endl << endl;

        sqlite3_close(dbs);

    }



    void show_users_db() {

        // FUNTION TO PRINT THE USERS DATABASE

        cout << endl << endl << endl;

        cout << "******************* USER DATABASE *******************" << endl << endl;

        sqlite3* db;
        sqlite3_stmt* stmt;
        sqlite3_open("database.db", &db);

        sqlite3_prepare_v2(db, "select uid, pwd from users", -1, &stmt, 0);

        // TEMPORARY VARIABLES FOR STORING ID AND PASSWORD!
        const unsigned char* id;
        const unsigned char* password;


        while(sqlite3_step(stmt) != SQLITE_DONE){

            id = sqlite3_column_text(stmt, 0);
            password = sqlite3_column_text(stmt, 1);
            cout << "** user id: " << id << "       ";
            cout << "** password: " << password << endl;
        }

        cout << endl << "DISPLAY COMPLETE..." << endl << endl;

        sqlite3_close(db);

    }



    void modify_cars_db() {

        int choice;

        cout << endl << endl << endl;
        cout << "******************* MODIFY CARS DATABASE *******************" << endl << endl;
        cout << "1. ADD TO DATABASE" << endl;
        cout << "2. DELETE FROM DATABASE" << endl;
        cout << "ENTER CHOICE: ";
        cin >> choice;

        switch(choice){

            case 1: add_to_cars_database(); break;
            case 2: delete_cars(); break;
            default: cout<<"WRONG CHOICE!";

        }

    }



    void modify_users_db() {
        // DEFINE THIS FUNCTION

        cout << "modify users database...." << endl;

        char* err;
        char name[50];
        sqlite3* db;
        sqlite3_stmt* stmt;
        sqlite3_open("database.db", &db);
        char operation[150];
        sprintf(operation , "delete from users where name like '%s'",name);

        int res = sqlite3_exec(db, operation, NULL, NULL, &err);

        if(res != SQLITE_OK){
            cout << "ERROR... " << err;
        }else{
            cout << "DATA DELETED SUCCESSFULLY..." << endl << endl;
        }

        sqlite3_close(db);
        cout << endl << endl;


    }



    void add_to_cars_database() {

        char name[50];
        char type[50];
        char status[50];
        int price;
        int i;
        char choice = 'Y';

        while (choice == 'Y')
        {



            cout << "ENTER NAME: ";
            cin >> name;

            for(i=0; name[i] != '\0'; i++)
            {
                if(name[i] == '_')
                {
                    name[i] = ' ';
                }
            }

            cout << "ENTER PRICE: ";
            cin >> price;

            cout << "ENTER TYPE: ";
            cin >> type;

            for(i=0; type[i] != '\0'; i++)
            {
                if(type[i] == '_')
                {
                    type[i] = ' ';
                }
            }

            cout << "ENTER STATUS: ";
            cin >> status;

            for(i=0; status[i] != '\0'; i++)
            {
                if(status[i] == '_')
                {
                    status[i] = ' ';
                }
            }



            add_cars( name, price, type, status);

            cout << "ADD MORE?(Y/N)";
            cin >> choice;
        }

        modify_cars_db();


    }

    void add_cars( char* NAME, int PRICE ,char* TYPE, char* STATUS) {

        char* err;
        sqlite3* dbs;
        sqlite3_stmt* stmt;


        sqlite3_open("carsdatabase.db", &dbs);

        char operation[150];
        sprintf(operation , "insert into carsTable ( name, price, type, status) values ('%s' , '%d' ,'%s', '%s');" ,NAME, PRICE ,TYPE, STATUS); //SPRINTF PRINTS TO A STRING BUFFER!
        // puts(operation); // debug statement

        int res = sqlite3_exec(dbs, operation, NULL, NULL, &err);

        if(res != SQLITE_OK){
            cout << "ERROR... " << err;
        }else{
            cout << "DATA ADDED SUCCESSFULLY..." << endl << endl;
        }

        sqlite3_close(dbs);
        cout << endl << endl;

    }

    void delete_cars() {

        // DEFINE THIS FUNCTION

        cout << "delete cars database...." << endl;
        char* err;
        char name[50];
        sqlite3* dbs;
        sqlite3_stmt* stmt;

        cout << "\nEnter name of the car: ";
        cin >> name;

        for(int i=0; name[i] != '\0'; i++)
        {
            if(name[i] == '_')
            {
                name[i] = ' ';
            }
        }

        sqlite3_open("carsdatabase.db", &dbs);

        char operation[150];
        sprintf(operation , "delete from carsTable where name like '%s'",name);

        int res = sqlite3_exec(dbs, operation, NULL, NULL, &err);

        if(res != SQLITE_OK){
            cout << "ERROR... " << err;
        }else{
            cout << "DATA DELETED SUCCESSFULLY..." << endl << endl;
        }

        sqlite3_close(dbs);
        cout << endl << endl;

    }


};



class admin {

    string pass = "me@ADMIN";

public:
    bool authenticate(string s){
        if (s == pass)
            return true;
        else
            return false;
    }

    void show_admin_menu() {
        int choice;

        cout << endl << endl << endl;
        cout << "******************* ADMIN MENU *******************" << endl << endl;
        cout << "1. VIEW CARS DATABASE" << endl;
        cout << "2. VIEW USERS DATABASE" << endl;
        cout << "3. MODIFY CARS DATABASE" << endl;
        cout << "4. MODIFY USERS DATABASE" << endl;
        cout << "ENTER CHOICE (1/2/3/4): ";
        cin >> choice;

        switch(choice){
            case 1: view_cars_database(); break;
            case 2: view_users_database(); break;
            case 3: modify_cars_database(); break;
            case 4: modify_users_database(); break;
            default: cout << "WRONG CHOICE!"; cout << endl << endl << endl; show_admin_menu();
        }

    }

    void view_cars_database() {

        char choice;


        database db;
        db.show_cars_db();


        cout << endl << "go back? (y/n): ";
        cin >> choice;
        if (choice == 'y')
            show_admin_menu();
    }




    void view_users_database() {

        char choice;

        database db;
        db.show_users_db();

        cout << endl << "go back? (y/n): ";
        cin >> choice;
        if(choice == 'y')
            show_admin_menu();

    }




    void modify_cars_database() {
         char choice;

        database db;
        db.modify_cars_db();

        cout << endl << "go back? (y/n): ";
        cin >> choice;
        if(choice == 'y')
            show_admin_menu();
    }




    void modify_users_database() {
        char choice;

        database db;
        db.modify_users_db();

        cout << endl << "go back? (y/n): ";
        cin >> choice;
        if(choice == 'y')
            show_admin_menu();
    }

};




class user{

    const unsigned char* iden;
    const unsigned char* password;

public:

    bool user_auth(char* id, char* pass){
        // A FUNCTION TO CHECK IF THE USER EXISTS IN THE USER DATABASE BY COMPARING ID AND PASSWORD.

        // int i,j;
        sqlite3* db;
        sqlite3_stmt* stmt;
        sqlite3_open("database.db", &db);

        bool found = false;
        bool flag = false;

        sqlite3_prepare_v2(db, "select uid, pwd from users", -1, &stmt, 0);

        while(sqlite3_step(stmt) != SQLITE_DONE)
        {

            iden = sqlite3_column_text(stmt, 0);
            password = sqlite3_column_text(stmt, 1);

            const char* curr_id =  reinterpret_cast<const char*>(iden);
            const char* curr_pass = reinterpret_cast<const char*>(password);

            int id_match = strcmpi(id, curr_id);
            int pass_match = strcmpi(pass, curr_pass);

            if((id_match == 0) && (pass_match == 0)) {
                cout << "*** LOGIN SUCCESSFUL ***" << endl;
                found = true;
                break;
            }

            else if((id_match == 0) && (pass_match != 0)) {
                cout << "WRONG PASSWORD...." << endl;
                flag = true;
            }
        }

        if(!found && !flag) {
            cout << "USER NOT FOUND..." << endl;
        }


        sqlite3_close(db);

        return found;
}



    void show_user_menu(){
        int choice;


        cout << endl << endl << endl;
        cout << "******************* USER MENU *******************" << endl << endl;
        cout << "1. VIEW CARS DATABASE" << endl;
        cout << "2. CHANGE PASSWORD" << endl;
        cout << "ENTER CHOICE (1/2): ";
        cin >> choice;

        switch(choice){
            case 1: view_cars_database(); break;
            case 2: change_password(); break;
            default: cout << "WRONG CHOICE!"; cout << endl << endl; show_user_menu();
        }
    }




    void change_password() {
        cout << "not implemented yet......." << endl << endl << endl;
        show_user_menu();
    }



    void view_cars_database() {

        char choice;


        database db;
        db.show_cars_db();


        cout << endl << "go back? (y/n): ";
        cin >> choice;
        if (choice == 'y')
            show_user_menu();
    }



};



class newUser{

public:
    void add(char* id, char* password){

        char* err;
        sqlite3* db;
        sqlite3_stmt* stmt;

        // inserting the values for new user in the database.
        sqlite3_open("database.db", &db);

        char command[50];
        sprintf(command, "INSERT INTO users VALUES ('%s' ,'%s');", id, password); //SPRINTF PRINTS TO A STRING BUFFER!
        // puts(command); // debug statement

        int response = sqlite3_exec(db, command, NULL, NULL, &err);

        if(response != SQLITE_OK){
            cout << "ERROR... " << err;
        }else{
            cout << "USER ADDED SUCCESSFULLY..." << endl << endl;
        }

        sqlite3_close(db);

    }

};




class sys{

public:
    void show_menu(){
        int choice;

        cout << "******************* WELCOME TO CAR RENTAL SYSTEM *******************";
        cout << endl << endl << "1. ADMIN LOGIN" << endl;
        cout << "2. USER LOGIN" <<  endl;
        cout << "3. NEW USER" << endl;
        cout << endl << "ENTER YOUR CHOICE (1/2/3): ";
        cin >> choice;

        switch(choice) {
            case 1 : admin_login(); break;
            case 2 : user_login(); break;
            case 3 : new_user(); break;
            default : cout << "wrong choice!";
        }
    }






    void admin_login(){
        admin adm;  // adm is an object of admin class declared above.

        char pass[50];
        int attempts = 3;

        while (attempts >= 0){

            cout << "ENTER PASSWORD: ";

            pass_input(pass);

            if(adm.authenticate(pass))
            {
                adm.show_admin_menu();
                break;
            }

            else
            {
                cout << endl;
                cout << "UNSUCCESSFUL! " << attempts << " ATTEMPTS LEFT!" << endl;
            }

            -- attempts;


        }

        cout << endl << endl;
        show_menu();

    }




    void user_login() {
        user us;

        char id[50];
        char password[50];

        cout << "ENTER USER ID: ";
        cin >> id;
        cout << "ENTER USER PASSWORD: ";
        pass_input(password);
        cout << endl;

        if(us.user_auth(id, password)){
            cout << endl << endl;
            us.show_user_menu();
        }

        else {
            cout << endl << endl;
            show_menu();
        }
    }





    void new_user() {

        char id[50];
        char password[50], temp[50];

        cout << "ENTER ID: ";
        cin >> id;
        cout << "ENTER PASSWORD: ";
        pass_input(password);
        cout << endl;
        cout << "CONFIRM PASSWORD: ";
        pass_input(temp);
        cout << endl;

        if(strcmpi(password, temp)){
            cout << "PASSWORDS DO NOT MATCH! TRY AGAIN!" << endl << endl;
            show_menu();
        }

        else {
            newUser nu;
            nu.add(id, password);
            cout << endl << endl;
            show_menu();
        }

    }


    void pass_input(char* password) {


        int p = 0;

        while(password[p]!='\r') {

            password[p]=getch();

            // CHECKS FOR ENTER KEY
            if(password[p] == 13){
                break;
            }


            // CHECKS FOR BACKSPACE OR DEL KEY
            if(password[p] == 127 || password[p] == 8){
                cout << "\b \b";
                -- p;
            }

            else {
                cout << "*";
                ++ p;
            }

        }

        password[p]='\0';

    }

};

