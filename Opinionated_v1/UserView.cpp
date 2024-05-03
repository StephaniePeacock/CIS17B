/* 
 * File:   UserView.cpp
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserView Class Implementation
 */

#include "UserView.h"
using namespace std;

//template <class T>
//T UserView<T>::UserView() {}

//for textual prompts to the user
void UserView::prompt(int choice){
    switch(choice){
        case 1:
            cout << endl << "Main Menu" << endl;
            cout << "[1] Login\n"
                    "[2] Register\n"
                    "[3] Rules\n"
                    "[4] Exit\n" << ">> ";
            break;
        case 2:
            cout << "Enter your email address: ";
            break;
        case 3:
            cout << "Enter your Password: ";
            break;    
        case 4:break;   
        case 5:break;
        case 6:break;
        case 7:break;
        case 8:break;
        case 9:break;
        case 10:break;
        case 11:break;
        default: break;
    }
}

//to guide the user when there's a problem with the input
void UserView::err(int choice){
    switch(choice){
        case 1:
            cout << "Must be at least 7 characters long.\n";
            break;
        case 2:
            cout << "Must be no more than 80 characters long.\n";
            break;
        case 3:
            cout << "Invalid email format.\n";
            break;    
        case 4:
            cout << "Password must contain an upper case letter.\n";
            break;   
        case 5:
            cout << "Password must contain a lower case letter.\n";
            break;
        case 6:
            cout << "Password must contain a number.\n";
            break;
        case 7:break;
        case 8:break;
        case 9:break;
        case 10:break;
        case 11:break;
        default: break;
    }
}
