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
                    "[3] Exit\n"
                    ">> ";
            break;
        case 2:
            cout << "Enter the email address: ";
            break;
        case 3:
            cout << "Enter the Password: ";
            break;    
        case 4:                                 //User Menu
            cout << "[1] Take Survey\n"
                    "[2] View Stats\n"
                    "[3] Update Account\n"
                    "[4] Logout\n"
                    ">> ";
            break;   
        case 5:                                 //Admin Menu
            cout << "[1] View All Users\n"
                    "[2] Add User\n"
                    "[3] Delete User\n"
                    "[4] Modify User\n"
                    "[5] Exit Menu\n"
                    ">> ";
            break;
        case 6:
            cout << "[1] Admin Menu\n"
                    "[2] User Menu\n"
                    "[3] Exit Menu\n"
                    ">> ";
            break;
        case 7:
            cout << "[1] Change email\n"
                    "[2] Update Password\n"
                    "[3] Delete Account\n"
                    "[4] Exit Menu\n"
                    ">> ";
            break;
        case 8:
            cout << "Are you sure? This can't be undone.\n"
                    "Enter Y to continue, any other key to cancel.\n"
                    ">> ";
            break;
        case 9:
            cout << "Account Removed.\n";
            break;
        case 10:
            cout << "Cancelling.\n";
            break;
        case 11:
            cout << "[1] Modify User's Email \n"
                    "[2] Modify User's Password\n"
                    "[3] Modify User's Admin Status\n"
                    "[4] Modify User's Number of Surveys Completed\n"
                    "[5] Modify User's Number of Questions Answered\n"
                    "[6] Modify User's Rank\n"
                    "[7] Exit Menu\n"
                    ">> ";
            break;
        case 12:
            cout << "Enter the new value.\n"
                    ">> ";
            break;
        case 13:
            cout << "Enter the email of the user you wish to modify.\n"
                    ">> ";
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
        case 8:
            cout << "Email already exists.\n";
            break;
        case 9:
            cout << "No such Email exists.\n";
            break;
        case 10:
            cout << "User data is not correct.\n";
            break;
        case 11:
            cout << "Unable to modify your account, access User Menu to make changes.\n"
                    "Press Y to exit, any other key to re-enter.\n"
                    ">> ";
            break;
        default: break;
    }
}

//shows current user's data
void UserView::display(const User& user) const {
    cout << "Email              : " << user.getEmail() << endl
         << "Password           : " << user.getPword() << endl
         << "Surveys Completed  : " << user.getNumSurveys() << endl
         << "Questions Answered : " << user.getNumQuestions() << endl
         << "Current Rank       : " << user.getRank() << endl << endl;
}
