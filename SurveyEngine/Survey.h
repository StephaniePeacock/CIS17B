/* 
 * File:   Survey.h
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 4:05 PM
 * Purpose: Survey Class Specification
 */

using namespace std;

#ifndef SURVEY_H
#define SURVEY_H

class Survey {
private:
    string name;    //name of the survey
    string about;   //survey description
    int numQs;      //number of questions in the survey
    int* qIDs;      //dynamic array that links to the question locations
public:
    Survey();
    Survey(const Survey& orig);
    virtual ~Survey();

    //Mutators

    //Accessors

    //Other Functions
};

#endif /* SURVEY_H */

