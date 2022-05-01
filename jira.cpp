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

Jira::Jira() {
    this->time = 0;
    this->userName = "";
    this->projects = vector<Project*>();
    users = vector<TeamMember*>();
}

Jira::Jira(int time, string currentUser, vector<Project*> projects, vector<TeamMember*> users) {
    this->time = time;
    this->projects = projects;
    this->users = users;
    // Regardless of there is a program or not, when program is run, we need someone to sign in, so initialize as null
    this->userName = currentUser;
}

Jira::Jira(const Jira &j) {
    time = j.getTime();
    userName = j.getUserName();
    projects = j.getProjects();
    users = j.getUsers();
}

void Jira::signIn(vector<TeamMember*> &allUsers, vector<Project*> &allProjects) {
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
        displayJiraHome(allUsers, allProjects);
    }
    else {
        cout<<"Users not found."<<endl;
        cout<<"Please sign up."<<endl;
        createAccount(allUsers, allProjects);

    }
}

void Jira::displaySignInUp(vector<TeamMember*> &allUsers, vector<Project*> &allProjects) {
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
        signIn(allUsers, allProjects);
    }
    else {
        createAccount(allUsers, allProjects);
    }
}


void Jira::displayJiraHome(vector<TeamMember*> &allUsers, vector<Project*> &allProjects) {
    int menuOption = 0;
    
    while(menuOption != 14) {
        cout<<endl;
        cout<<"These are menu options. -------------------"<<endl;
        cout<<"1) Load previous projects. "<<endl;
        cout<<"2) Save current projects. "<<endl;
        cout<<"3) Log out."<<endl;
        cout<<"4) View all of your projects. "<<endl;
        cout<<"5) View specific project and its details. "<<endl;
        cout<<"6) Create new project (you will be the project owner for this project)."<<endl;
        cout<<"7) View specific issue and its details. "<<endl;
        cout<<"8) Create new issue. "<<endl;
        cout<<"9) Work on issue. (Sprint stimulation)."<<endl;
        cout<<"10) Update your project status. "<<endl;
        cout<<"11) Update your issue status. "<<endl;
        cout<<"12) Delete your project. "<<endl;
        cout<<"13) Delete your issue. "<<endl;
        cout<<"14) Quit (would not save the current project, please save if needed). "<<endl;
        
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
            logOut(allUsers, allProjects);
            displaySignInUp(allUsers, allProjects);
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
            createProject(allProjects);
        }

        //Move Issue
        else if(menuOption == 9) {
            moveGivenIssue(allProjects);
        }

        else if(menuOption == 13) {
            deleteGivenIssue(allProjects);
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
void Jira::createAccount(vector<TeamMember*> &allUsers, vector<Project*> &allProjects) {
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
    allUsers.push_back(newUser);
    users.push_back(newUser);
    cout<<"Successfully created new account."<<endl;
    displayJiraHome(allUsers, allProjects);
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

void Jira::logOut(vector<TeamMember*> &allUsers, vector<Project*> &allProjects) {
    this->userName = "";
    allUsers = this->users;
    allProjects = this->projects;
}

void Jira::createProject(vector<Project*> &allProjects) {
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
        cout<<"Please give a time frame for this sprint."<<endl;
        getline(cin, timeFrame);
    }
    sprint1->setTimeFrame(stoi(timeFrame));
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
    allProjects = this->projects;
}

void Jira::createIssueJira(vector<TeamMember*> allUsers, vector<Project*> allProjects) {
    int givenPID;
    cout<<"Please provide the projectID that you want to create an issue"<<endl;
    cin>>givenPID;
    bool created = false;
    
    for(int i = 0; i <projects.size(); i++) {
        if(givenPID == projects[i]->getProjectID()) {
            projects[i]->createIssue(userName, allUsers);
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
void Jira::deleteGivenIssue(vector<Project*> allProjects) {
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
    allProjects = this->projects;
}

void Jira::moveGivenIssue(vector<Project*> allProjects) {
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
    allProjects = this->projects;
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
            projects[i]->saveProject();
          }
          for (int i = 0; i < users.size(); i++) {
              jira << "Users: " << users[i]->getUsername() << endl;}
 
     }
     jira.close();
}

/*string savedOutput = ""
for (projec : projects) {
    savedOutput += project.getSave()
}*/