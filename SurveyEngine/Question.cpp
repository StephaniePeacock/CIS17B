/* 
 * File:   Question.cpp
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 12:52 PM
 * Purpose: Question Class Implementation
 */
#include "Question.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

//default constructor
Question::Question() : qText(""), numAns(0), 
                       totalResp(0), type(false) {
    answers = nullptr;
    //answers = new Answer[numAns];
}
//constructor for loading from file
Question::Question(fstream& file){
    load(file);
}
// Copy constructor -- OMG this took so long to figure out I needed
Question::Question(const Question& other) : qText(other.qText), numAns(other.numAns), 
        totalResp(other.totalResp), type(other.type) {
    //copy the answers array
    answers = new Answer[numAns];
    for (int i = 0; i < numAns; ++i) {
        answers[i] = other.answers[i];
    }
}
//destructor
Question::~Question(){
    //delete the answers array
    delete [] answers;
    answers = nullptr;
    //decrement the count
}
//Helper for addAnswer - gets the input
Answer& Question::newAnswer(){
    //create a new structure
    Answer* newAns = new Answer;
    //now get the options
    string input;  //holds the string
    char ch;       //hold the response
    bool valid = false;    //to stop the loop
    //find out what kind of answer it is
    cout << "Is this a preset answer? (Y/N) ";
    do{
        cin >> ch;
        if(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N'){
            cout << "Invalid choice. Please re-enter\n";
        } else { valid = true; }
    } while(!valid);
    
    //if preset, get the answer 
    if(ch == 'y' || ch == 'Y'){
        cout << "Enter the answer text: ";
        cin.ignore();
        getline(cin,input);
        //and set the data
        newAns->aText = input;
        newAns->custom = false;
    } else {
        newAns->aText = "";
        newAns->custom = true;
    }
    //new answers always start with chosen 0
    newAns->chosen = 0;
    //return the new Answer
    return *newAns;
}
//pushes answer to the answers array
void Question::addAnswer(){
    //make a temp array 1 bigger
    Answer *temp = new Answer[numAns + 1];
    //fill the existing elements
    for(int i = 0; i < numAns; i++){
        temp[i] = answers[i];
    }
    //put the latest answer at the end
    temp[numAns] = newAnswer();
    //increase the size
    numAns++;
    //delete the original
    delete [] answers;
    //set to the new array
    answers = temp; 
}
//delete an answer
void Question::delAnswer(int indx){
    //make a temp array 1 smaller
    Answer *temp = new Answer[numAns - 1];
    //check if the answer being removed is the first one
    if(indx != 0){
        //fill the existing elements before the one being removed
        for(int i = 0; i < indx; i++){
            temp[i] = answers[i];
        }
    }
    //now fill everything after the one removed
    for(int i = indx; i < numAns - 1; i++){
        temp[i] = answers[i+1];
    }
    //decrease the size
    numAns--;
    //delete the original
    delete [] answers;
    //set to the new array
    answers = temp;
}
//prints the selected answer (for the user)
void Question::printQ(){
    cout << qText << endl;
    for(int i = 0; i < numAns; i++){
         cout << i+1 << ") " << answers[i].aText << endl;
    }
    cout << endl;
}
//for the admin, to see the Question's responses
void Question::showResp(){

}
//save the question to the file
void Question::save(fstream& file){
    //write the question text
    int txtSize = qText.size(); //get the size
    file.write(reinterpret_cast<const char*>(&txtSize), sizeof(int));
    file.write(qText.c_str(), txtSize); //now write the string
    //now the number of answers
    file.write(reinterpret_cast<char*>(&numAns), sizeof(int));
    //write each answer
    for (int i = 0; i < numAns; ++i) {
            txtSize = answers[i].aText.size();
            file.write(reinterpret_cast<char*>(&txtSize), sizeof(int));
            file.write(answers[i].aText.c_str(), txtSize);
            file.write(reinterpret_cast<char*>(&answers[i].chosen), sizeof(int));
            file.write(reinterpret_cast<char*>(&answers[i].custom), sizeof(bool));
        }
    //total number of responses
    file.write(reinterpret_cast<char*>(&totalResp), sizeof(int));
    //and the type
    file.write(reinterpret_cast<char*>(&type), sizeof(bool));
}
//load a question from a file
void Question::load(fstream& file){
    //load the question text
    int txtSize;    // for all the sizes
    file.read(reinterpret_cast<char*>(&txtSize), sizeof(int));
    qText.resize(txtSize);  //size the string w/ null terminator
    file.read(&qText[0],txtSize);   //and pop it in
    //now the number of answers
    file.read(reinterpret_cast<char*>(&numAns), sizeof(int));
    //create the array
    answers = new Answer[numAns];
    //now each answer
    for(int i = 0; i < numAns; i++){
        file.read(reinterpret_cast<char*>(&txtSize), sizeof(int));
        answers[i].aText.resize(txtSize); //size it
        file.read(&answers[i].aText[0], txtSize); //pop it in
        file.read(reinterpret_cast<char*>(&answers[i].chosen), sizeof(int));
        file.read(reinterpret_cast<char*>(&answers[i].custom), sizeof(bool));
        
        
    }
    //total responses
    file.read(reinterpret_cast<char*>(&totalResp), sizeof(int));
    //type
    file.read(reinterpret_cast<char*>(&type), sizeof(bool));
}
// Assignment operator - This took WAY too long to figure out I needed
Question& Question::operator=(const Question& other) {
    if (this != &other) {
        //copy all the things
        qText = other.qText;
        numAns = other.numAns;
        totalResp = other.totalResp;
        type = other.type;
        // Delete old answers array
        delete[] answers;
        //copy the answers array
        answers = new Answer[numAns];
        for (int i = 0; i < numAns; ++i) {
            answers[i] = other.answers[i];
        }
    }
    return *this;
}






//might use this later idk, it's here if I need it
int Question::getSize(){
    //add all the static stuff first
    int size = sizeof(qText) + sizeof(numAns) + sizeof(totalResp) + sizeof(type);
    //now add each answer to the size
    for (int i = 0; i < numAns; ++i) {
        size += answers[i].aText.size(); // Size of answer text
        size += sizeof(int);            // Size of chosen
        size += sizeof(bool);    
    }
    return size;
}

