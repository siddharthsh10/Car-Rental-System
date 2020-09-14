# include <iostream>
# include <string>
# include <cstring>
# include <stdlib.h>
# include <conio.h>
# include <stdio.h>

# include "sqlite3.h"

using namespace std;


class database {
public:
    void show_cars_db() {
        // DEFINE THIS FUNCTION

        cout << "\t\t\t\t\t\t\t view cars database...." << endl;
        sqlite3* db;
        sqlite3_stmt* stmt;
        sqlite3_open("carsdb.db", &db);

        sqlite3_prepare_v2(db, "select name, price, type, status from cars", -1, &stmt, 0);

        const unsigned char* name;
        int price;
        const unsigned char* type;
        const unsigned char* status;

        while(sqlite3_step(stmt) != SQLITE_DONE){

            name = sqlite3_column_text(stmt, 0);
            price = sqlite3_column_int(stmt, 1);
            type = sqlite3_column_text(stmt, 2);
            status = sqlite3_column_text(stmt, 3);
            cout << "\t\t\t\t\t\t\t ** name: " << name<< "   ";
            cout << "** price: " << price << "   ";
            cout << "** type: " << type << "   ";
            cout << "** status: " <<status <<endl;
        }

        cout << endl << "\t\t\t\t\t\t\t DISPLAY COMPLETE..." << endl << endl;

        sqlite3_close(db);

    }



    void show_users_db() {

        // FUNTION TO PRINT THE USERS DATABASE

        cout << endl << endl << endl;

        cout << "\t\t\t\t\t\t\t displaying users database..." << endl << endl;

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
            cout << "\t\t\t\t\t\t\t ** user id: " << id << "          ";
            cout << "** password: " << password << endl;
        }

        cout << endl << "\t\t\t\t\t\t\t DISPLAY COMPLETE..." << endl << endl;

        sqlite3_close(db);

    }



    void modify_cars_db()
    {
        // DEFINE THIS FUNCTION



        int choice;

        cout << endl << endl << endl << endl <<endl;
        cout << "\t\t\t\t\t\t\t **************** MODIFY CARS DATABASE ****************" << endl << endl;
        cout << "\t\t\t\t\t\t\t 1. ADD TO DATABASE." << endl;
        cout << "\t\t\t\t\t\t\t 2. DELETE FROM DATABASE." << endl;
        cout << "\t\t\t\t\t\t\t ENTER CHOICE (1/2): ";
        cin >> choice;

        switch(choice)
        {
            case 1: add_to_cars_database(); break;
            case 2: delete_from_cars_database(); break;
            default: cout << "\t\t\t\t\t\t\t WRONG CHOICE!"; cout << endl << endl << endl; modify_cars_db();

        }
    }


    void add_to_cars_database()
    {
        string name;
        int price;
        string type;
        string status;

        char choice = 'y';

        char* err;
        sqlite3* db;
        sqlite3_stmt* stmt;
        sqlite3_open("carsdb.db", &db);

        string command;

        while(choice == 'y')
        {

            cout << endl;

            cout << "\t\t\t\t\t\t\t CAR NAME: ";
            getline(cin,name);
            getline(cin,name);

            cout << endl;

            cout << "\t\t\t\t\t\t\t PRICE: ";
            cin >> price;

            cout << endl;

            cout << "\t\t\t\t\t\t\t TYPE: ";
            getline(cin,type);
            getline(cin,type);

            cout << endl;

            cout << "\t\t\t\t\t\t\t STATUS: ";
            getline(cin,status);

            cout << endl;

            char command[50];
            sprintf(command, "INSERT INTO cars VALUES ('%s' ,%d ,'%s' ,'%s');", name, price, type, status); //SPRINTF PRINTS TO A STRING BUFFER!


            int response = sqlite3_exec(db, command, NULL, NULL, &err);

            if(response != SQLITE_OK)
            {
                cout << "\t\t\t\t\t\t\t ERROR... " << err;
            }

            else
            {
                cout << "\t\t\t\t\t\t\t USER ADDED SUCCESSFULLY..." << endl << endl;
            }



            cout << "\t\t\t\t\t\t\t ADD MORE?(y/n)";
            cin >> choice;
        }

        sqlite3_close(db);


    }


    void delete_from_cars_database()
    {

    }



    void modify_users_db() {
        // DEFINE THIS FUNCTION

        cout << "\t\t\t\t\t\t\t modify users database...." << endl;
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

        cout << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t\t ********************* ADMIN MENU *********************" << endl << endl << endl;
        cout << "\t\t\t\t\t\t\t 1. VIEW CARS DATABASE" << endl;
        cout << "\t\t\t\t\t\t\t 2. VIEW USERS DATABASE" << endl;
        cout << "\t\t\t\t\t\t\t 3. MODIFY CARS DATABASE" << endl;
        cout << "\t\t\t\t\t\t\t 4. MODIFY USERS DATABASE" << endl;
        cout << "\t\t\t\t\t\t\t ENTER CHOICE (1/2/3/4): ";
        cin >> choice;


        switch(choice){
            case 1: view_cars_database(); break;
            case 2: view_users_database(); break;
            case 3: modify_cars_database(); break;
            case 4: modify_users_database(); break;
            default: cout << "\t\t\t\t\t\t\t WRONG CHOICE!"; cout << endl << endl << endl; show_admin_menu();
        }

    }

    void view_cars_database() {

        char choice;


        database db;
        db.show_cars_db();


        cout << endl << "\t\t\t\t\t\t\t go back? (y/n): ";
        cin >> choice;
        if (choice == 'y')
            show_admin_menu();
    }




    void view_users_database() {

        char choice;

        database db;
        db.show_users_db();

        cout << endl << "\t\t\t\t\t\t\t go back? (y/n): ";
        cin >> choice;
        if(choice == 'y')
            show_admin_menu();

    }




    void modify_cars_database() {
         char choice;

        database db;
        db.modify_cars_db();

        cout << endl << "\t\t\t\t\t\t\t go back? (y/n): ";
        cin >> choice;
        if(choice == 'y')
            show_admin_menu();
    }




    void modify_users_database() {
        char choice;

        database db;
        db.modify_users_db();

        cout << endl << "\t\t\t\t\t\t\t go back? (y/n): ";
        cin >> choice;
        if(choice == 'y')
            show_admin_menu();
    }

};




class user{

    string dummy_id = "user";
    string dummy_pass = "user";

public:

    bool user_auth(string id, string pass){
        // A FUNCTION TO CHECK IF THE USER EXISTS IN THE USER DATABASE BY COMPARING ID AND PASSWORD.

        // DUMMY IMPLEMNTATION
        if((id == dummy_id) && (pass == dummy_pass))
            return true;

        else if ((id == dummy_id) && (pass != dummy_pass)){
            cout << "\t\t\t\t\t\t\t WRONG PASSWORD!" << endl;
            return false;

        }

        else{
            cout << "\t\t\t\t\t\t\t THE USER DOES NOT EXIST!" << endl;
            return false;
        }
    }





    void show_user_menu(){



        int choice;
        database db;

        cout << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t\t ********************** USER MENU **********************" << endl << endl << endl;
        cout << "\t\t\t\t\t\t\t 1. VIEW CARS DATABASE" << endl;
        cout << "\t\t\t\t\t\t\t 2. CHANGE PASSWORD" << endl;
        cout << "\t\t\t\t\t\t\t ENTER CHOICE (1/2): ";
        cin >> choice;

        switch(choice){
            case 1: view_cars_database(); break;
            case 2: change_password(); break;
            default: cout << "\t\t\t\t\t\t\t WRONG CHOICE!"; cout << endl << endl;show_user_menu();
        }
    }




    void change_password() {
        cout << "\t\t\t\t\t\t\t not implemented yet......." << endl << endl << endl;

    }



    void view_cars_database() {

        char choice;


        database db;
        db.show_cars_db();


        cout << endl << "\t\t\t\t\t\t\t go back? (y/n): ";
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
            cout << "\t\t\t\t\t\t\t ERROR... " << err;
        }else{
            cout << "\t\t\t\t\t\t\t USER ADDED SUCCESSFULLY..." << endl << endl;
        }

        sqlite3_close(db);

    }

};




class sys{

public:
    void show_menu(){

        system("CLS");
        int choice;

        cout << endl << endl << endl << endl << endl;
        cout << "\t\t\t\t\t\t\t ************* WELCOME TO CAR RENTAL SYSTEM *************";
        cout << endl << endl << endl << "\t\t\t\t\t\t\t 1. ADMIN LOGIN" << endl;
        cout << "\t\t\t\t\t\t\t 2. USER LOGIN" <<  endl;
        cout << "\t\t\t\t\t\t\t 3. NEW USER" << endl;
        cout << endl << "\t\t\t\t\t\t\t ENTER YOUR CHOICE (1/2/3): ";
        cin >> choice;
        cout << endl;

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

            cout << "\t\t\t\t\t\t\t ENTER PASSWORD: ";
            int i;
            char temp;

            pass_input(pass);

            if(adm.authenticate(pass)){
                adm.show_admin_menu();
                break;
            }

            else
            	cout << endl;
                cout << "\t\t\t\t\t\t\t UNSUCCESSFUL! " << attempts << " ATTEMPTS LEFT!" << endl;

            -- attempts;

        }

        cout << endl << endl;
        show_menu();

    }




    void user_login() {
        user us;

        string id;
        char password[50];

        cout << "\t\t\t\t\t\t\t ENTER USER ID: ";
        cin >> id;
        cout << "\t\t\t\t\t\t\t ENTER USER PASSWORD: ";
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

        cout << "\t\t\t\t\t\t\t ENTER ID: ";
        cin >> id;
        cout << "\t\t\t\t\t\t\t ENTER PASSWORD: ";
        pass_input(password);
        cout << endl;
        cout << "\t\t\t\t\t\t\t CONFIRM PASSWORD: ";
        pass_input(temp);
        cout << endl;

        if(strcmpi(password, temp)){
            cout << "\t\t\t\t\t\t\t PASSWORDS DO NOT MATCH! TRY AGAIN!" << endl << endl;
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

