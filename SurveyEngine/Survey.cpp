/* 
 * File:   Survey.cpp
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 4:05 PM
 * Purpose: Survey Class Implementation
 */
#include <iostream>
#include "Survey.h"
using namespace std;

Survey::Survey() : surveyID(0), name(""), about(""), numQs(0) {
    questions = new Question[numQs];
    for(int i = 0; i < numQs; i++){
        questions[i] = Question();
    }
}

Survey::Survey(fstream& file) {
    load(file);
}

Survey::~Survey() {
    delete []questions;
    questions = nullptr;
}
//save to file
void Survey::save(fstream& file){
    //write the Id
    file.write(reinterpret_cast<char*>(&surveyID), sizeof(int));
    //name string
    int txtSize = name.size(); //get the size & write it
    file.write(reinterpret_cast<const char*>(&txtSize), sizeof(int));
    file.write(name.c_str(), txtSize); //now write the string
    //now the description
    txtSize = about.size();//get the size of description
    file.write(reinterpret_cast<const char*>(&txtSize), sizeof(int));
    file.write(about.c_str(), txtSize); //now write the string
    //now the number of questions
    file.write(reinterpret_cast<char*>(&numQs), sizeof(int));
    //now loop and write each question
    for(int i = 0; i < numQs; i++){
        questions[i].save(file);
    }  
}

//load from file
void Survey::load(fstream& file){
    //read the ID
    file.read(reinterpret_cast<char*>(&surveyID), sizeof(int));
    //name string
    int txtSize;    // for all the sizes
    file.read(reinterpret_cast<char*>(&txtSize), sizeof(int));
    name.resize(txtSize);  //size the string w/ null terminator
    file.read(&name[0],txtSize);   //and pop it in
    //about string
    file.read(reinterpret_cast<char*>(&txtSize), sizeof(int));
    about.resize(txtSize);  //size the string w/ null terminator
    file.read(&about[0],txtSize);   //and pop it in
    //num questions
    file.read(reinterpret_cast<char*>(&numQs), sizeof(int));
    //create the array
    questions = new Question[numQs];
    //individual questions
    for(int i = 0; i < numQs; i++){
        questions[i].load(file);
    }
}

//Helper for addAnswer - gets the input
Question& Survey::newQuestion(){
    //create a new object
    Question* newQ = new Question;
    //now get the options
    string input;  //holds the string
    char ch;       //hold the response
    int num;
    bool valid = false;    //to stop the loop
    //get the question
    cout << "Enter the question text: ";
    getline(cin,input);
    //and set the data
    newQ->setQText(input);
    //get the number of answers
    cout << "How many answers will this question have: ";
    cin >> num;
//    cin.ignore();
    //newQ->numAns = num;
    //now add the answers (creates the array and pushes answer to it - also changes numAns)
    for(int i = 0; i < num; i++){
        newQ->addAnswer();
    }
    //set the total responses always start at 0
    //find out what kind of answer it is
    cout << "Does this question only allow one response? (Y/N) ";
    do{
        cin >> ch;
        if(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N'){
            cout << "Invalid choice. Please re-enter.\n";
        } else { valid = true; }
    } while(!valid);
    //if preset, get the answer 
    if(ch == 'y' || ch == 'Y'){
    //    cout << "Setting type to false" << endl;
        newQ->setType(false);
    } else {
    //    cout << "Setting type to true" << endl;
        newQ->setType(true);
    }
    //return the new question
    cout << "Returning to add question." << endl;
    return *newQ;
}

//pushes question to survey
void Survey::addQuestion(){
    //make temp array 1 bigger
    Question *temp = new Question[numQs +1];
    //fill the existing elements
    for(int i = 0; i < numQs; i++){
        temp[i] = questions[i];
    }
    //put the latest answer at the end
    cout << "Adding new question" << endl;
    temp[numQs] = newQuestion();
    cout << "Temp Answer is: " << temp[0].getAnsTxt(0) << endl;
//    cout << "New question added." << endl;
    //increase the size
//    cout << "increasing size of numQs" << endl;
    numQs++;
    cout << "deleting old array" << endl;
    //delete the original
    delete [] questions;
    cout << "old array deleted" << endl;
    //set to the new array
    questions = temp;
    cout << "Reassigned answer is: " << questions[0].getAnsTxt(0) << endl;
    cout << "questions set to temp array" << endl;
}

//pops a question out of the survey
void Survey::delQuestion(int indx){
    //make a temp array 1 smaller
    Question *temp = new Question[numQs - 1];
    //check if the answer being removed is the first one
    if(indx != 0){
        //fill the existing elements before the one being removed
        for(int i = 0; i < indx; i++){
            temp[i] = questions[i];
        }
    }
    //now fill everything after the one removed
    for(int i = indx; i < numQs - 1; i++){
        temp[i] = questions[i+1];
    }
    //decrease the size
    numQs--;
    //delete the original
    delete [] questions;
    //set to the new array
    questions = temp;
}