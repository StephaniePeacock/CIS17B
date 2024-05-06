/* 
 * File:   Survey.h
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 4:05 PM
 * Purpose: Survey Class Specification
 */
#include <fstream>
#include "Question.h"
using namespace std;

#ifndef SURVEY_H
#define SURVEY_H

class Question;

class Survey {
private:
    int surveyID;           //for serialization of files
    string name;            //name of the survey
    string about;           //survey description
    int numQs;              //number of questions in the survey
    Question* questions;    //dynamic array of questions
public:
    Survey();
    Survey(fstream&);
    virtual ~Survey();

    //Mutators
    void setID(int i)       { surveyID = i; }
    void setName(string n)  { name = n; }
    void setAbout(string a) { about = a; }
    void setNumQs(int n)    { numQs = n; }
    //Accessors
    int getID()             { return surveyID; }
    string getName()        { return name; }
    string getAbout()       { return about; }
    int getNumQs()          { return numQs; }
    Question& getQuestion(int indx) { return questions[indx]; }
    //Other Functions
    void save(fstream&);
    void load(fstream&);
    Question& newQuestion();    //helper for addQuestion - gets the question input
    void addQuestion();         //adds the question to the survey
    void delQuestion(int indx); //deletes a question from the survey
};

//For keeping track of the total number of surveys created
static int count;

#endif /* SURVEY_H */

