/* 
 * File:   UserController.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserController Class Specification
 */

#include "User.h"
#include "UserView.h"
#include "Survey.h"

#include <regex>
using namespace std;

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

//Forward Declarations
class User;
class UserView;
class Survey;

class UserController {
private:
    User *user;
    UserView  *userView;
//    Survey *survey;     //i forgot to use this, all surveys are local omfg
    fstream file;  //gonna try for all file operations
//    fstream sfile;  //current survey file
//    fstream ifile;  //index file for list of surveys
public:
    UserController()  { user = new User(); userView = new UserView(); } //##May need to set these to null ptr instead
    ~UserController() { delete user;       delete userView; }
    
    //Menus
    void mainMenu();                //inital menu - login, register, quit
    void userMenu(User&);           //shown if user is not admin, or admin selects (take survey, view account, change account, exit)
    bool acctMenu(User&);           //user can modify their account details
    void adminMenu(const User&);    //shown if user is admin (Manage Users, Manage Surveys, View Users, View Surveys) 
    void updateUser(const User);    //modify a user - can't modify self
    void surveyMenu(User&);         //so the user can access the surveys
        
    //Support Functions
    void getInfo(string&,string&);  //get user email & password for validation
    void enterEmail(string&);       //email portion of getInfo()
    void enterPW(string& p);        //password portion of getInfo()
    void login();                   //access database & load user
    void reg();                     //create new user
    bool checkEm(string&);          //make sure email meets formatting
    bool checkPw(string&);          //make sure pw meets formatting
    bool verify(string, string);    //verify user matches from file
    
    //File Management Functions
    void delUser(int pos);          //delete a user - can't delete self
    void addUser(const User*);      //add user to file
    void get(int, User*);           //get a user from the file at specific position
    void set(int, const User&);     //overwrite current user data at position
    int count();                    //helper for find() - # records in file
    long int size();                //helper for find() - used to get count()
    int find(string email);         //finds existing user in database
    void sort(int, User*);          //for sorting the users before we pop them in
    void displayAll();              //for admin to view all
    
    //Survey functions
    void addSurvey();               //add a survey
    void deleteSurvey(int);         //delete survey from index & survey file
    void modifySurvey(int num);     //change existing survey

    void printSurveyNames();        //gets IDs from index file, opens each survey
                                    //and prints the ID & survey name of each survey
    int  getValidID();              //force user to pick a valid survey
    
};

#endif /* USERCONTROLLER_H */

