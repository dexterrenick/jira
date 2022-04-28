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
    int time;
    string userName;
    map<Project, TeamMember> projects; 
    vector<TeamMember> users;

public:
    // Empty constructor for a new Jira Program if one doesn't exist yet
    Jira();
    // If there is an existing Jira Program, read in data
    Jira(int time, map<Project, TeamMember> projects, vector<TeamMember> users);

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
};

#endif