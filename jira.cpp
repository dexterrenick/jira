// Dexter, Grace, Khai
// jira.cpp
// Stores Jira methods
// Version 0.0.1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "project.hpp"
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"
#include "jira.hpp"


using namespace std;

Jira::Jira() {
    this->time = 0;
    this->userName = "";
    this->projects = map<Project, TeamMember>();
    users = vector<TeamMember>();
}

Jira::Jira(int time, map<Project, TeamMember> projects, vector<TeamMember> users) {
    this->time = time;
    this->projects = projects;
    this->users = users;
    // Regardless of there is a program or not, when program is run, we need someone to sign in, so initialize as null
    this->userName = "";
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
        if(users[i].getUsername() != owner) {
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
    
    cout<<"How many developer(s) do you want ot include in this project?"<<endl;
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


    vector<Sprint> listOfSprints(sprintSize);
    vector<Issue> listOfTodo(toDoSize);

    this->projects.insert(pair<Project, TeamMember>(new Project(projName, deadline, listOfTodo, listOfSprints, owner, prjLeads, developers), owner));
}

// Allows user to create an account if they do not yet have one
void Jira::createAccount() {
    string userEmail;
    cout << "Enter user email: " << endl;
    cin >> userEmail;
    // Verify they do not already have an account, if they don't add them to the list

    ifstream MyReadFile("users.txt");

    bool newUser = true;
    if (!(fileStream.fail())) {
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
    string userEmail;
    cout << "Enter user email: " << endl;
    cin >> userEmail;

    bool userExists = false;
    if (!(fileStream.fail())) {
        // Use a while loop together with the getline() function to read the file line by line
        while (getline (MyReadFile, myText)) {
            if(myText == userEmail) {
                userExists = true;
            }
        }
    }
    if (!userExists) {
        cout << "User not found." << endl;
        displaySignInUp();
    }
    else {
        displayJiraHome();
    }
}

void Jira::displaySignInUp() {
    string option = "";
    cout << "1) Sign in" << endl;
    cout << "2) Sign up << endl" << endl;
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
            myfile << (users.at(i).getUserName()) << endl;
        }
        myfile.close();
    }
}

void Jira::incrementTime() {
    this->time++;
}

void Jira::displayJiraHome() {
    vector<int> userProjects = vector<int>();
    auto iter = projects.begin();
    
    cout << "Here is a list of projects you are involved in and your role: " << endl;
    // Getting projects they are in
    while (iter != projects.end()) {
        if ((iter->first).hasUser(this->userName)) {
            userProjects.push_back((iter->first).getProjectID);
            cout << "PID: " << ((iter->first).getProjectID()) << " PROJECT NAME: " << ((iter->first).getProjectName()) << ((iter->first).getUserRole(userName)) << endl;
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
            string openProject;
            cin >> openProject;

            try {
                int openProjectInt = stoi(openProject);
                if (count(userProjects.begin(), userProjects.end(), openProjectInt)) {
                    validProjectEntered = true;
                }
            } catch(...) {
                cout << "Please enter the PID, a number." << endl;
            }
            cout << "Invalid PID, please try again." << endl;
        }
    }
    iter = projects.begin();
    // IF it is in users projects, we know it is an existing project
    while (iter != projects.end()) {
        if (openProjectInt == ((iter->first).getProjectID())) {
            (iter->first).displayProject(userName);
        }
    }
}
