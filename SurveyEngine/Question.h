/* 
 * File:   Question.h
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 12:52 PM
 * Purpose: Question Class Specification
 */
#include <string>
using namespace std;

#ifndef QUESTION_H
#define QUESTION_H

struct Answer {
    string aText;       // Answer text (prefilled or getline() if custom response)
    int chosen;         // Number of times this answer was chosen
    bool custom;        // If the response is a custom fill in from the user
};

class Question {
private:
//    streampos loc;      //byte location in the file
//    int size;           //used to calculate the next question's ID
    string qText;       //question text
    int numAns;         //for making the answers array
    Answer* answers;    //array of answer structs
    int totalResp;      // Total number of times the question is answered
    bool type;          //false = single choice, true = multiple choice

public:
    // Constructors
    Question();
    Question(const fstream&);
    // Destructor
    ~Question();
    // Accessors      
    string getQText() const     { return qText; }
    int getNumAns() const       { return numAns; }
    int  getSize();             
    int getTotalResp() const    { return totalResp; }
    bool getType() const        { return type; }

    // Mutators
    void setQText(const string& txt)    { qText = txt; }
    void addAnswer();           //pushes new answer to the survey
    void delAnswer(int);        //pops an answer out of the survey
    bool setType(bool t)                { type = t; return type;}
    //Other Functions
    void addResponse(int);
    void resetStatistics();
    Answer* newAnswer();        //helper for addAnswer()
    void printQ();
    void showResp();
    void save(fstream&);
    void load(fstream&);
};

//For keeping track of the number of records in the file
static int count;

#endif /* QUESTION_H */

