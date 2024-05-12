/* 
 * File:   User.cpp
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: User Class Implementation
 */

#include "User.h"
#include "Generics.h"
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

User::User(const string em, const string pw, const bool ad, const int ns, const int nq, const int r){
    strncpy(email,em.c_str(), user::MAX);
    email[user::MAX-1] = '\0';    //null terminate it
    strncpy(pword,pw.c_str(), user::MAX);
    pword[user::MAX-1] = '\0';    //null terminate it
    this->admin = ad;
    this->numS = ns;
    this->numQ = nq;
    this->rank = r;
}

//for comparing emails to sort
bool User::operator< (const User& other) const {
    return strcmp(this->email, other.email) < 0;
}   

bool User::operator> (const User& other) const {
    return strcmp(this->email, other.email) > 0;
} 

//copy one user to another - I learned my lesson with Surveys!
void User::operator= (const User& other){
    strncpy(this->email, other.email, user::MAX);
    strncpy(this->pword, other.pword, user::MAX);
    this->admin = other.isAdmin();
    this->numS = other.getNumSurveys();
    this->numQ = other.getNumQuestions();
    this->rank = other.getRank();
}  

//let's make it easier to check if emails are equal
bool User::operator==(const User& other) const{
    return strcmp(this->email, other.email) == 0;
}    


