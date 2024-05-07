/* 
 * File:   Survey.cpp
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 4:05 PM
 * Purpose: Survey Class Implementation
 */
#include <iostream>
#include <fstream>
#include "Survey.h"
using namespace std;

Survey::Survey() : name(""), about(""), numQs(0) {
    questions = new Question[numQs];
    for(int i = 0; i < numQs; i++){
        questions[i] = Question();
    }
    fstream file("SurveyIDs.bin", ios::in | ios::out | ios::binary);
//debug    if (file.is_open()) { cout << "File is open." << endl; } else { cout << "File is not open." << endl; }
    int num = 0;
    int *temp, *surveys;        //so we can access these throughout
    file.seekg(0, ios::end);    //move to the end
    if(file.tellg() == 0){      //if the end is the beginning (aka file is empty)
        file.seekg(0,ios::beg); //go back to the beginning
        surveyID = 1;           //set the first ID that we can increment off of
        surveys = new int[1];   //only 1 element, so make an array of 1
        num++;
    } else {                    //not empty, so read in the file to get the last ID
        file.seekg(0,ios::beg); //go back to the beginning
        file.read(reinterpret_cast<char*>(&num), sizeof(int));//first get the size of the array
        temp = new int[num];    //now allocate memory
        file.read(reinterpret_cast<char*>(temp), num* sizeof(int));//and read in the existing elements
        for(int i = 0; i < num; i++){   //check if there's an available ID from a deleted survey first
            if(temp[i] > i+1){          //a survey was deleted
                surveyID = i+1;         //assign deleted number to current survey
                break;                  //no need to keep checking now, gtfo
            } else if (temp[i] == num) {//we ran through all the existing options
                surveyID = num+1;       //move to the next number
            }
        }
        surveys = new int[num+1];       //now make a new array to hold this ID
        for(int i = 0; i < num; i++) {  //copy the existing array in
            surveys[i] = temp[i];
        }
        surveys[num] = surveyID;        //now add the new ID
        num++;                          //increment num for the writing to file
        for(int i = 0;i < num-1; i++){  //sort the array - do the Mark sort!
            for(int j = i+1; j < num; j++){
                if(surveys[i] > surveys[j]){
                    surveys[i] = surveys[i]^surveys[j];
                    surveys[j] = surveys[i]^surveys[j];
                    surveys[i] = surveys[i]^surveys[j];
                }
            }
        }
    }
    file.seekp(0);//move to the beginning of the file to overwrite the data
    file.write(reinterpret_cast<char*>(&num), sizeof(int));//write the size to the file
    file.write(reinterpret_cast<char*>(surveys), num* sizeof(int));//now write the array
    file.close();//and close the file
    delete [] temp;//delete the arrays
    delete [] surveys;
    temp = nullptr;
    surveys = nullptr;
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
        newQ->setType(false);
    } else {
        newQ->setType(true);
    }
    //return the new question
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
    temp[numQs] = newQuestion();
    //increase the size
    numQs++;
    //delete the original
    delete [] questions;
    //set to the new array
    questions = temp;
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