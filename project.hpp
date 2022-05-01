#ifndef Project_hpp
#define Project_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include <fstream>
#include "issue.hpp"
#include "sprint.hpp"
#include "teamMember.hpp"

using namespace std;

class Project {
public:
    Project(string PName, int ProjectDeadline,  TeamMember owner, vector<TeamMember*> leads, vector<TeamMember*> developers);
    Project(string PName, int ProjectDeadline, vector<Issue*> issuesToDo, vector<Sprint*> sprints, vector<Issue*> issuesDone, TeamMember owner, vector<TeamMember*> leads, vector<TeamMember*> developers);
    // So we can autoincrement
    
    // gets project ID
    int getProjectID() const {return projectID;}
    // sets project ID
    void setProjectID(int pID) {projectID = pID;}

    // gets project name
    string getProjectName() const {return projectName;}
    // sets project name
    void setProjectName(string givenName) {projectName = givenName;}
    
    //get deadline
    int getProjectDeadline() const {return projectDeadline;}
    
    //set deadline
    void setProjectDeadline(int givenD) {projectDeadline = givenD;}

    // gets list of issues to do
    vector<Issue*> getTodo() const {return toDo;}
    // sets list of issues to do
    void setTodo(vector<Issue*> givenToDo) {toDo = givenToDo;}

    // gets list of sprints currently in progress
    vector<Sprint*> getInProgress() const {return inProgress;}
    // sets list of sprints currently in progress
    void setInProgress(vector<Sprint*> givenIP) {inProgress = givenIP;}
    

    // gets list of issues that are done
    vector<Issue*> getDone() const {return done;}
    // sets list of issues that are done
    void setDone(vector<Issue*> givenD) {done = givenD;}

    // gets project owner
    TeamMember getProjectOwner() const {return projectOwner;}
    // sets project owner
    void setProjectOwner(TeamMember givenOwner) {projectOwner = givenOwner;}

    // gets list of project leads
    vector<TeamMember*> getProjectLeads() const {return projectLeads;}
    // sets list of project leads
    void setProjectLeads(vector<TeamMember*> listOfProjectLeads) {projectLeads = listOfProjectLeads;}

    // gets list of devs
    vector<TeamMember*> getTeamDevelopers() const {return teamDevelopers;}
    // sets list of devs
    void setTeamDevelopers(vector<TeamMember*> givenTeamDevelopers) {teamDevelopers = givenTeamDevelopers;}

    // saves current state to a text file
    void saveProject();

    // Determines if a given user is a member of this project
    bool hasUser(string user);
    
    // functions to add:
    //createIssue(issueID)
    //deleteIssue(issueID) done
    //updateIssue(issueID)
    //assignIssue(issueID, teamMember)

    void displayProject(string currentUser);

    // Returns string of users highest access level in given project
    string getUserRole(string currentUser);

    void createIssue(string member, vector<TeamMember*> allUsers);

    void deleteIssue(TeamMember owner, int issueID);

    void deleteIssue(string member, int issueID);

    void assignIssue(string member, TeamMember* assignee, int issueID);

    //check if the current username is in this project's lead team
    bool isMemberOfProjectLeads(string member);

    //check if the current username is in the developers
    bool isMemberOfDevelopers(string member);
    
    friend ostream& operator<<(ostream& out, const Project& proj);

    //Move issue from one place to another
    void moveIssue(string member, int issueID);

    void updateIssue(string member, int issueID);

private:
    inline static int currentProject = 0;
    // defines project ID
    int projectID;

    // defines name of the project
    string projectName;

    // defines deadline of the project
    int projectDeadline;

    // list of issues to do
    vector<Issue*> toDo;

    //list of sprints in progress
    vector<Sprint*> inProgress;
    
    // list of completed issues
    vector<Issue*> done;

    // defines project owner
    TeamMember projectOwner;

    // defines list of project leads
    vector<TeamMember*> projectLeads;
    
    // defines list of developers
    vector<TeamMember*> teamDevelopers;

};

#endif
