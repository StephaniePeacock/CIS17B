/* 
 * File:   UserController.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserController Class Specification
 */

#include "UserModel.h"
#include "UserView.h"
using namespace std;

#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

//Forward Declarations
class UserModel;
class UserView;

class UserController {
private:
    UserModel *model;
    UserView  *view;  
public:
    UserController(){}
    ~UserController() {}
    void mainMenu(){
        
    }
};

#endif /* USERCONTROLLER_H */

