# include <iostream>
# include <string>
# include <stdlib.h>
# include<conio.h>

using namespace std;


class database {
public:
    void show_cars_db() {
        // DEFINE THIS FUNCTION

        cout << "view cars database...." << endl;
    }

    void show_users_db() {
        // DEFINE THIS FUNCTION

        cout << "view users database...." << endl;
    }

    void modify_cars_db() {
        // DEFINE THIS FUNCTION

        cout << "modify cars database...." << endl;
    }

    void modify_users_db() {
        // DEFINE THIS FUNCTION

        cout << "modify users database...." << endl;
    }

};



class admin {

    string pass = "ADMIN";

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

    string dummy_id = "user";
    string dummy_pass = "user";

public:

    bool user_auth(string id, string pass){
        // A FUNCTION TO CHECK IF THE USER EXISTS IN THE USER DATABASE BY COMPARING ID AND PASSWORD.

        // DUMMY IMPLEMNTATION
        if((id == dummy_id) && (pass == dummy_pass))
            return true;

        else if ((id == dummy_id) && (pass != dummy_pass)){
            cout << "WRONG PASSWORD!" << endl;
            return false;

        }

        else{
            cout << "THE USER DOES NOT EXIST!" << endl;
            return false;
        }
    }





    void show_user_menu(){
        int choice;
        database db;

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
    void add(string id, string password){
        // IMPLEMENT THIS FUNCTION TO ADD USER TO THE DATABASE!
        cout << "not implemented yet...." << endl << endl;
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

        string pass;
        int attempts = 3;

        while (attempts >= 0){

            cout << "ENTER PASSWORD: ";
            char pass[32]; // TO store password
            int i;
            char temp;
            
            for(i=0;;) //infinite loop
		    {
		        temp = getch(); //stores char typed in temp
		        
		        if((temp >= 'a' && temp <= 'z')||(temp >= 'A' && temp <= 'Z')||(temp >= '0' && temp <= '9')) //check if a is numeric or alphabet
		        {
		            pass[i] = temp;//stores temp in pass
		            ++i;
		            cout << "*";
		        }
		        
		        if(temp == '\b' && i >= 1) //if user typed backspace & i should be greater than 1
		        {
		            cout << "\b \b"; //delete the character behind the cursor.
		            --i;
		        }
		        
		        if(temp == '\r') //if enter is pressed
		        {
		            pass[i] = '\0'; //null means end of string.
		            break; //break the loop
		        }
		    }

            if(adm.authenticate(pass)){
                adm.show_admin_menu();
                break;
            }

            else
            	cout << endl;
                cout << "UNSUCCESSFUL! " << attempts << " ATTEMPTS LEFT!" << endl;

            -- attempts;

        }

        cout << endl << endl;
        show_menu();

    }




    void user_login() {
        user us;

        string id, password;

        cout << "ENTER USER ID: ";
        cin >> id;
        cout << "ENTER USER PASSWORD: ";
        cin >> password;

        if(us.user_auth(id, password)){
            us.show_user_menu();
        }

        else {
            show_menu();
        }
    }





    void new_user() {

        string id, password, temp;

        cout << "ENTER ID: ";
        cin >> id;
        cout << "ENTER PASSWORD: ";
        cin >> password;
        cout << "CONFIRM PASSWORD: ";
        cin >> temp;

        if(password != temp){
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





    void clear() {
        //FUNCTION FOR CLEARING THE SCREEN
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        cout << "\x1B[2J\x1B[H";
    }

};

