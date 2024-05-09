/* 
 * File:   User.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: User Class Specification
 */
#include <string>
#include <fstream>
using namespace std;

#ifndef USER_H
#define USER_H

namespace user {    //thanks for the idea Hannes!
    const int MAX = 100;
}


class User {
private:
    char email[user::MAX];
    char pword[user::MAX];
    bool admin; //is the user an admin
    int numS;   //number of surveys completed
    int numQ;   //total number of questions answered
    int rank;   //let's incentivize answering questions with a rank system
       
public:
    
    User();// Default Constructor
    User(const string, const string);//New Registered User Constructor
    User(fstream){}//Load from File Constructor
    // Destructor
    ~User() {}
    // Mutators
    void setEm(const string);
    void setPw(const string);
    void changeAdmin()  { admin = !admin; }
    void setNumS(int s) { numS = s; }   //manually set the number of surveys (for admin only)
    void setNumQ(int q) { numQ = q; }   //manually set the number of questions (for admin only)
    void setRank(int r) { rank = r; }   //manually set the rank (for admin only)
    void addNumS()      { numS++; }     //increment when user completes a survey
    void addNumQ()      { numQ++; }     //increment when user completes a question
    void addRank()      { rank++; }     //increment when user ranks up
    
    
    // Accessors
    const string getEmail() const   { return email; }
    const string getPword() const   { return pword; }
    const bool isAdmin() const      { return admin; }
    int getNumSurveys() const       { return numS; }
    int getNumQuestions() const     { return numQ; }
    int getRank() const             { return rank; }
    
    //Other Functions
    //I NEED A COPY CONSTRUCTOR AND AN = OVERRIDE!!

};

#endif /* USER_H */

