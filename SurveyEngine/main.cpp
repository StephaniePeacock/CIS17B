/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 12:51 PM
 * Purpose: 
 */


//System Libraries
#include <iostream>
#include <fstream>
using namespace std;

//User Libraries
#include "Question.h"
//Global Constants - Math/Physics/Chemistry/Conversions Only

//Function Prototypes

//Execution Begins Here

int main(int argc, char** argv) {
    //create the question object
    string input;   //for getting all the things
    int num;        //for any numbers we need
    fstream test;
    Question q;
    //get the question text
    cout << "Enter the question: ";
    getline(cin,input);
    q.setQText(input);  //set it to the object
    //get the type of question
    cout << "Enter the question type. 1 for single choice, 2 for multi-choice, 3 for custom response: ";    
    cin >> num;
    q.setType(num);
    //get the number of answers
    cout << "How many answers will this question have: ";
    cin >> num;
    //now add the answers (creates the array and pushes answer to it)
    for(int i = 0; i < num; i++){
        q.addAnswer();
    }
    q.printQ();
    cout << "Enter the number of the answer you wish to delete: ";
    cin >> num;
    q.delAnswer(num-1);
    q.printQ();
    cout << "Writing to test file.\n";
    test.open("test.bin", ios::out | ios::binary);
    q.save(test);
    test.close();
    Question b;
    test.open("test.bin", ios::in |ios::binary);
    cout << "Loading from file.\n\n";
    b.load(test);
    cout << "Question from file:\n\n";
    b.printQ();
    //Exit Program    
    return 0;
}

