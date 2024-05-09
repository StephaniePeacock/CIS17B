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
    string name;
    fstream file;
    void open(int);
    void close(int);
    
public:
    Database();
    Database(string);
    virtual ~Database();

    //Mutators
    void setSurvey(int);    //other streams will be static
    
    //Accessors
    string getUsersFileName() const { return users.name; }
    string getSurveyFileName() const { return survey.name; }
    string getIndexFileName() const { return index.name; }
    fstream& getUsersFileStream() { return users.source; }
    fstream& getSurveyFileStream() {    return survey.source; }
    fstream& getIndexFileStream() { return index.source; }

    //Other Functions
    void add(const User&);
        
        /// @brief Get the number of records in the database.
        /// @return The number of records in the database.
        int count();

        /// @brief Get the size (in bytes) of the database.
        /// @return The size (in bytes) of the database.
        long int size();

        /// @brief Find a user record in the database.
        /// @param email The email of the user record to find.
        /// @return The index position of the record in the database.
        int find(string email);

        /// @brief Add a new user record to the database.
        /// @param user The user record to add.        
        

        /// @brief Get a user recrod from the database.
        /// @param pos The index position of the user record to get.
        /// @return The record of the found user. WARNING: Returns dynamically allocated memory.
        void get(int, User*);

        /// @brief Get all user records from the database.
        /// @return A pointer to an array of user records. WARNING: Returns dynamically allocated memory.
        void getAll(User*);

        /// @brief Set the given record at the given index in the database.
        /// @param  pos The index position of the record to set.
        /// @param  user The user record to set.void set(int, const User*);
        void set(int, const User&);

        /// @brief Set all records in the database at once.
        /// @param  users The array of users to write to the database.
        /// @param  cnt The number of records in the array that will be written to the database.
        void setAll(User*, int);

        /// @brief Delete the record at the given index in the database.
        /// @param pos The index position of the user record to delete.
        void del(int);

        /// @brief Delete all records in the database.
        void delAll();
        
        /// @brief Display all users
        void display();
    
    
};

#endif /* DATABASE_H */

