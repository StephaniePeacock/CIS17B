/* 
 * File:   UserController.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserController Class Specification
 */

#include "User.h"
#include "UserView.h"

#include <regex>
using namespace std;

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

//Forward Declarations
class User;
class UserView;

class UserController {
private:
    User *user;
    UserView  *userView;  
public:
    UserController()  { user = new User(); userView = new UserView(); } //##May need to set these to null ptr instead
    ~UserController() { delete user;       delete userView; }
    
    //Menus
    void mainMenu();    //inital menu - login, register, quit
    void userMenu();    //shown if user is not admin, or admin selects (take survey, view account, change account, exit)
    void adminMenu();   //shown if user is admin (Manage Users, Manage Surveys, View Users, View Surveys) 
    void surveyMenu();  //so the user can access the surveys
    bool acctMenu(User*);    //user can modify their account details
    //Support Functions
    void getInfo(string&,string&);  //get user email & password for validation
    void login();                   //access database & load user
    void reg();                     //create new user
    bool checkEm(string&);          //make sure email meets formatting
    bool checkPw(string&);          //make sure pw meets formatting
    bool verify(string, string);    //verify user matches from file
    //admin functions
    void delUser(const User*) {}   //delete a user - can't delete self
    void updateUser(const User*) {}  //modify a user - can't modify self

};

#endif /* USERCONTROLLER_H */

