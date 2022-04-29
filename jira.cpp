// Dexter, Grace, Khai
// jira.cpp
// Stores Jira methods
// Version 0.0.1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>
#include <future>

#include "project.hpp"
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"
#include "jira.hpp"


using namespace std;

Jira::Jira() {
    this->time = 0;
    this->userName = "";
    this->projects = vector<Project>();
    users = vector<TeamMember>();
}

Jira::Jira(int time, vector<Project> projects, vector<TeamMember> users) {
    this->time = time;
    this->projects = projects;
    this->users = users;
    // Regardless of there is a program or not, when program is run, we need someone to sign in, so initialize as null
    this->userName = "";
}

Jira::~Jira() {
    saveUsers();
}

Jira::Jira(const Jira &j) {
    time = j.getTime();
    userName = j.getUsername();
    projects = j.getProjects();
    users = j.getUsers();
}

void Jira::createProject(TeamMember owner) {
    int projID, deadline, sprintSize, toDoSize, projectLeadSize, developerSize;
    string projName;
    cout<<"Please give the name of the project."<<endl;
    cin>>projName;
    cout<<"Please give the duration of the project (number of days)."<<endl;
    cin>>deadline;
    cout<<"Please give the number of sprints you want to work on."<<endl;
    cin>>sprintSize;
    cout<<"Please give the number of issues you want to work on."<<endl;
    cin>>toDoSize;
    
    cout<<"How many project lead(s) do you want to include in this project?"<<endl;
    cin>>projectLeadSize;
    cout<<"Please choose the following users to be your project lead(s)."<<endl;
    for(int i = 0; i < users.size(); i++) {
        if(users[i].getUsername() != owner.getUsername()) {
            cout<<users[i].getUsername()<<", ";
        }
    }
    cout<<endl;
    
    vector<TeamMember> prjLeads(projectLeadSize);
    while(projectLeadSize != 0) {
        cout<<"Please enter the name of the user for project lead."<<endl;
        string name;
        cin>>name;
        for(int i = 0; i < users.size(); i++) {
            if(name == users[i].getUsername()) {
                prjLeads.push_back(users[i]);
            }
            else {
                cout<<"This person is not available."<<endl;
            }
        }
        projectLeadSize--;
    }
    
    cout<<"How many developer(s) do you want to include in this project?"<<endl;
    cin>>developerSize;

    cout<<"Please choose the following users to be your developers."<<endl;
    for(int i = 0; i < users.size(); i++) {
        for(int j = 0; j < prjLeads.size(); j++) {
            if(users[i].getUsername() != prjLeads[j].getUsername()) {
                cout<<users[i].getUsername()<<", ";
            }
            else {
                cout<<"This person is not available."<<endl;
            }
        }
        cout<<endl;
    }
    
    vector<TeamMember> developers(developerSize);
    while(developerSize != 0) {
        cout<<"Please enter the name of the user for developer."<<endl;
        string name;
        cin>>name;
        for(int i = 0; i < users.size(); i++) {
            if(name == users[i].getUsername()) {
                developers.push_back(users[i]);
            }
            else {
                cout<<"This person is not available."<<endl;
            }
        }
        developerSize--;
    }

  vector<Sprint> listOfSprints;
  char another = 'y';
  
   while(tolower(another) == 'y') {
    vector<Issue> problems;
    Sprint sprint1(0, 0, problems);
    int timeFrame;
    cout<<"Please give a time frame for this sprint."<<endl;
    cin>> timeFrame;
    sprint1.setTimeFrame(timeFrame);

    listOfSprints.push_back(sprint1);
    cout<<"\nEnter another sprint? (y/n)"<<endl;
    cin>>another;
    cin.ignore();
    cout<<endl;
  } 
  vector<Issue> listOfTodo;
  vector<Issue> listOfDone;
  
  Project project1(projName, deadline, listOfTodo, listOfSprints, listOfDone, owner, prjLeads, developers);

  this->projects.push_back(project1);
}

// Allows user to create an account if they do not yet have one
void Jira::createAccount() {
    string userEmail, myText;
    cout << "Enter user email: " << endl;
    cin >> userEmail;
    // Verify they do not already have an account, if they don't add them to the list

    ifstream MyReadFile("users.txt");

    bool newUser = true;
    if (!(MyReadFile.fail())) {
        // Use a while loop together with the getline() function to read the file line by line
        while (getline(MyReadFile, myText)) {
            if(myText == userEmail) {
                newUser = false;
            }
        }
    }
    // Don't want duplicate user emails
    if (!newUser) {
        this->users.push_back(userEmail);
    }
    MyReadFile.close();

}

void signIn() {
    string userEmail, myText;
    cout << "Enter user email: " << endl;
    cin >> userEmail;
    fstream MyReadFile("users.txt");

    bool userExists = false;
    if (!(MyReadFile.fail())) {
        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, myText)) {
            if(myText == userEmail) {
                userExists = true;
            }
        }
    }
    if (!userExists) {
        cout << "User not found." << endl;
        //displaySignInUp();
    }
    else {
       //displayJiraHome();
    }
}

void Jira::displaySignInUp() {
    string option = "";
    cout << "1) Sign in" << endl;
    cout << "2) Sign up" << endl;
    cout << "Enter your choice: " << endl;
    cin >> option;
    while (option != "1" || option != "2") {
        cout << "Invalid option. Try again: " << endl;
        cin >> option;
    }
    if (option == "1") {
        signIn();
    }
    createAccount();
}

void Jira::saveUsers() {
    ofstream myfile("example.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < users.size(); i++) {
            myfile << users.at(i).getUsername() << endl;
        }
        myfile.close();
    }
}

void Jira::incrementTime() {
    this->time++;
}

void Jira::displayJiraHome() {
    vector<int> userProjects = vector<int>();
    
    cout << "Here is a list of projects you are involved in and your role: " << endl;
    // Getting projects they are in
    for(int i = 0; i < projects.size(); i++) {
        if (projects.at(i).hasUser(this->userName)) {
            userProjects.push_back(projects.at(i).getProjectID());
            cout << "PID: " << projects.at(i).getProjectID() << " PROJECT NAME: " << (projects.at(i).getProjectName()) << " ROLE: " << (projects.at(i).getUserRole(userName)) << endl;
        }
    }
    // Give them option to create a project
    cout << endl;
    
    int openProjectInt;
    if (userProjects.size() == 0) {
        cout << "It looks like you aren't in any projects!" << endl;
    } else {
        bool validProjectEntered = false;
        while (!validProjectEntered) {
            cout << "Which project would you like to open?" << endl;
            cout << "ENTER PID: " << endl;
            string openProject = "";
            cin >> openProject;

            try {
                openProjectInt = stoi(openProject);
                if (count(userProjects.begin(), userProjects.end(), openProjectInt)) {
                    validProjectEntered = true;
                }
            } catch (...) {
                cout << "Please enter the PID, a number." << endl;
            }
            cout << "Invalid PID, please try again." << endl;
        }
    }

    // IF it is in users projects, we know it is an existing project
    for (int i = 0; i < projects.size(); i++) {
        if (openProjectInt == projects.at(i).getProjectID()) {
            projects.at(i).displayProject(userName);
        }
    }
}
/*
static void Jira::runTimer() {
    std::cout << "Start\n";
    while (true) {
        this->time++;
        this_thread::sleep_for(chrono::seconds(1));

    }
} */


/*
void Jira::saveJira(){
        ofstream save;
        cout << "Save Current State\n\n";
        save.open("jira.txt");
        if(save.is_open()) {
            
            }} */
