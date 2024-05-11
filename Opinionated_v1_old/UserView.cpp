/* 
 * File:   UserView.cpp
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserView Class Implementation
 */

#include <iostream>
#include "UserView.h"
using namespace std;

//for textual prompts to the user
void UserView::prompt(int choice){
    switch(choice){
        case 1:                                 //Main Menu
            cout << endl << "Main Menu" << endl;
            cout << "[1] Login\n"
                    "[2] Register\n"
                    "[3] Rules\n";
            break;
        case 2:
            cout << "Enter your email address: ";
            break;
        case 3:
            cout << "Enter your Password: ";
            break;    
        case 4:                                 //User Menu
            cout << "[1] Take Survey\n"
                    "[2] View Stats\n"
                    "[3] Update Account"
                    "\n[4] Logout\n";
            break;   
        case 5:                                 //Admin Menu
            cout << "[1] View All Users\n"
                    "[2] Add User\n"
                    "[3] Delete User\n"
                    "[4] Modify User\n"
                    "[5] Exit Menu\n";
            break;
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
        case 7:
            cout << "Invalid choice.\n";
            break;
        case 8:break;
        case 9:break;
        case 10:break;
        case 11:break;
        default: break;
    }
}

//shows current user's data
void UserView::display() const {
    cout << "Email              : " << user.getEmail() << endl
         << "Password           : " << user.getPword() << endl
         << "Surveys Completed  : " << user.getNumSurveys() << endl
         << "Questions Answered : " << user.getNumQuestions() << endl
         << "Current Rank       : " << user.getRank() << endl;
}

//shows selected user's data (for admin)
void UserView::display(int n) const {
    
} 