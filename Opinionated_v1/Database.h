/* 
 * File:   Database.h
 * Author: Stephanie Peacock
 * Created on May 2, 2024, 11:55 PM
 * Purpose: Database Class Specification
 */

#include "Generics.h"
using namespace std;

#ifndef DATABASE_H
#define DATABASE_H

class Database {
private:
    string userFile;
    fstream users;
    string queryFile;
    fstream questions;
public:
    Database();
    virtual ~Database();

    //Mutators

    //Accessors

    //Other Functions
    void open(bool);
};

#endif /* DATABASE_H */

