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
    userFile = "Users.bin";
    string queryFile = "Questions.bin";
  //  users.open();
  //  queries.opem();
}

Database::~Database() {
}

//Let's be D.R.Y. and set it up for both files
void Database::open(bool file){
    if(file){   //true is users
        users.open(userFile, ios::binary | ios::in | ios::out);
        if(!users.is_open()){
            cout << "Error opening file!\n";
        }
    }
    else {      //false for questions
        questions.open(queryFile, ios::binary | ios::in | ios::out);
        if(!questions.is_open()){
            cout << "Error opening file!\n";
        }
    }
    
}

