/* 
 * File:   Database.h
 * Author: Stephanie Peacock
 * Created on May 2, 2024, 11:55 PM
 * Purpose: Database Class Specification
 */

using namespace std;

#ifndef DATABASE_H
#define DATABASE_H

class Database {
private:
    string uFile = "Users.bin";
    fstream users;
    string qFile = "Questions.bin";
    fstream questions;
public:
    Database();
    virtual ~Database();

    //Mutators

    //Accessors

    //Other Functions
    void open(bool);
    void close(bool);
};

#endif /* DATABASE_H */

