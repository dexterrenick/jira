#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctype.h>

#include "project.hpp"

using namespace std;

// functions to add:
    //moveIssue(issueID)
    //createIssue() got it
    //deleteIssue(issueID) gotit
    //updateIssue(issueID)
    //assignIssue(issueID, teamMember)

Project::Project(string PName, int ProjectDeadline,  TeamMember owner, vector<TeamMember*> leads, vector<TeamMember*> developers) {
    projectID = this->currentProject;
    currentProject++;
    projectName = PName;
    projectDeadline = ProjectDeadline;
    toDo = vector<Issue*>();
    inProgress = vector<Sprint*>();
    done = vector<Issue*>();
    projectOwner = owner;
    projectLeads = leads;
    teamDevelopers = developers;
}



Project::Project(string PName, int ProjectDeadline, vector<Issue*> issuesToDo,
vector<Sprint*> sprints, vector<Issue*> issuesDone, TeamMember owner, vector<TeamMember*> leads, vector<TeamMember*> developers) {
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

ostream& operator<<(ostream& out, const Project& proj) {
    out<<"Project ID: "<<proj.projectID<<endl;
    out<<"Project name: "<<proj.projectName<<endl;
    out<<"ProjectDeadline: "<< proj.projectDeadline<<endl;
    out<<"List of ToDo Issue --- ";
    out<<"Total issues: "<<proj.toDo.size()<<endl;
    for(int i = 0; i < proj.toDo.size(); i++) {
        out<<"Issue ID: ";
        out<<*proj.toDo[i];
        out<<endl;
    }
    cout<<endl;
    out<<"List of Sprints in progress --- ";
    out<<"Total sprints: "<<proj.inProgress.size()<<endl;
    for(int j = 0; j < proj.inProgress.size(); j++) {
        out<<"Sprint ID: ";
        out<<*proj.inProgress[j];
        out<<endl;
    }
    cout<<endl;
    out<<"List of Work done --- ";
    out<<"Total issues: "<<proj.done.size()<<endl;
    for(int i = 0; i < proj.done.size(); i++) {
        out<<"Issue ID: ";
        out<<*proj.done[i];
        out<<endl;
    }
    cout<<endl;
    out<<"Project Owner: "<<proj.projectOwner<<endl;
    out<<"Project lead(s): ";
    for(int i = 0; i < proj.projectLeads.size(); i++) {
        out<<*proj.projectLeads[i]<<", ";
    }
    out<<endl;
    out<<"Team developer(s): ";
    for(int i = 0; i < proj.teamDevelopers.size(); i++) {
        out<<*proj.teamDevelopers[i]<<", ";
    }
    out<<endl;
    return out;
}

bool Project::hasUser(string user) {
    if (getProjectOwner().getUsername() == user) {
     return true;
    }
    for (int i = 0; i < teamDevelopers.size(); i++) {
     if (teamDevelopers[i]->getUsername() == user) {
         return true;
     }
    }
    for (int i = 0; i < projectLeads.size(); i++) {
     if (projectLeads[i]->getUsername() == user) {
         return true;
     }
    }
    return false;
}

string Project::getUserRole(string currentUser) {
    string s = "";
    bool found = false;
    if (projectOwner.getUsername() == currentUser) {
        found = true;
        s += "Project Owner";
        
    }
    for (int i = 0; i < projectLeads.size(); i++) {
        if (projectLeads.at(i)->getUsername() == currentUser) {
            found = true;
             if (s != "") {
                 s += " - ";
             }
             else {
                 s += "Lead";
             }
        }
    }
    for (int i = 0; i < teamDevelopers.size(); i++) {
     if (teamDevelopers.at(i)->getUsername() == currentUser) {
         found = true;
         if (s != "") {
             s += " - ";
         }
         else {
             s += "Developer";
         }
     }
    }
    if(found == true) {
        return s;
    }
    else {
        return "No Role";
    }
}
