/* 
 * File:   UserController.cpp
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserController Class Implementation
 */

#include "UserController.h"
#include "Generics.h"
using namespace std;

//inital menu - login, register, quit
void UserController::mainMenu(){
    char choice;
    userView->prompt(1); // intro menu
    cin >> choice;
    switch(choice){
        case '1':
            login();    break;
        case '2':
            reg();      break;
        case '3':
            return;     break;
        default: 
            userView->err(7);     break;        
    }  
}

//shown if user is not admin, or admin selects (take survey, view account, change account, exit)
void UserController::userMenu(){
    char choice;
    bool quit = false;
    do {
        userView->prompt(4);
        switch (choice) {
            case '1':   //Survey menu
                surveyMenu();               break;
            case '2':   //displays user's info
                userView->display();    break;
            case '3':   //exits if the user deletes acct
                if(!acctMenu(user)){    
                    quit = true; }          break;
            case '4':   //exit to main menu
                quit = true;                break;
            default:
                userView->err(7);           break;
        }
    } while (!quit);  
}

//shown if user is admin (Manage Users, Manage Surveys, View Users, View Surveys)
void UserController::adminMenu(){
    char choice;
    bool quit = false;
    do{
        userView->prompt(5);
        cin >> choice;
        switch(choice){
            case '1':                             
                userView->displayAll();     break;  //view all users
            case '2': 
                reg();                      break;  //add user
            case '3': 
                delUser(user);             break;  //delete user
            case '4': 
                updateUser(user); break;  //modify user menu
            case '5': 
                quit = true;                break;  //exit menu
            default: 
                userView->err(7);           break;  //invalid choice
        }
    } while (!quit);
} 

//user access to the surveys
void UserController::surveyMenu(){}

//user can modify their account details - return false if user deletes account
bool UserController::acctMenu(User* user){
    return true;
}

//So we can be D.R.Y.       ***DONE***
void UserController::getInfo(string& e, string& p){
    userView->prompt(2);    // ask for email
    do{
        getline(cin,e);         //get the email   
        if(e.length() < 7){ //make sure its not too small
            userView->err(1);   //tell user its too small (lol)
        }
        if(e.length() > 80){//make sure it's not too big
            userView->err(2);   //tell user it's too big (that's what she said)
        }
        if(!checkEm(e)){    //size is good but wrong email format
            userView->err(3);
        }
    } while (e.length() < 7 || e.length() > 80 || !checkEm(e)); //go till it fits
    
    //now get the password
    userView->prompt(3);    //ask for password
    do{
        getline(cin,p);         //get the password   
        if(p.length() < 7){ //make sure its not too small
            userView->err(1);   //tell user its too small (lol)
        }
        if(p.length() > 80){//make sure it's not too big
            userView->err(2);   //tell user it's too big (that's what she said)
        }
        //err prompts are in the checkEm function
    } while (e.length() < 7 || e.length() > 80 || !checkEm(e)); //go till it fits
}

//access existing user
void UserController::login(){
    string e,p;             // to hold the emails & pw till we verify
    getInfo(e,p);           // get the inputs
    //verify the user's information is correct
    cout << "Placeholder for checking the DB for valid info.\n";
    //set the model to match
//    this->user->setEm(e);    //## Change this to open the file & copy the user's data in
//    this->user->setPw(p);    //## Change this to open the file & copy the user's data in
    
    
}

//create a new user
void UserController::reg(){
    string e,p;             // to hold the emails & pw till we verify
    getInfo(e,p);           // get the inputs
    //make a new model
    User* newUser = new User(e,p);
    delete user;       //delete original
    user = newUser;    //replace with new one
    //##Save the user to file - need to add
}

//force valid style email   ***DONE***
bool UserController::checkEm(string& em){
    /*Regular expression! declare the pattern first
    * checks local for no . at start or end, no double dots
    * then checks for at exactly 1 @ 
    * lastly checks domain for no . at start or end
    * and at least 2 letters after the last . for top level domain  */
    const regex pattern(R"(\b[A-Za-z0-9_][A-Za-z0-9._-]*[A-Za-z0-9]@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*(?:\.[A-Z|a-z]{2,}\b))");
    //now check if the email matches the pattern and return it
    return regex_match(em, pattern);
}

//password requirements     ***DONE***
bool UserController::checkPw(string& pw){
    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false; 
    bool num   = false;
    //verify we have upper, lower, and number - check all at once!
    for(char ch : pw){
        if(isupper(ch)){ upper = true; }
        if(islower(ch)){ lower = true; }
        if(isdigit(ch)){ num   = true; }
    }
    //we met all criteria, set to true
    if(upper && lower && num) { valid = true; }
    //missing something
    if(!upper) { userView->err(4); }
    if(!lower) { userView->err(5); }
    if(!num)   { userView->err(6); }
    //send it back baby
    return valid;
}

//## Need to get this working after file stuff is in
bool UserController::verify(string em, string pw){
    return true;
<<<<<<< Updated upstream
}
=======
}

//admin can't modify themselves in this menu
void UserController::updateUser(const User* admin){
    
}

//delete a user - can't delete self
void UserController::delUser(const User*) {}

//add user to file
void UserController::addUser(const User*){}  

//get a user from the file at specific position
void UserController::get(int, User*){}

//overwrite current user data at position
void UserController::set(int, const User&){}    
    
>>>>>>> Stashed changes
