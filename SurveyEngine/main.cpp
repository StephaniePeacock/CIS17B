/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on May 4, 2024, 12:51 PM
 * Purpose: 
 */


//System Libraries
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//User Libraries
#include "Question.h"
#include "Survey.h"
//Global Constants - Math/Physics/Chemistry/Conversions Only

//Function Prototypes
void test();
//Execution Begins Here

int main(int argc, char** argv) {
//    test();
    
    //create the question object
    string input;   //for getting all the things
    int num;        //for any numbers we need
    char ch;        //for any chars
    bool valid = false;
    fstream test;
    Survey s;
    //get the survey name
    cout << "Enter the Survey name: ";
    getline(cin,input);
    s.setName(input);  //set it to the object
    //get the survey description
    cout << "Enter the Survey description: ";
    getline(cin,input);
    s.setAbout(input);  //set it to the object
    //add questions until the user stops
    do{
        do{
            cout << "Would you like to add a question? (Y/N)";
            cin >> ch;
            
            if(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N'){
                cout << "Invalid choice. Please re-enter: ";
            } else { valid = true; }
            cin.ignore();
        } while(!valid);
        //yes was picked, let's add a question! 
        if(ch == 'y' || ch == 'Y'){
            s.addQuestion();
        }
    }while (ch !='n' && ch != 'N');
    
    //print survey
    cout << "Survey ID  : " << s.getID() << endl
         << "Survey Name: " << s.getName() << endl
         << "Description: " << s.getAbout() << endl
         << "Num Queries: " << s.getNumQs() << endl;
    for(int i = 0; i < s.getNumQs(); i++){
        cout << "Question " << i+1 << ":" << endl;
        s.getQuestion(i).printQ();
        cout << endl;
    }
//    q.printQ();
//    cout << "Enter the number of the answer you wish to delete: ";
//    cin >> num;
//    q.delAnswer(num-1);
//    q.printQ();
//    cout << "Writing to test file.\n";
  test.open("surveys/"+to_string(s.getID())+".bin", ios::out | ios::binary);
    s.save(test);
    test.close();
    Survey b;
    test.open("surveys/"+to_string(s.getID())+".bin", ios::in |ios::binary);
    cout << "Loading from file.\n\n";
    b.load(test);
    cout << "Survey from file:\n\n";
    
    //for debug - let's make sure they are there
    //print survey
    cout << "Survey ID  : " << b.getID() << endl
         << "Survey Name: " << b.getName() << endl
         << "Description: " << b.getAbout() << endl
         << "Num Queries: " << b.getNumQs() << endl;
    for(int i = 0; i < b.getNumQs(); i++){
        cout << "Question " << i+1 << ":" << endl;
        b.getQuestion(i).printQ();
        cout << endl;
    }
    //remove("test.bin");
    //Exit Program    
    return 0;
}

void test(){
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
    test.open("surveys/test.bin", ios::out | ios::binary);
    q.save(test);
    test.close();
    Question b;
    test.open("surveys/test.bin", ios::in |ios::binary);
    cout << "Loading from file.\n\n";
    b.load(test);
    cout << "Question from file:\n\n";
    b.printQ();
    //remove("test.bin");
    //Exit Program    

}

