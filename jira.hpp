// Dexter, Grace, Khai
// jira.hpp
// Stores jira definitions
// Version 0.0.1

#ifndef jira_hpp
#define jira_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"

using namespace std;

class Jira {
protected:
    // Time can be static because there won't be two jira applications
    static int time;
    string userName;
    vector<Project> projects; 
    vector<TeamMember> users;

public:
    // Empty constructor for a new Jira Program if one doesn't exist yet
    Jira();
    // If there is an existing Jira Program, read in data
    Jira(int time, vector<Project> projects, vector<TeamMember> users);
    // Destructor that saves all relevant data when program closes
    ~Jira();
    // Copy constructor
    Jira(const Jira &j);
    // Allows project owner to make new prjoect
    void createProject(TeamMember owner);
    // Allows user to create an account if they do not yet have one
    void createAccount();
    // Allows user to sign in if they already have an account
    void signIn();
    // Saves user out to users.txt when program closes
    void saveUsers();
    // Increment's the time by one
    void incrementTime();
    // Homepage for jira to access various parts of the project
    void displayJiraHome();
    // Allows user option to sign in or up for jira account
    void displaySignInUp();
    // Timer to run asynchronously to control project time
    // static void runTimer();
    // Get time
    int getTime() const {return this->time;}
    // Get userName
    string getUsername() const {return this->userName;}
    // Get projects
    vector<Project> getProjects() const {return this->projects;}
    // Get projects
    vector<TeamMember> getUsers() const {return this->users;}

    // save current state of Jira to a text file
    void saveJira();
};

#endif