#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>
#include <future>
#include <cctype>
#include <regex>


#include "project.hpp"
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"
#include "jira.hpp"


using namespace std;

//default construtor
Jira::Jira() {
    this->time = 0;
    this->userName = "";
    this->projects = vector<Project*>();
    users = vector<TeamMember*>();
}

//delegating constructor
Jira::Jira(int time, string currentUser, vector<Project*> projects, vector<TeamMember*> users) {
    this->time = time;
    this->projects = projects;
    this->users = users;
    // Regardless of there is a program or not, when program is run, we need someone to sign in, so initialize as null
    this->userName = currentUser;
}

//
Jira::Jira(const Jira &j) {
    time = j.getTime();
    userName = j.getUserName();
    projects = j.getProjects();
    users = j.getUsers();
}

void Jira::signIn() {
    string userEmail, myText;
    cout <<"Enter username: " << endl;
    cin >> userEmail;
    bool found = false;
    
    for(int i = 0; i < this->users.size(); i++) {
        if(isUserUsed(userEmail)) {
            found = true;
        }
    }
    
    if(found == true) {
        this->setUserName(userEmail);
        displayJiraHome();
    }
    else {
        cout<<"Users not found."<<endl;
        cout<<"Please sign up."<<endl;
        createAccount();

    }
}

void Jira::displaySignInUp() {
    int option = 0;
    cout << "1) Sign in" << endl;
    cout << "2) Sign up" << endl;
    cout<<"Please choose options."<<endl;
    cin>>option;
    
    while (option != 1 && option != 2) {
        cout << "Invalid option. Try again: "<<endl;
        cin >> option;
    }
    if (option == 1) {
        signIn();
    }
    else {
        createAccount();
    }
}


void Jira::displayJiraHome() {
    int menuOption = 0;
    
    while(menuOption != 14) {
        cout<<endl;
        cout << "Current Time: " << getTime() << endl;
        cout<<"These are menu options. -------------------"<<endl;
        cout<<"1) Load previous projects. "<<endl;
        cout<<"2) Save current projects. "<<endl;
        cout<<"3) Log out."<<endl;
        cout<<"4) View all of your projects. "<<endl;
        cout<<"5) View specific project and its details. "<<endl;
        cout<<"6) Create new project (you will be the project owner for this project)."<<endl;
        cout<<"7) Create new issue. "<<endl;
        cout<<"8) Work on issue. (Sprint simulation)."<<endl;
        cout<<"9) Update your project status. "<<endl;
        cout<<"10) Update your issue status. "<<endl;
        cout<<"11) Assign a member to an issue."<<endl;
        cout<<"12) Delete your project. "<<endl;
        cout<<"13) Delete your issue. "<<endl;
        cout<<"14) Quit (would not save the current project, please save if needed). "<<endl;
        updateAllStatus();
        
        cin>>menuOption;
        
        while(menuOption > 14 || menuOption < 1) {
            cout<< "Please select a menu option.\n";
            cin>> menuOption;
        }
        if(menuOption == 1) {
            
        }
        
        else if(menuOption == 2) {
            
        }
        
        //Log out.
        else if(menuOption == 3) {
            logOut();
            displaySignInUp();
        }
        
        //View all of your projects.
        else if(menuOption == 4) {
            displayUserPj();
        }
        
        //View specific project and its details.
        else if(menuOption == 5) {
            displayUserGivenPj();
        }
        
        //Create new project.
        else if(menuOption == 6) {
            createProject();
        }
        else if(menuOption == 7) {
            createIssueJira();
        }

        //Move Issue
        else if(menuOption == 8) {
            sprintSimulation();
        }
        
        else if (menuOption == 9) {
            updateGivenProject();
        }
        else if(menuOption == 10) {
            updateIssueJira();
        }
        else if(menuOption == 11) {
            assignIssueJira();
        }
        else if(menuOption == 12) {
            deleteGivenProject();
        }
        else if(menuOption == 13) {
            deleteGivenIssue();
        }
    }
//    if(menuOption == 11) {
//        exit(0);
//    }
}

void Jira::displayUserPj() {
    int projCount = 0;
    cout << "Here is a list of projects you are involved in and your role: " << endl;
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->hasUser(this->userName)) {
            projCount++;
            cout<<"PID: "<<projects[i]->getProjectID()<<endl
            <<"PName: "<<projects[i]->getProjectName()<<endl
            <<"Time frame: "<<projects[i]->getProjectDeadline()<<endl;
            cout<<"List of ToDo Issue --- ";
            cout<<"Total issues: "<<projects[i]->getTodo().size()<<endl;

            cout<<endl;
            cout<<"List of Sprints in progress --- ";
            cout<<"Total sprints: "<<projects[i]->getInProgress().size()<<endl;
            
            cout<<endl;
            cout<<"List of Work done --- ";
            cout<<"Total issues: "<<projects[i]->getDone().size()<<endl;
            
            cout<<endl;
            cout<<"Project Owner: "<<projects[i]->getProjectOwner().getUsername()<<endl;
            cout<<"Project lead(s): ";
            for(int k = 0; k < projects[i]->getProjectLeads().size(); k++) {
                cout<<projects[i]->getProjectLeads().at(k)->getUsername()<<", ";
            }
            cout<<endl;
            cout<<"Team developer(s): ";
            for(int z = 0; z < projects[i]->getTeamDevelopers().size(); z++) {
                cout<<projects[i]->getTeamDevelopers().at(z)->getUsername()<<", ";
            }
            cout<<endl;
        }
    }
    if(projCount == 0) {
        cout<<"You are currently not in any project."<<endl;
    }
}

//print the specific project the user is involved in and wants to see
void Jira::displayUserGivenPj() {
    int givenPrj;
    vector<Project*> userProjs;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->hasUser(this->userName)) {
            userProjs.push_back(projects[i]);
        }
    }

    cout<<"All of the projects you are involved: ";
    for(int i = 0; i < userProjs.size(); i++) {
        cout<<" PID - "<<userProjs[i]->getProjectID()<<", ";
    }
    cout<<endl;
    cout<<"Please enter the project ID you want to view."<<endl;
    cin>>givenPrj;
    bool found = false;
    for(int i = 0; i < userProjs.size(); i++) {
        if(givenPrj == userProjs[i]->getProjectID()) {
            cout<<*userProjs[i];
            found = true;
        }
    }
    if(found == false) {
        cout<<"This project ID is not found"<<endl;
    }
}

//to create new account and update vector of teamMembers in Jira and main
//if successfully created acc, user will go to displayJiraHome
//else continue enter new username
void Jira::createAccount() {
    string newAcc;
    cout<<"Please enter the new username."<<endl;
    cin.ignore();
    getline(cin, newAcc);

    while(isUserUsed(newAcc)) {
        cout<<"The given username is unavailable. Please try again!"<<endl;
        cout<<"Please enter the new username."<<endl;
        cin>> newAcc;
    }
    TeamMember* newUser = new TeamMember(newAcc);
    this->users.push_back(newUser);
    users.push_back(newUser);
    cout<<"Successfully created new account."<<endl;
    displayJiraHome();
}


bool Jira::isUserUsed(string givenUsername) {
    bool unavailable = false;
    for(int i = 0; i < users.size(); i++) {
        if(givenUsername == users[i]->getUsername()) {
            unavailable = true;
        }
    }
    return unavailable;
}

void Jira::logOut() {
    this->userName = "";
}

void Jira::createProject() {
    regex e ("^-?\\d+");
    string projectLeadSize = "-1";
    string developerSize = "-1";
    string deadline = "-1";
    string projName;
    cout<<"Please give the name of the project."<<endl;
    cin.ignore();
    getline(cin, projName);

    
    while (!(regex_match(deadline,e)) || stoi(deadline) < 1) {
        cout<<"Please give the duration of the project (number of days)."<<endl;
        getline(cin, deadline);
    }



    // Make sure that there are enough users for requested number of project leads
    while (!(regex_match(projectLeadSize,e)) || stoi(projectLeadSize) < 1 || stoi(projectLeadSize) > users.size()) {
        cout<<"Please give the number of leads you'd like on the project."<<endl;
        getline(cin, projectLeadSize);
        if ((regex_match(projectLeadSize,e)) && stoi(projectLeadSize) > users.size()) {
            cout << "You do not have enough organization members for that many leads. You have: " << users.size() << " organization members." << endl;
        }
    }

    cout<<"Please choose the following users to be your project lead(s)."<<endl;
    for(int i = 0; i < users.size(); i++) {
        if(users[i]->getUsername() != this->userName) {
            cout<<users[i]->getUsername()<<", ";
        }
    }
    cout<<endl;
    
    vector<TeamMember*> prjLeads;
    while (prjLeads.size() < stoi(projectLeadSize)) {
        cout<<"Please enter the name of the user for project leads."<<endl;
        string name;
        getline(cin, name);
        bool realUser = false;
        for(int i = 0; i < users.size(); i++) {
            if(name == users[i]->getUsername()) {
                realUser = true;
                // Make sure we haven't added them already
                bool duplicate = false;
                for (int j = 0; j < prjLeads.size(); j++) {
                    if (prjLeads.at(j)->getUsername() == name) {
                        duplicate = true;
                    }
                }
                if (!duplicate) {
                    prjLeads.push_back(users[i]);
                } else {
                    cout << "User already added." << endl;
                }    
            }
        }
        if (!realUser) {
            cout << "Invalid username entered. Try again: " << endl;
        }
    }

    
    cout<<"Project lead(s): ";
    for(int j = 0; j < prjLeads.size(); j++) {
        cout<<prjLeads[j]->getUsername()<<", ";
    }
    cout<<endl;

    // Make sure that there are enough users for requested number of project leads
    while (!(regex_match(developerSize,e)) || stoi(developerSize) < 1 || stoi(developerSize) > users.size()) {
        cout<<"How many developer(s) do you want to include in this project?"<<endl;
        cin>>developerSize;
    }
    
    cout<<"Please choose the other users to be your developers."<<endl;

    vector<TeamMember*> developers;
    // Issues with input stream reading in \n after first try
    bool firstTime = true;
    while (developers.size() < stoi(developerSize)) {
        cout<<"Please enter the name of the user for developer."<<endl;
        string name;
        if (firstTime) {
            cin.ignore();
            firstTime = false;
        }
        getline(cin, name);
        bool realUser = false;
        for(int i = 0; i < users.size(); i++) {
            if(name == users[i]->getUsername()) {
                realUser = true;
                // Make sure we haven't added them already
                bool duplicate = false;
                for (int j = 0; j < developers.size(); j++) {
                    if (developers.at(j)->getUsername() == name) {
                        duplicate = true;
                    }
                }
                if (!duplicate) {
                    developers.push_back(users[i]);
                } else {
                    cout << "User already added." << endl;
                }    
            }
        }
        if (!realUser) {
            cout << "Invalid username entered. Try again: " << endl;
        }
    }

    cout<<"Team Developer(s): ";
    for(int i = 0; i < developers.size(); i++) {
        cout<<developers[i]->getUsername()<<", ";
    }
    cout<<endl;

    vector<Sprint*> listOfSprints;
    string another = "y";

    while(tolower(another.at(0)) == 'y') {
    vector<Issue*> problems;
    Sprint* sprint1 = new Sprint(0, 0, problems);
    string timeFrame = "-1";
    while (!(regex_match(timeFrame,e)) || stoi(timeFrame) < 1) {
        cout<<"Please give a due date for this sprint."<<endl;
        getline(cin, timeFrame);
    }
    sprint1->setDueDate(stoi(timeFrame));
    listOfSprints.push_back(sprint1);
    cout<<"\nEnter another sprint? (y/n)"<<endl;
    getline(cin, another);
    cout<<endl;
    }
    vector<Issue*> listOfTodo;
    vector<Issue*> listOfDone;

    cout << "Project added." << endl;
    Project* project1 = new Project(projName, stoi(deadline), listOfTodo, listOfSprints,listOfDone, this->userName, prjLeads, developers);

    this->projects.push_back(project1);
}

void Jira::createIssueJira() {
    int givenPID;
    cout<<"Please provide the projectID that you want to create an issue"<<endl;
    cin>>givenPID;
    bool created = false;
    
    for(int i = 0; i <projects.size(); i++) {
        if(givenPID == projects[i]->getProjectID()) {
            projects[i]->createIssue(userName, this->users);
            created = true;
        }
    }
    if(created == true) {
        cout<<"Succesfully created an issue in this project!"<<endl;
    }
    else {
        cout<<"Not successfully created an issue in this project!"<<endl;
    }
}
void Jira::deleteGivenIssue() {
    int givenPID;
    cout<<"Please provide the projectID you want to delete its issue."<<endl;
    cin>>givenPID;
    
    for(int i = 0; i < projects.size(); i++) {
        if(givenPID == projects[i]->getProjectID()) {
            int issueID;
            cout<<"Please provide the issueID you want to delete."<<endl;
            cin>> issueID;
            projects[i]->deleteIssue(userName, issueID);
        }
    }
}

void Jira::moveGivenIssue() {
    int givenPID;
    cout<<"Please provide the projectID you want to move its issue."<<endl;
    cin>>givenPID;
    
    for(int i = 0; i < projects.size(); i++) {
        if(givenPID == projects[i]->getProjectID()) {
            int issueID;
            cout<<"Please provide the issueID you want to move."<<endl;
            cin>> issueID;
            projects[i]->moveIssue(userName, issueID);
        }
    }
}

// saves current state of the project
void Jira::saveJira(){
        ofstream jira;
        cout << "Save Current State\n\n";
        jira.open("jira.txt");
        if(jira.is_open()) {
            jira << "Time: " << time << endl;
            jira << "Username: " << userName;
    vector<TeamMember*> users;
    for (int i = 0; i < projects.size(); i++) {
            jira << "Projects : " << endl;
            projects[i]->savedOutput();
          }
          for (int i = 0; i < users.size(); i++) {
              jira << "Users: " << endl;
              jira << users[i]->getUsername() << endl;}
 
     }
     jira.close();
}

// opens current state of the project based on text file
void Jira::openJira(){}

/*string savedOutput = ""
for (projec : projects) {
    savedOutput += project.getSave()
}*/

void Jira::sprintSimulation() {
    bool run = true;
    cout << getTime() << endl;
    string option = "";
    while (run) {
        cin.clear();
        cout << "1) Work on issues (increases current time)" << endl; 
        cout << "2) Move issue" << endl; 
        cout << "3) Exit" << endl; 
        cout << "Enter your option: " << endl;
        cin >> option;
        if (option == "1") {
            incrementTime();
        } else if (option == "2") {
            moveGivenIssue();
        } else {
            run = false;
        }
        updateAllStatus();
    }
}

void Jira::updateAllStatus() {
    // Handle sprints first in case anything gets sent back to todo
    for (int i = 0; i < projects.size(); i++) {
        for (int j = 0; j < projects.at(i)->getInProgress().size(); j++) {
            // If sprint is due, dump all items into todo
            if (this->time > projects.at(i)->getInProgress().at(j)->getDueDate()) {
                projects.at(i)->dumpSprint(projects.at(i)->getInProgress().at(j)->getSprintID());
            } 
            else {
                for (int k = 0; k < projects.at(i)->getInProgress().at(j)->getIssues().size(); k++) {
                    if (projects.at(i)->getInProgress().at(j)->getIssues().at(k)->getCurrentTime() > this->time) {
                        projects.at(i)->getInProgress().at(j)->getIssues().at(k)->setStatus("overdue");
                    } else {
                        projects.at(i)->getInProgress().at(j)->getIssues().at(k)->setStatus("in progress");
                    }
                    projects.at(i)->getInProgress().at(j)->getIssues().at(k)->setCurrentTime(this->time);
                }
            }
        }
        // Handle todo items
        for (int j = 0; j < projects.at(i)->getTodo().size(); j++) {
            projects.at(i)->getTodo().at(j)->setCurrentTime(time);
            if (projects.at(i)->getTodo().at(j)->getCurrentTime() > this->time) {
                projects.at(i)->getTodo().at(j)->setStatus("overdue");
            } else {
                projects.at(i)->getTodo().at(j)->setStatus("open");
            }
            projects.at(i)->getTodo().at(j)->setCurrentTime(this->time);
        }
        // We don't need to handle done items because we don't need to update their time because it isn't displayed
    }
}


//assign a member to an issue
void Jira::assignIssueJira() {
    bool assigned = false;
    int givenPID, issueID;
    string assignee;
    TeamMember* assigneeMember = new TeamMember();
    vector<Project*> userProjs;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->hasUser(this->userName)) {
            userProjs.push_back(projects[i]);
        }
    }

    cout<<"All of the projects you are involved: ";
    for(int i = 0; i < userProjs.size(); i++) {
        cout<<*userProjs[i]<<", ";
    }
    
    cout<<"Please provide the projectID that you want to assign a member to an issue"<<endl;
    cin>>givenPID;
    
    for(int i = 0; i < projects.size(); i++) {
        if(givenPID == projects[i]->getProjectID()) {
            cout<<"Please provide the issue ID you want to assign a member to."<<endl;
            cin>>issueID;
            cout<<"Please provide the member you want to assign the issue to."<<endl;
            cin>>assignee;
            for(int i = 0; i < users.size(); i++) {
                if(assignee == users[i]->getUsername()) {
                    assigneeMember = users[i];
                }
            }
            projects[i]->assignIssue(userName, assigneeMember, issueID);
            assigned = true;
        }
    }
    if(assigned == true) {
        cout<<"Succesfully assigned a member to this issue in this project!"<<endl;
    }
    else {
        cout<<"Not successfully assigned a member to this issue in this project!"<<endl;
    }
}


void Jira::updateIssueJira() {
    bool update = false;
    int givenPID, issueID;
    vector<Project*> userProjs;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->hasUser(this->userName)) {
            userProjs.push_back(projects[i]);
        }
    }

    cout<<"All of the projects you are involved: ";
    for(int i = 0; i < userProjs.size(); i++) {
        cout<<*userProjs[i]<<", ";
    }
    cout<<endl;
    cout<<"Please provide the projectID that you want to update an issue"<<endl;
    cin>>givenPID;
    
    for(int i = 0; i < projects.size(); i++) {
        if(givenPID == projects[i]->getProjectID()) {
            cout<<"Please provide the issue ID you want to update."<<endl;
            cin>>issueID;
            projects[i]->updateIssue(userName, issueID);
            update = true;
        }
    }
    if(update == true) {
        cout<<"Succesfully updated this issue in this project!"<<endl;
    }
    else {
        cout<<"Not successfully updated this issue in this project!"<<endl;
    }
}

void Jira::deleteGivenProject() {
    bool deleted = false;
    int givenPID;
    vector<Project*> userProjs;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->getProjectOwner().getUsername() == this->userName) {
            userProjs.push_back(projects[i]);
        }
    }

    cout<<"All of the projects you are project owner: ";
    for(int i = 0; i < userProjs.size(); i++) {
        cout<<*userProjs[i]<<", ";
    }
    cout<<endl;
    cout<<"Please provide the projectID that you want to delete"<<endl;
    cin>>givenPID;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->getProjectID() == givenPID && projects[i]->getProjectOwner().getUsername() == this->userName) {
            projects.erase(projects.begin() + i);
            deleted = true;
        }
    }
    if(deleted == true) {
        cout<<"Successfully deleted this project."<<endl;
    }
    else {
        cout<<"Not successfully deleted this project."<<endl;
    }
}

void Jira::updateGivenProject() {
    bool updated = false;
    int givenPID;
    vector<Project*> userProjs;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->getProjectOwner().getUsername() == this->userName || projects[i]->isMemberOfProjectLeads(userName)) {
            userProjs.push_back(projects[i]);
        }
    }

    cout<<"All of the projects you are project owner or project lead: ";
    for(int i = 0; i < userProjs.size(); i++) {
        cout<<*userProjs[i]<<", ";
    }
    cout<<endl;
    cout<<"Please provide the projectID that you want to update?"<<endl;
    cin>>givenPID;
    
    for(int i = 0; i < projects.size(); i++) {
        if(projects[i]->getProjectID() == givenPID && ((projects[i]->getProjectOwner().getUsername() == this->userName) || (projects[i]->isMemberOfProjectLeads(userName)))) {
            cout<<"What you want to update?"<<endl;
            cout<<"ProjectName (N), Deadline (D), assign Project Leads (L), assign Developers (DV)"<<endl;
            string selection;
            cin>>selection;
            if(selection == "N" || selection == "n") {
                string newName;
                cout<<"Please write new project name"<<endl;
                cin>>newName;
                projects[i]->setProjectName(newName);
                cout<<"New Name "<<projects[i]->getProjectName()<<" is updated!"<<endl;
                updated = true;
            }
            else if(selection == "D" || selection == "d") {
                cout<<"Please enter new deadline (numbers of days)"<<endl;
                int newDeadline;
                cin>>newDeadline;
                projects[i]->setProjectDeadline(newDeadline);
                cout<<"New deadline: "<<projects[i]->getProjectDeadline()<<" is updated!"<<endl;
                updated = true;
            }
            else if(selection == "L" || selection == "l") {
                string decision;
                cout<<"Do you want to add new project lead (A) or remove a project lead (R)"<<endl;
                cin>>decision;
                if(decision == "A" || decision == "a") {
                    projects[i]->addLeadProject(this->users);
                    updated = true;
                }
                else if(decision == "R" || decision == "r") {
                    projects[i]->removeLeadProject();
                    updated = true;
                }
            }
            
            else if(selection == "DV" || selection == "dv") {
                string decision;
                cout<<"Do you want to add new developer (A) or remove a developer (R)"<<endl;
                cin>>decision;
                if(decision == "A" || decision == "a") {
                    projects[i]->addDeveloper(this->users);
                    updated = true;
                }
                else if(decision == "R" || decision == "r") {
                    projects[i]->removeDeveloper();
                    updated = true;
                }
            }
        }
    }
    if(updated == true) {
        cout<<"Successfully updated this project."<<endl;
    }
    else {
        cout<<"Not successfully updated this project."<<endl;
    }
}