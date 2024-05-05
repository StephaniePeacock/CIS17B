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
    uFile = "Users.bin";
    qFile = "Questions.bin";
  //  users.open();
  //  queries.opem();
}

Database::~Database() {
}

//Let's be D.R.Y. and set it up for both files
void Database::open(bool file){
    if(file){   //true is users
        users.open(uFile, ios::binary | ios::in | ios::out);
        if(!users.is_open()){
            cout << "Error opening file!\n";
        }
    }
    else {      //false for questions
        questions.open(qFile, ios::binary | ios::in | ios::out);
        if(!questions.is_open()){
            cout << "Error opening file!\n";
        }
    }
    
}

//Let's be D.R.Y. and set it up for both files
void Database::close(bool file){
    if (file) { // True for users
            if (users.is_open()) {
                users.close();
            } else {
                std::cout << "User file is not open!\n";
            }
        } else { // False for questions
            if (questions.is_open()) {
                questions.close();
            } else {
                std::cout << "Question file is not open!\n";
            }
        }
    
}

