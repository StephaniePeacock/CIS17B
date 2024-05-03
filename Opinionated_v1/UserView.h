/* 
 * File:   UserView.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserView Class Specification
 */
#include "Generics.h"
using namespace std;

#ifndef USERVIEW_H
#define USERVIEW_H

//template <class T>

class UserView {
private:
    //if I have time add color mode option, so the user can toggle between color schemes
public:
    UserView(){}
    virtual ~UserView(){}

    //Mutators

    //Accessors

    //Other Functions
    void prompt(int);    //for textual prompts to the user
    void err(int);  //to guide the user when there's a problem with the input
};

#endif /* USERVIEW_H */

