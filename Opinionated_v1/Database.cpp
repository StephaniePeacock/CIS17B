/* 
 * File:   Database.cpp
 * Author: Stephanie Peacock
 * Created on May 2, 2024, 11:55 PM
 * Purpose: Database Class Implementation
 */
#include <iostream>
#include <fstream>
#include "Database.h"
using namespace std;

Database::Database() {
    users.name = "Users.bin";
    index.name = "SurveyIDs.bin";
}

Database::~Database() {
}

//Let's be D.R.Y. and set it up for both files
void Database::open(int file){
    if(file == 1){   //true is users
        users.source.open(users.name, ios::binary | ios::in | ios::out);
        if(!users.source.is_open()){
            cout << "Error opening file!\n";
        }
    }           //User file
    else if (file == 2){      //false for questions
        survey.source.open(survey.name, ios::binary | ios::in | ios::out);
        if(!survey.source.is_open()){
            cout << "Error opening file!\n";
        }
    }     //Survey file
    else if (file == 3) {
        index.source.open(index.name, ios::binary | ios::in | ios::out);
        if(!index.source.is_open()){
            cout << "Error opening file!\n";
        }
    }    //Index file
    else {  cout << "Invalid file selected.\n"; } 
}

//Let's be D.R.Y. and set it up for both files
void Database::close(int file){
    if (file == 1) { 
        if (users.source.is_open()) {
            users.source.close();
        } else {
            cout << "User file is not open!\n";
        }
    } 
    else if (file == 2) {
        if (survey.source.is_open()) {
            survey.source.close();
        } else {
            cout << "Survey file is not open!\n";
        }
    } 
    else if (file == 3) {
        if (index.source.is_open()) {
            index.source.close();
        } else {
            cout << "Index file is not open!\n";
        }
    } 
    else {  cout << "Invalid file selected.\n"; }
}

//Adds a user to the database
void Database::add(const User& user) {
    this->open(1);  //opens the users file
    file.write(reinterpret_cast<const char*>(&user), sizeof(User));
    this->close(1); //close the user file   
}



