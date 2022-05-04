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
    
    ~Project();
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
    
    //to print the project's detail
    void displayProject(string currentUser);

    // Returns string of users highest access level in given project
    string getUserRole(string currentUser);

    //to create an issue by the given users(check role)
    //invite a user if they are not in the project
    void createIssue(string member, vector<TeamMember*> allUsers);

    //to delete an issue by the given username(check role) and given issueID
    void deleteIssue(string member, int issueID);
    
    //to assign an assignee by the given memer(check role) and given issueID
    void assignIssue(string member, TeamMember* assignee, int issueID);

    //check if the current username is in this project's lead team
    bool isMemberOfProjectLeads(string member);

    //check if the current username is in the developers
    bool isMemberOfDevelopers(string member);
    
    //cout operator
    friend ostream& operator<<(ostream& out, const Project& proj);

    //Move issue from one place to another
    void moveIssue(string member, int issueID);

    // Moves all items from sprint to todo and deletes sprint
    void dumpSprint(int sprintID);

    //to update an issue by the given member(check role) and the given issueID
    void updateIssue(string member, int issueID);

    string savedOutput();

    // opens text file and updates project based on given textfile
    void openProject();
    
    //to add a member to the lead project
    //test if they are in the team or in the prj
    void addLeadProject(vector<TeamMember*> allUsers);
    
    //remove a member in the project lead
    void removeLeadProject();
    
    //add a member to the developer team
    //remove them if they are in project lead
    //make them join if they are not in the prj
    void addDeveloper(vector<TeamMember*> allUsers);
    
    //to remove the developer int he team
    void removeDeveloper();

private:
    static int currentProject;
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
