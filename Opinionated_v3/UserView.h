/* 
 * File:   UserView.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserView Class Specification
 */
#include "Generics.h"
#include "User.h"
using namespace std;

#ifndef USERVIEW_H
#define USERVIEW_H

class User;
class Survey;

class UserView {
private:
    const User& user;       //so we don't have to pass it - should update when we change user!
    //if I have time add color mode option, so the user can toggle between color schemes
public:
    UserView() : user(User()){} //default - DON'T USE! Just here cause we have to
    UserView(const User& user) : user(user) {}  //The REAL constructor
    virtual ~UserView(){}

    //Display Functions
    void display(const User&) const;    //shows current user's data  (for user)
    void surveyInfo(const Survey);      //full printout of the survey data
    void showSurvey(const Survey);      //print out the survey & questions no data
    void printQ(const Survey s, int indx);

    //Accessors

    //Menu Messages
    static void prompt(int);   //for textual prompts to the user
    static void err(int);      //to guide the user when there's a problem with the input
};

#endif /* USERVIEW_H */

