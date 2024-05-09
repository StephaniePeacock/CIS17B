/* 
 * File:   User.cpp
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: User Class Implementation
 */
#include <cstring>
#include "User.h"
using namespace std;

//default constructor
User::User() : admin(false), numS(0), numQ(0), rank(1) {
    email[0] = '\0';
    pword[0] = '\0';
}
//register new user
User::User(const string em, const string pw) : admin(false), numS(0), numQ(0), rank(1){
    strcpy(email,em.c_str());
    strcpy(pword,pw.c_str());
}






