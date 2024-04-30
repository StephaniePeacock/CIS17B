/* 
 * File:   UserModel.h
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserModel Class Specification
 */

#include "Generics.h"
using namespace std;

#ifndef USERMODEL_H
#define USERMODEL_H

class UserModel {
private:
    char *email;
    string password;
    bool admin; //is the user an admin
    int numS;   //number of surveys completed
    int numQ;   //total number of questions answered
    int rank;   //let's incentivize answering questions with a rank system
    
    // Mutators
    void setEmail(const char *e) {
        delete[] email;
        email = strdup(e);
    }
    void setPass(const string& p) { password = p; }
    void changeAdmin()  { admin = !admin; }
    void setNumS(int s) { numS = s; }   //manually set the number of surveys (for admin only)
    void setNumQ(int q) { numQ = q; }   //manually set the number of questions (for admin only)
    void setRank(int r) { rank = r; }   //manually set the rank (for admin only)
    void addNumS()      { numS++; }     //increment when user completes a survey
    void addNumQ()      { numQ++; }     //increment when user completes a question
    void addRank()      { rank++; }     //increment when user ranks up
    
public:
    // Default Constructor
    UserModel() : email(nullptr), password(""), admin(false), numS(0), numQ(0), rank(0) {}
    //New Registered User Constructor
    UserModel(const string em, const string pw) : password(pw), admin(false), numS(0), numQ(0), rank(0) {
        email = strdup(em.c_str());
    }
    //Load from File Constructor
    UserModel(fstream){}
    // Destructor
    ~UserModel() { delete[] email; }

    // Accessors
    const char* getEmail() const            { return email; }
    const std::string& getPassword() const  { return password; }
    bool isAdmin() const                    { return admin; }
    int getNumSurveys() const               { return numS; }
    int getNumQuestions() const             { return numQ; }
    int getRank() const                     { return rank; }


    //Other Functions
};

#endif /* USERMODEL_H */

