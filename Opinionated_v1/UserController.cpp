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
    int choice;
    userView->prompt(1); // intro menu
    cin >> choice;
    switch(choice){
        case 1:
            login();
            break;
        case 2:
            reg();
            break;
        case 3:
            return; //go back
            break;
        default:
            break;
            
    }
    
}

//shown if user is not admin, or admin selects (take survey, view account, change account, exit)
void UserController::userMenu(){

}

//shown if user is admin (Manage Users, Manage Surveys, View Users, View Surveys)
void UserController::adminMenu(){

} 

//So we can be D.R.Y.
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
    this->userModel->setEm(e);    //## Change this to open the file & copy the user's data in
    this->userModel->setPw(p);    //## Change this to open the file & copy the user's data in
    
    
}
//create a new user
void UserController::reg(){
    string e,p;             // to hold the emails & pw till we verify
    getInfo(e,p);           // get the inputs
    //make a new model
    UserModel* newUser = new UserModel(e,p);
    delete userModel;       //delete original
    userModel = newUser;    //replace with new one
}

//make sure we have a valid style email
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

bool UserController::verify(string em, string pw){
    return true;
}