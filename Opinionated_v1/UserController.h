/* 
 * File:   UserController.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserController Class Specification
 */

#include "UserModel.h"
#include "UserView.h"

#include <regex>
using namespace std;

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

//Forward Declarations
class UserModel;
class UserView;

class UserController {
private:
    UserModel *userModel;
    UserView  *userView;  
public:
    UserController()  { userModel = new UserModel(); userView = new UserView(); }
    ~UserController() { delete userModel;            delete userView; }
    
    //Menus
    void mainMenu();    //inital menu - login, register, quit
    void userMenu();    //shown if user is not admin, or admin selects (take survey, view account, change account, exit)
    void adminMenu();   //shown if user is admin (Manage Users, Manage Surveys, View Users, View Surveys) 
    //Support Functions
    void getInfo(string&,string&);  //get user email & password for validation
    void login();                   //access database & load user
    void reg();                     //create new user
    bool checkEm(string&);          //make sure email meets formatting
    bool checkPw(string&);          //make sure pw meets formatting
    bool verify(string, string);    //verify user matches from file
};

#endif /* USERCONTROLLER_H */

