// Dexter, Grace, Khai
// jira.hpp
// Stores jira definitions
// Version 0.0.1

#ifndef jira_hpp
#define jira_hpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <cctype>
#include <vector>
#include <regex>
#include <cstdlib>
#include "teamMember.hpp"
#include "project.hpp"
#include "issue.hpp"
#include "sprint.hpp"

using namespace std;

class Jira {
protected:
    // Time can be static because there won't be two jira applications
    int time;
    string userName;
    vector<Project*> projects;
    vector<TeamMember*> users;

public:
    // Empty constructor for a new Jira Program if one doesn't exist yet
    Jira();
    // If there is an existing Jira Program, read in data
    Jira(int time, string currentUser, vector<Project*> projects, vector<TeamMember*> users);
    // Destructor that saves all relevant data when program closes
    ~Jira();
    // Copy constructor
    Jira(const Jira &j);
    // Allows project owner to make new prjoect
    void createProject();
    // Allows user to create an account if they do not yet have one
    void createAccount();
    // Allows user to sign in if they already have an account
    void signIn();
    // Saves user out to users.txt when program closes
    void saveUsers();
    // Increment's the time by one
    void incrementTime(){this->time++;};
    // Homepage for jira to access various parts of the project
    void displayJiraHome();
    //check if the given username is available or not
    bool isUserUsed(string givenUsername);
    // Allows user option to sign in or up for jira account
    void displaySignInUp();
    // Timer to run asynchronously to control project time
    static void runTimer();
    
    //print the projects the user is involved in
    void displayUserPj();
    
    //print the specific project the user is involved in and wants to see
    void displayUserGivenPj();
    
    //to log out and restart the sign in/sign up
    void logOut();
    
    void createIssueJira();

    void openJira();

    // Get time
    int getTime() const {return this->time;}
    // Get userName
    string getUserName() const {return this->userName;}
    void setUserName(string given_email) {this->userName = given_email;}
    // Get projects
    vector<Project*> getProjects() const {return this->projects;}
    
    void setProjects(vector<Project*> givenP) {this->projects = givenP;}
    // Get projects
    vector<TeamMember*> getUsers() const {return this->users;}
    void setUsers(vector<TeamMember*> givenUsers) {this->users = givenUsers;}

    void deleteGivenIssue();
    void deleteGivenProject();
    void moveGivenIssue();

    void assignIssueJira();

    void updateIssueJira();

    void updateGivenProject();
    void saveJira();

    // Simulates working on working on a sprint
    void sprintSimulation();

    // Delets sprints at deadlines, moves completed items to todo, sets issue status if complete, sets issues current time
    void updateAllStatus();
};

#endif

