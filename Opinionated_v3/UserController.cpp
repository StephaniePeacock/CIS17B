/* 
 * File:   UserController.cpp
 * Author: Stephanie Peacock
 * Created on April 29, 2024, 7:46 PM
 * Purpose: UserController Class Implementation
 */

#include <fstream>
#include "UserController.h"
#include "Generics.h"
using namespace std;

//inital menu - login, register, quit
void UserController::mainMenu(){
    char choice;
    bool quit = false;
    do {

        userView->prompt(1); // intro menu
        cin >> choice;
        switch(choice){
            case '1':
                login();
                break;
            case '2':
                reg();
                break;
            case '3':   
                quit = true;
                break;
            case 'a': 
                displayAll();   //Debug - display all Users
                break;
            case 'd':           //Debug - Reset Users.bin to empty
                file.open("Users.bin", ios::out | ios::binary | ios::trunc);
                file.close();
                break;
            case 's':           //Debug - display list of surveys
                printSurveyNames();
                break;
            case 'f':           //Debug - Reset SurveyIDs.bin to empty
                file.open("SurveyIDs.bin", ios::out | ios::binary | ios::trunc);
                file.close();
                break;
            case 'n': {         //Debug - create starter users
                displayAll();
                User admin("admin@no.com", "Password1", true, 10, 10,10);
                addUser(&admin);
                User a("no1@no.com", "Password1");
                addUser(&a);
                User b("no2@no.com", "Password1");
                addUser(&b);
                User c("no3@no.com", "Password1");
                addUser(&c);
                displayAll();
                break;
            }
            default: 
                userView->err(7);     break;        
        }
    } while (!quit);
}

//login menu                        ***DONE***
void UserController::login(){
    User user;
    string e,p;             // to hold the emails & pw till we verify
    cin.ignore();
    userView->prompt(2);    //ask for the email dummy
    getline(cin,e);         // get the email
    long int pos = find(e);
    if(pos < 0) {           //email was not found
        userView->err(9);
        return;             //go back to main menu
    }
    userView->prompt(3);    //ask for the password dummy
    getline(cin,p);         //get the password
    if(!verify(e,p)){       //input doesn't match file
        userView->err(10);
        return;             //go back to main menu
    }
    get(pos, &user);        //login was correct, assign
    if(!user.isAdmin()){    //see if user is admin
        userMenu(user);     //not admin, display user menu
    } else {
        char choice;
        bool quit = false;
        do{
            userView->prompt(6);
            cin >> choice;
            switch(choice){
                case '1':
                    adminMenu(user);
                    break;
                case '2': 
                    userMenu(user);
                    break;
                default: quit = true;
                break;
            }
        } while (!quit);  
    }
}

//shown if user is not admin, or admin selects (take survey, view account, change account, exit)
void UserController::userMenu(User& user){
    char choice;
    bool quit = false;
    do {
        userView->prompt(4);
        cin >> choice;      //get the choice dummy
        switch (choice) {
            case '1':       //Survey menu
                surveyMenu(user);
                break;
            case '2':       //displays user's info
                userView->display(user);
                break;
            case '3':       //exits if the user deletes acct
                if(!acctMenu(user)){    
                    quit = true; }
                break;
            case '4':       //exit to main menu
                quit = true;
                break;
            default:
                userView->err(7);
                break;
        }
    } while (!quit);  
}

//user can modify their account details - return false if user deletes account
bool UserController::acctMenu(User& user){
    char choice, sure;      //for inputs
    string e, p;            //to hold new em & pw
    bool quit = false;      //to exit menu w/o delete
    int pos = find(user.getEmail());    //for overwriting old data
    do{
        userView->prompt(7);
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case '1' :              //changing the email - need to redo file sort    
                enterEmail(e);      //get the new email
                user.setEm(e);      //copy email to user copy
                delUser(pos);       //delete original user from file
                addUser(&user);     //add the copy to file
                break;
            case '2' :
                enterPW(p);         //get new password
                user.setPw(p);      //copy password to user
                set(pos,user);      //update file
                break;
            case '3' :
                userView->prompt(8);        //double check
                cin >> sure;
                if(sure == 'Y' || sure == 'y'){
                    delUser(pos);
                    userView->prompt(9);    //removed
                    return false;           //force logout since user is gone
                } else { userView->prompt(10); }
                break;
            case '4' :
                quit = true;
                break;
            default: userView->err(7); break;
        }
    } while (!quit);
    //account wasn't deleted
    return true;
}

//shown if user is admin (Manage Users, Manage Surveys, View Users, View Surveys)
void UserController::adminMenu(const User& admin){
    string e;
    char choice;
    int num;
    bool stop = false;  //for outer loop
    do{
        bool quit = false;      //for inner loop
        userView->prompt(14);   //user or survey
        cin >> choice;
        switch(choice){
            case '1' :                          //Manage Users
                do{
                    userView->prompt(5);
                    cin >> choice;
                    switch(choice){
                        case '1':               //view all users            
                            displayAll();       
                            break;  
                        case '2':               //add user
                            reg();              
                            break;  
                        case '3':               //delete user
                        {
                            User user;                      //temp user
                            cin.ignore();
                            userView->prompt(2);
                            getline(cin,e);                  //get the email of the user we want to delete  
                            int pos = find(e);              //find position of user
                            if(e != admin.getEmail()){      //if not admin
                                pos = find(e);              //find user's position
                                if(pos != -1){
                                    get(pos, &user);        //copy data into the user
                                    delUser(pos);           //delete the user 
                                } else { 
                                    userView->err(9);       //user not found
                                }
                            } else { 
                                userView->err(11); 
                                cin >> choice;      //ask user if they want to exit
                                if(choice == 'y' || choice == 'Y') {
                                    quit = true;    
                                }
                            }
                            break;  
                        }
                        case '4': 
                            updateUser(admin);   //modify user menu
                            break;  
                        case '5': 
                            quit = true;        //Exit User Menu               
                            break;  
                        default: 
                            userView->err(7);   //invalid choice          
                            break;  
                    }
                } while (!quit);
                quit = false;                   //reset for other case
                break;
            case '2' :                          //Manage Surveys
                do {
                    quit = false;
                    userView->prompt(15);       //add, modify, delete, exit
                    cin >> choice;
                    switch(choice){
                        case '1' :              //View Survey Data     
                        {
                            printSurveyNames();         //get the options
                            num = getValidID();         //force valid choice
                            e = "surveys/" + to_string(num) + ".bin"; //get file name
                            file.open(e,ios::in | ios::out | ios::binary);    //open the correct file
                            Survey s(file);             //load survey from file
                            file.close();               //close file
                            userView->surveyInfo(s);    //display the data
                            break;
                        }
                        case '2' :              //Add Survey
                            cin.ignore();
                            addSurvey();
                            break;
                        case '3' :              //Modify Survey
                            printSurveyNames();         //get the options
                            num = getValidID();         //force valid choice
                            break;
                        case '4' :              //Delete Survey
                                printSurveyNames();         //get the options
                                num = getValidID();         //force valid choice
                                deleteSurvey(num);          //delete selected
                            break;
                        case '5' :              //Exit Survey Menu
                            quit = true;
                            break;
                        default: 
                            userView->err(7);   //invalid choice          
                            break;
                    }
                } while(!quit);
                quit = false;                   //reset for other case
                break;
            case '3' : stop = true;             //Exit Admin Menu
                break;
            default: 
                userView->err(7);               //invalid choice          
                break; 
        }
    } while (!stop);
} 

//admin can't modify themselves in this menu - modified my code from Battleship
void UserController::updateUser(const User admin){
    //if email isn't changed then re-save to same position
    char choice;
    int num, pos;
    bool quit = false;
    User user;
    string input;
    userView->prompt(13);    //get email we want to change
    cin.ignore();
    getline(cin, input);
    if(input != admin.getEmail()){  //make sure we're not trying to change the admin account
        pos = find(input);              //find user's position
        if(pos != -1){                  //user is found
            get(pos, &user);            //copy data into the user
            do {    
                userView->prompt(11);       //menu to pick what to change
                cin >> choice;
                cin.ignore();
                switch(choice){
                    case '1' :              //change email - need to redo save
                        enterEmail(input);  //get the new email
                        user.setEm(input);  //copy email to user copy
                        delUser(pos);       //delete original user from file
                        addUser(&user);     //add the copy to file
                        quit = true;        //back out, since pos is changed
                        break;
                    case '2':               //change pw
                        enterPW(input);     //get new password
                        user.setPw(input);  //copy password to user
                        set(pos,user);      //update file
                        break;
                    case '3' :               //swap admin status
                        user.changeAdmin();
                        set(pos,user);      //update file
                        break;
                    case '4':               //change numS
                        userView->prompt(12);
                        cin >> num;
                        user.setNumS(num);
                        set(pos,user);      //update file
                        break;
                    case '5':                   //change numQ
                        userView->prompt(12);
                        cin >> num;
                        user.setNumQ(num);
                        set(pos,user);      //update file
                        break;
                    case '6' :                  //change Rank
                        userView->prompt(12);
                        cin >> num;
                        user.setRank(num);
                        set(pos,user);      //update file
                        break;
                    case '7' :
                        quit = true;
                    default: userView->err(7);  //invalid
                        break;     
                }
            } while(!quit);
        } else { 
            userView->err(9);        //user not found
        }   
    } else { 
        userView->err(11);  //admin can't change self
        cin >> choice;      //ask user if they want to exit
        if(choice == 'y' || choice == 'Y') {
            return;    
        }
    }
 
}

//user access to the surveys        *** TO DO ***************************************
void UserController::surveyMenu(User& user){

}

//splitting for updating            ***DONE***
void UserController::enterEmail(string& e){
    userView->prompt(2);        // ask for email
    int pos;
    
 //   getline(cin,e);         //get the email
 //   cin.ignore();
    while (e.length() < 7 || e.length() > user::MAX-1 || !checkEm(e) || pos != -1){
        getline(cin,e);         //get the email
        pos = find(e);          //to check for duplicates
        if(e.length() < 7){     //make sure its not too small
            userView->err(1);   //tell user its too small (lol)
        }
        if(e.length() > user::MAX-1){    //make sure it's not too big
            userView->err(2);   //tell user it's too big (that's what she said)
        }
        if(!checkEm(e)){        //size is good but wrong email format
            userView->err(3);
        }
        if(pos != -1){      
            userView->err(8);   //email exists - can't reuse!
        }    
    } 
}

//splitting for updating            ***DONE***
void UserController::enterPW(string& p){
    //now get the password
    userView->prompt(3);    //ask for password
    do{
        getline(cin,p);         //get the password   
        if(p.length() < 7){ //make sure its not too small
            userView->err(1);   //tell user its too small (lol)
        }
        if(p.length() > user::MAX-1){//make sure it's not too big
            userView->err(2);   //tell user it's too big (that's what she said)
        }
        //err prompts are in the checkEm function
    } while (p.length() < 7 || p.length() > user::MAX-1 || !checkPw(p)); //go till it fits
}

//So we can be D.R.Y.               ***DONE***
void UserController::getInfo(string& e, string& p){
    enterEmail(e);  //get email entry
    enterPW(p);     //get password entry    
}

//create a new user                 ***DONE***
void UserController::reg(){
    string e,p;         // to hold the emails & pw till we verify
    cin.ignore();
    getInfo(e,p);       // get the inputs
    User user(e,p);     //make the user
    addUser(&user);     //add user to file
}

//force valid style email           ***DONE***
bool UserController::checkEm(string& em){
    /*Regular expression! declare the pattern first
    * checks local for no . at start or end, no double dots
    * then checks for at exactly 1 @ 
    * lastly checks domain for no . at start or end
    * and at least 2 letters after the last . for top level domain  */
    const regex pattern(R"(\b[A-Za-z0-9_][A-Za-z0-9._-]*[A-Za-z0-9]@[A-Za-z0-9-]+(?:\.[A-Za-z0-9-]+)*(?:\.[A-Z|a-z]{2,}\b))");
    //now check if the email matches the pattern and return it
    return regex_match(em, pattern);
}

//password requirements             ***DONE***
bool UserController::checkPw(string& pw){
    //initialize all to false
    bool valid = false;
    bool upper = false;
    bool lower = false; 
    bool num   = false;
    //verify we have upper, lower, and number - check all at once!
    for(char ch : pw){
        if(isupper(ch)){ upper = true; }
        if(islower(ch)){ lower = true; }
        if(isdigit(ch)){ num   = true; }
    }
    //we met all criteria, set to true
    if(upper && lower && num) { valid = true; }
    //missing something
    if(!upper) { userView->err(4); }
    if(!lower) { userView->err(5); }
    if(!num)   { userView->err(6); }
    //send it back baby
    return valid;
}

//verify user's login info is correct ***DONE***
bool UserController::verify(string em, string pw){
    bool valid = false;
    int pos = -1;
    //check all records for em - opens inside find
    pos = find(em);
    if (pos > -1) {
        //user found - check if password matches
        User user;
        get(pos, &user);
        if (user.getPword() == pw) {
            valid = true;
        }
    }
    return valid;
}

//delete a user                         ***DONE***
void UserController::delUser(int pos) {
    //open the file
    file.open("Users.bin", ios::in | ios:: out | ios::binary);
    int total = count();                    //get current number users
    file.seekp(0, ios::beg);                //GO TO BEGINNING
    User *temp = new User[total-1];         //make 1 less than current
    for(int i = 0; i < pos; i++){           //copy to position to delete
        file.read(reinterpret_cast<char*>(&temp[i]), sizeof(User));
    }
    file.seekp(sizeof(User), ios::cur);     //move past current one
    for(int i = pos; i < total - 1 ; i++) { //copy in the stuff after pos
        file.read(reinterpret_cast<char*>(&temp[i]), sizeof(User));
    }
    file.close();
    file.open("Users.bin", ios:: out | ios::binary | ios::trunc);
    file.close();
    file.open("Users.bin", ios::in | ios:: out | ios::binary);
    file.seekp(0, ios::beg);                //GO TO BEGINNING
    for(int i = 0; i < total - 1; i++){     //write the users back
        file.write(reinterpret_cast<char*>(&temp[i]), sizeof(User));
    }
    delete []temp;                          //delete the temp array now
    file.close();                           //close the file  
}

//add user to file                      ***DONE***
void UserController::addUser(const User* user){
    //open the file
    file.open("Users.bin", ios::in | ios:: out | ios::binary);
    int total = count();            //read in the current users to get total users  
    User *temp = new User[total+1]; //allocate the memory
    file.seekp(0, ios::beg);        //GO TO BEGINNING
    for(int i = 0; i < total; i++){ //add the users to the array
        file.read(reinterpret_cast<char*>(&temp[i]), sizeof(User));
    }
    temp[total] = *user;            //add the new user to the end
    total++;                        //increase size
    sort(total,temp);               //sort it
    file.seekp(0, ios::beg);        //go to beginning
    for(int i = 0; i < total; i++){ //write the users back
        file.write(reinterpret_cast<char*>(&temp[i]), sizeof(User));
    }
    delete []temp;                  //delete the temp array now
    file.close();                   //close the file
}  

//display all user data (for admin)     ***DONE***
void UserController::displayAll(){
    file.open("Users.bin", ios::in | ios::binary);  //open file
    int total = count();                            //get num of users
    file.seekg(0L, ios::beg);                        //go back to the beginning of file
    User* users = new User[total];                  //allocate memory
    for (int i = 0; i < total; ++i) {               //read in all & display
        file.read(reinterpret_cast<char*>(&users[i]), sizeof(User));
        userView->display(users[i]);                //print current user
    }
    file.close();
    if(file.is_open()){
        cout << "error closing file\n";
    }
}

//so users are sorted in the file       ***DONE***
void UserController::sort(int total, User* old){
    for(int i = 0;i < total-1; i++){
        for(int j = i+1; j < total; j++){
            if(old[i] > old[j]){
                User temp = old[i];
                old[i] = old[j];
                old[j] = temp;               
            }
        }
    }
}

//add a survey
void UserController::addSurvey(){
    string input;   //for getting all the things
    int num;        //for any numbers we need
    char ch;        //for any chars
    bool valid = false;
    Survey s;
    //get the survey name
    userView->prompt(16);
    getline(cin,input);
    s.setName(input);  //set it to the object
    //get the survey description
    userView->prompt(17);
    getline(cin,input);
    s.setAbout(input);  //set it to the object
    //add questions until the user stops
    do{
        do{
            userView->prompt(18);
            cin >> ch;
            
            if(ch != 'y' && ch != 'Y' && ch != 'n' && ch != 'N'){
                userView->err(7);   //invalid choice 
            } else { valid = true; }
            cin.ignore();
        } while(!valid);
        //yes was picked, let's add a question! 
        if(ch == 'y' || ch == 'Y'){
            s.addQuestion();
        }
    }while (ch !='n' && ch != 'N');
    file.open("surveys/"+to_string(s.getID())+".bin", ios::out | ios::binary);
    s.save(file);
    file.close();
}

//delete a survey
void UserController::deleteSurvey(int num){
    file.open("SurveyIDs.bin", ios::in | ios::out | ios::binary);
    int numSurveys;
    file.read(reinterpret_cast<char*>(&numSurveys), sizeof(int));
    int *temp = new int[numSurveys-1];  //1 smaller than current
    for(int i = 0; i < num; i++){       //read in before
        file.read(reinterpret_cast<char*>(&temp[i]), sizeof(int));
    }
    file.seekp(sizeof(int), ios::cur);  //skip the one to delete
    for(int i = num; i < numSurveys -1; i++){
        file.read(reinterpret_cast<char*>(&temp[i]), sizeof(int));
    }
    file.close();               //close the file so we can empty it
    file.open("SurveyIDs.bin", ios::out | ios::binary | ios::trunc);
    file.close();               //close empty file
    file.open("SurveyIDs.bin", ios::in | ios::out | ios::binary);
    file.seekp(0, ios::beg);    //go to beginning
    numSurveys--;               //remove extra then write to file
    file.write(reinterpret_cast<char*>(&numSurveys), sizeof(int));
    for(int i = 0; i < numSurveys; i++){  //write array to file
        file.write(reinterpret_cast<char*>(&temp[i]), sizeof(int));
    }
    file.close();               //close the file
    delete []temp;              //clean up the garbage
    //now we need to remove survey file from directory
    remove(("surveys/" + to_string(num) + ".bin").c_str());
}

//choose a survey to modify
void UserController::modifySurvey(int num){
    char choice;
    int q = -1;
    bool quit = false;
    file.open("surveys/" + to_string(num) + ".bin", ios::in | ios::out | ios::binary);
    Survey s(file); //load survey from file
    file.close();
    do {
        userView->prompt(20);
        cin >> choice;
        switch(choice){
            case '1' :                      //Modify question
                userView->showSurvey(s);              //print the survey
                while(q < 0 || q > s.getNumQs()){    
                    userView->prompt(20);   //get question number
                    cin >> q;
                    if(q < 0 || q > s.getNumQs()) {
                        userView->err(7);   //invalid choice
                    }
                }
                s.modifyQuestion(q-1);
                break;
            case '2' :                      //add question
                s.addQuestion();
                break;
            case '3' :                      //delete question
                userView->showSurvey(s);              //print the survey
                while(q < 0 || q > s.getNumQs()){    
                    userView->prompt(20);   //get question number
                    cin >> q;
                    if(q < 0 || q > s.getNumQs()) {
                        userView->err(7);   //invalid choice
                    }
                }
                s.delQuestion(q-1);
                break;
            case '4' :                      //exit Menu
                quit = true;
                break;
            default : userView->err(7);     //invalid choice
                break;       
        }
    } while(!quit);
}

//print IDs and names for all existing surveys ***DONE***
void UserController::printSurveyNames() {
    file.open("SurveyIDs.bin", ios::in | ios::binary);
    int numSurveys, nameSize, surveyID; 
    string fileName, surveyName;
    fstream surveyFile;
    file.read(reinterpret_cast<char*>(&numSurveys), sizeof(int));
    
    for (int i = 0; i < numSurveys; ++i) {
        //read in survey ID
        file.read(reinterpret_cast<char*>(&surveyID), sizeof(int));
        fileName = "surveys/" + to_string(surveyID) + ".bin";   // set filename
        surveyFile.open(fileName, ios::in | ios::binary);       //open file
        surveyFile.seekg(sizeof(int), ios::cur);  //position the pointer past the survey ID
        //read survey name from the survey file
        surveyFile.read(reinterpret_cast<char*>(&nameSize), sizeof(int));
        
        surveyName.resize(nameSize);        //size the string w/ null terminator
        surveyFile.read(&surveyName[0], nameSize);  //and pop it in
        cout << surveyID << ") " << surveyName << endl;
        surveyFile.close();                         //close the survey file
    }
    file.close();       //close the index file
}

//force user to pick a survey that exists
int UserController::getValidID(){
    int choice, numSurveys, surveyID;
    bool valid = false, found = false;
    while(!valid){
        userView->prompt(19);   //ask for input
        cin >> choice;          //get the chosen ID
        file.open("SurveyIDs.bin", ios::in | ios::binary); //open file
        //get number of surveys
        file.read(reinterpret_cast<char*>(&numSurveys), sizeof(int));
        for (int i = 0; i < numSurveys; ++i) {  //check all IDs
            file.read(reinterpret_cast<char*>(&surveyID), sizeof(int));
            if (surveyID == choice) {   //ID matches choice
                found = true;           //we found it!
                break;                  //gtfo
            }
        }
        file.close();   //close index file
        found ? valid = true : valid = false, userView->err(7);    //gtfo if found or err if invalid
    }
    return choice;
}


/*************************************************
 * Borrowed from Battleship with Hannes approval *
 *************************************************/

//get the number of records in the file
int UserController::count() {
    int fbytes = size();        // Get size of file
    int rbytes = sizeof(User);  // Get size of record
    // Calculate and return number of records in database
    return fbytes / rbytes;
}

//helper for find() and count() - gets total size of file
long int UserController::size() {
    file.seekg(0L, ios::end);
    return file.tellg();
}

//get a user from the file at specific position
void UserController::get(int pos, User* user){
    file.open("Users.bin", ios::in | ios::binary);
    long int cur = pos * sizeof(User);
    file.seekg(cur, ios::beg);
    file.read(reinterpret_cast<char*>(user), sizeof(User));
    file.close();
}

//overwrite current user data at position
void UserController::set(int pos, const User& user){
    file.open("Users.bin", ios::in | ios::out | ios::binary);
    long int cur = pos * sizeof(User);
    file.seekp(cur, ios::beg);
    file.write(reinterpret_cast<const char*>(&user), sizeof(User));
    file.flush();
    file.close();
}  

//finds position of user in file - modified a bit from Hannes
int UserController::find(string email) {
    //open file
    file.open("Users.bin", ios::in | ios:: out | ios::binary);
    int i = 0;          //temp counter at 0
    int pos = -1;       //post starts a -1 in case not found
    int end = count();  //so we know when to stop
    User current;       //temp user
    file.seekg(0L, ios::beg);   //reset to the beginning
    while (i < end) {   //go until found or file reaches end
        file.read(reinterpret_cast<char*>(&current), sizeof(User));
        if (current.getEmail() == email) {  //account found
            pos = i;
            break; 
        }
        if (current.getEmail() > email) {   //we've passed the spot it could be
            break;
        }
        i++;            //not found, increment i
    }
    file.close();       //close file
    return pos;
}


