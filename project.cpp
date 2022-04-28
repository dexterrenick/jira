#include "project.hpp"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
// functions to add:
    //moveIssue(issueID)
    //createIssue(issueID)
    //deleteIssue(issueID)
    //updateIssue(issueID)
    //assignIssue(issueID, teamMember)


Project::Project(string PName, int ProjectDeadline, vector<Issue> issuesToDo, 
vector<Sprint> sprints, vector<Issue> issuesDone, TeamMember owner, vector<TeamMember> leads, vector<TeamMember> developers) {
    projectID = this->currentProject;
    currentProject++;
    projectName = PName;
    projectDeadline = ProjectDeadline;
    toDo = issuesToDo;
    inProgress = sprints; 
    done = issuesDone;
    projectOwner = owner;
    projectLeads = leads;
    teamDevelopers = developers;
}

int Project::getProjectID() {
    return this->projectID;
}

string Project::getProjectName() {
    return this->projectName;
}

void Project::displayProject(string currentUser) {
    cout << "SHOULD DISPLAY RELEVANT INFORMATION FOR GIVEN CURRENT USER (WHOS SIGNED IN) HERE" << endl;
}

void Project::saveState(){
        ofstream saved;
        cout << "Save Current State\n\n";
        saved.open("saved.txt");
        if(saved.is_open()) {
            saved << "Project ID: " << projectID << endl;
            saved << "Project Name: " << projectName << endl;
            saved << "Project Deadline: " << projectDeadline << endl;
            saved << "Issues To Do: " << toDo << endl;
            saved << "Sprints In Progress: " << inProgress << endl;
            saved << "Issues Completed: " << done << endl;
            saved << "Project Owner: " << projectOwner << endl;
            saved << "Project Leads: " << projectLeads << endl;
            saved << "Developers: " << teamDevelopers << endl;
 
     }
     saved.close();
}