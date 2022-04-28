#ifndef Project_hpp
#define Project_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "issue.hpp"
#include "sprint.hpp"
#include "teamMember.hpp"

using namespace std;

class Project {
public:
    Project(string, int, vector<Issue>, vector<Sprint>, vector<Issue>, TeamMember, vector<TeamMember>, vector<TeamMember>);
    // So we can autoincrement
    
    
    // gets project ID
    int getProjectID() {return projectID;}
    // sets project ID
    void setProjectID(int pID) {projectID = pID;}

    // gets project name
    string getProjectName() {return projectName;}
    // sets project name
    void setProjectName(string givenName) {projectName = givenName;}

    // gets list of issues to do
    vector<Issue> getTodo() {return toDo;}   
    // sets list of issues to do 
    void setTodo(vector<Issue> givenToDo) {toDo = givenToDo;}

    // gets list of sprints currently in progress
    vector<Sprint> getInProgress() {return inProgress;}
    // sets list of sprints currently in progress
    void setInProgress(vector<Sprint> givenIP) {inProgress = givenIP;}

    // gets list of issues that are done
    vector<Issue> getDone() {return done;}
    // sets list of issues that are done
    void setDone(vector<Issue> givenD) {done = givenD;}

    // gets project owner
    TeamMember getProjectOwner() {return projectOwner;}
    // sets project owner
    void setProjectOwner(TeamMember givenOwner) {projectOwner = givenOwner;}

    // gets list of project leads
    vector<TeamMember> getProjectLeads() {return projectLeads;}
    // sets list of project leads
    void setProjectLeads(vector<TeamMember> listOfProjectLeads) {projectLeads = listOfProjectLeads;}

    // gets list of devs
    vector<TeamMember> getTeamDevelopers() {return teamDevelopers;}
    // sets list of devs
    void setTeamDevelopers(vector<TeamMember> givenTeamDevelopers) {teamDevelopers = givenTeamDevelopers;}

    // saves current state to a text file
    void saveState(); 
    
    // functions to add:
    //moveIssue(issueID)
    //createIssue(issueID)
    //deleteIssue(issueID)
    //updateIssue(issueID)
    //assignIssue(issueID, teamMember)

    void displayProject(string currentUser);





private:
    static int currentProject = 0;
    // defines project ID
    int projectID;

    // defines name of the project
    string projectName;

    // defines deadline of the project
    int projectDeadline;

    // list of issues to do
    vector<Issue> toDo;

    //list of sprints in progress
    vector<Sprint> inProgress;
    
    // list of completed issues
    vector<Issue> done;

    // defines project owner
    TeamMember projectOwner;

    // defines list of project leads
    vector<TeamMember> projectLeads;
    
    // defines list of developers
    vector<TeamMember> teamDevelopers;

};

#endif