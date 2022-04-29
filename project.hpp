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
    Project(string PName, int ProjectDeadline,  TeamMember owner, vector<TeamMember> leads, vector<TeamMember> developers);
    Project(string, int, vector<Issue>, vector<Sprint>, TeamMember, vector<TeamMember>, vector<TeamMember>);
    Project(string, int, vector<Issue>, vector<Sprint>, vector<Issue>, TeamMember, vector<TeamMember>, vector<TeamMember>);
    // So we can autoincrement
    
    
    // gets project ID
    int getProjectID() const {return projectID;}
    // sets project ID
    void setProjectID(int pID) {projectID = pID;}

    // gets project name
    string getProjectName() const {return projectName;}
    // sets project name
    void setProjectName(string givenName) {projectName = givenName;}

    // gets list of issues to do
    vector<Issue> getTodo() const {return toDo;}   
    // sets list of issues to do 
    void setTodo(vector<Issue> givenToDo) {toDo = givenToDo;}

    // gets list of sprints currently in progress
    vector<Sprint> getInProgress() const {return inProgress;}
    // sets list of sprints currently in progress
    void setInProgress(vector<Sprint> givenIP) {inProgress = givenIP;}

    // gets list of issues that are done
    vector<Issue> getDone() const {return done;}
    // sets list of issues that are done
    void setDone(vector<Issue> givenD) {done = givenD;}

    // gets project owner
    TeamMember getProjectOwner() const {return projectOwner;}
    // sets project owner
    void setProjectOwner(TeamMember givenOwner) {projectOwner = givenOwner;}

    // gets list of project leads
    vector<TeamMember> getProjectLeads() const {return projectLeads;}
    // sets list of project leads
    void setProjectLeads(vector<TeamMember> listOfProjectLeads) {projectLeads = listOfProjectLeads;}

    // gets list of devs
    vector<TeamMember> getTeamDevelopers() const {return teamDevelopers;}
    // sets list of devs
    void setTeamDevelopers(vector<TeamMember> givenTeamDevelopers) {teamDevelopers = givenTeamDevelopers;}

    // saves current state to a text file
    void saveState(); 

    // Determines if a given user is a member of this project
    bool hasUser(string userString);

    // Move issue from one state to another
    void moveIssue(int issueID, string moveTo);
    
    // functions to add:
   
    //createIssue(issueID)
    //deleteIssue(issueID) done
    //updateIssue(issueID)
    //assignIssue(issueID, teamMember)

    void displayProject(string currentUser);

    // Returns string of users highest access level in given project
    string getUserRole(string userString);

    void createIssue(TeamMember member);

    void deleteIssue(TeamMember owner, int issueID);

    void updateIssue(TeamMember member, int issueID);

    void assignIssue(TeamMember member, TeamMember assignee, int issueID);
    


private:
    inline static int currentProject = 0;
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