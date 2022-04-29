#include "project.hpp"
#include "issue.cpp"
#include "issue.hpp"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
// functions to add:
    //createIssue() got it
    //deleteIssue(issueID) gotit
    //updateIssue(issueID) 
    //assignIssue(issueID, teamMember)

Project::Project(string PName, int ProjectDeadline,  TeamMember owner, vector<TeamMember> leads, vector<TeamMember> developers) {
    projectID = this->currentProject;
    currentProject++;
    projectName = PName;
    projectDeadline = ProjectDeadline;
    toDo = vector<Issue>();
    inProgress = vector<Sprint>(); 
    done = vector<Issue>();
    projectOwner = owner;
    projectLeads = leads;
    teamDevelopers = developers;
}


Project::Project(string PName, int ProjectDeadline, vector<Issue> issuesToDo, vector<Sprint> sprints, vector<Issue> issuesDone, TeamMember owner, vector<TeamMember> leads, vector<TeamMember> developers) {
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
          for (int i = 0; i < toDo.size(); i++) {
            saved << "Issues To Do: " << toDo[i].getIssueID() << " " <<
              toDo[i].getPriority() << " " <<
              toDo[i].getStatus() << " " <<
              toDo[i].getAssignedTo().getUsername() <<endl;
          }
          for (int i = 0; i < inProgress.size(); i++) {
            saved << "Sprints In Progress: " << inProgress[i].getSprintID() << " " <<
              inProgress[i].getTimeFrame() << " " <<
              inProgress[i].getTimeWorking() << 
              " ";
            for(int j = 0; j < inProgress[i].getIssueSize(); j++) {
              saved << "Issues: " << inProgress[i].getIssueWithIndex(j).getIssueID();
            }
              
          }
          for (int i = 0; i < done.size(); i++) {
            saved << "Issues To Do: " << done[i].getIssueID() << " " <<
              done[i].getPriority() << " " <<
              done[i].getStatus() << " " <<
              done[i].getAssignedTo().getUsername() <<endl;
          }
          saved << "Project Owner: " << projectOwner.getUsername() << endl;
          for (int i = 0; i < projectLeads.size(); i++) {
            saved << "Project Leads: " << projectLeads[i].getUsername() << endl;}
          for (int i = 0; i < teamDevelopers.size(); i++) {
            saved << "Developers: " << teamDevelopers[i].getUsername() << endl;}
 
     }
     saved.close();
}

void Project::createIssue(TeamMember member) {
    int createdDate, dueDate, completionPercent;
    string priority, status, type, description, comments;
    TeamMember assignedTo, reporter;
    if(member.getUsername() == projectOwner.getUsername() || member.isMemberOf(projectLeads)) {
        cout<<"Please given the username of the team member who reported this issue."<<endl;
        string reporterName;
        cin>>reporterName;
        reporter.setUsername(reporterName);
        cout<<"Please enter a detailed description of this issue."<<endl;
        cin>>description;
        cout<<"Please give the priority of the issue ('Red', 'Yellow', or 'Green')."<<endl;
        cin>>priority;
        cout<<"Please give the date this issue was created."<<endl;
        cin>>createdDate;
        cout<<"Please give the date this issue is due."<<endl;
        cin>>dueDate;
        completionPercent = (dueDate-createdDate)/createdDate;
        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
        cin>>status;
        cout<<"Please give the type of the issue (ex. user story, task, build, test, debug, documentation, etc)."<<endl;
        cin>>type;
        cout<<"Please give the username of the team member assigned to this issue."<<endl;
        string assignName;
        cin>>assignName;
        assignedTo.setUsername(assignName);
        cout<<"Please enter any final comments for this issue."<<endl;
        cin>>comments;

        Issue issue1( priority, status, type, createdDate, dueDate, description, comments, reporter, assignedTo);

        this->toDo.push_back(issue1);
    }
    else {
        cout<<"Please given the username of the team member who reported this issue."<<endl;
        reporter=member;
        cout<<"Please enter a detailed description of this issue."<<endl;
        cin>>description;
        cout<<"Please give the priority of the issue ('Red', 'Yellow', or 'Green')."<<endl;
        cin>>priority;
        cout<<"Please give the date this issue was created."<<endl;
        cin>>createdDate;
        cout<<"Please give the date this issue is due."<<endl;
        cin>>dueDate;
        completionPercent = (dueDate-createdDate)/createdDate;
        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
        cin>>status;
        cout<<"Please give the type of the issue (ex. user story, task, build, test, debug, documentation, etc)."<<endl;
        cin>>type;
        cout<<"Please give the username of the team member assigned to this issue."<<endl;
        assignedTo=member;
        cout<<"Please enter any final comments for this issue."<<endl;
        cin>>comments;

        Issue issue1( priority, status, type, createdDate, dueDate, description, comments, reporter, assignedTo);
        this->toDo.push_back(issue1);
        
    }
    
}

//delete an issue with given member and given id
//only the project leads or the project owner can delete an issue
void Project::deleteIssue(TeamMember member, int issueID) {
    if(member.getUsername() == projectOwner.getUsername() || member.isMemberOf(projectLeads)) {
        for(int i = 0; i < toDo.size(); i++) {
            if(issueID == toDo[i].getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in toDo list. Do you want to delete this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    toDo.erase(toDo.begin() + i);
                    break;
                }
            }
        }
        for(int j = 0; j < inProgress.size(); j++) {
            for(int z = 0; z < inProgress[j].getIssueSize(); z++) {
                if(issueID == inProgress[j].getIssueWithIndex(z).getIssueID()) {
                    char selection = 'y';
                    cout<<"Issue is in InProgress list: Sprint ID: " <<inProgress[j].getSprintID()<<" .Do you want to delete this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        inProgress[j].getIssues().erase(inProgress[j].getIssues().begin() + z);
                        break;
                    }
                }
            }
        }
        for(int k = 0; k < done.size(); k++) {
            if(issueID == done[k].getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in Work Done list. Do you want to delete this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    done.erase(done.begin() + k);
                    break; 
                }
            }
        }
    }
    else {
        cout<<"Deleting issue is only allowed for project owner and project leads!"<<endl;
    }
}

bool Project::hasUser(string userString) {
    if (projectOwner.getUsername() == userString) {
        return true;
    }
    for (int i = 0; i < teamDevelopers.size(); i++) {
        if (teamDevelopers.at(i).getUsername() == userString) {
            return true;
        }
    }
    for (int i = 0; i < projectLeads.size(); i++) {
        if (projectLeads.at(i).getUsername() == userString) {
            return true;
        }
    }
    return false;
}

string Project::getUserRole(string userString) {
    string s = "";
    if (projectOwner.getUsername() == userString) {
        s += "Project Owner";
    }
    for (int i = 0; i < projectLeads.size(); i++) {
        if (projectLeads.at(i).getUsername() == userString) {
            if (s != "") {
                s += " - ";
            }
            else {
                s += "Lead";
            } 
        }
    }
    for (int i = 0; i < teamDevelopers.size(); i++) {
        if (teamDevelopers.at(i).getUsername() == userString) {
            if (s != "") {
                s += " - ";
            }
            else {
                s += "Developer";
            } 
        }
    }
    return "No Role";
}

void Project::updateIssue(TeamMember member, int issueID) {
    //if member is an owner or one of the project leads
    if(member.getUsername() == projectOwner.getUsername() || member.isMemberOf(projectLeads)) {
        for(int i = 0; i < toDo.size(); i++) {
            if(issueID == toDo[i].getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in toDo list. Do you want to update this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    char decision;
                    cout<<"What do you want to update?"<<endl;
                    cout<<"Description (D), comments (C), update status (S)"<<endl;
                    cin>>decision;
                    if(tolower(decision) == 'd') {
                        string description;
                        cout<<"Please write your new description here!"<<endl;
                        cin>>description;
                        toDo[i].setDescription(description);
                        break;
                    }
                    else if(tolower(decision) == 'c') {
                        string comments;
                        cout<<"Please write your comments here!"<<endl;
                        cin>>comments;
                        toDo[i].setComments(toDo[i].getComments() + " " + comments);
                        break;
                    }
                    else if(tolower(decision) == 's') {
                        string status;
                        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
                        cin>>status;
                        toDo[i].setStatus(status);
                        break;
                    }
                }
            }
        }
        for(int j = 0; j < inProgress.size(); j++) {
            for(int z = 0; z < inProgress[j].getIssueSize(); z++) {
                if(issueID == inProgress[j].getIssueWithIndex(z).getIssueID()) {
                    char selection = 'y';
                    cout<<"Issue is in InProgress list: Sprint ID: " <<inProgress[j].getSprintID()<<" .Do you want to update this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        char decision;
                        cout<<"What do you want to update?"<<endl;
                        cout<<"Description (D), comments (C), update status(S)."<<endl;
                        cin>>decision;
                        if(tolower(decision) == 'd') {
                            string description;
                            cout<<"Please write your new description here!"<<endl;
                            cin>>description;
                            inProgress[j].getIssueWithIndex(z).setDescription(description);
                            break;
                        }
                        else if(tolower(decision) == 'c') {
                            string comments;
                            cout<<"Please write your comments here!"<<endl;
                            cin>>comments;
                            inProgress[j].getIssueWithIndex(z).setComments(inProgress[j].getIssueWithIndex(z).getComments() + " " + comments);
                            break;
                        }
                        else if(tolower(decision) == 's') {
                            string status;
                            cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
                            cin>>status;
                            inProgress[j].getIssueWithIndex(z).setStatus(status);
                            break;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < done.size(); i++) {
            if(issueID == done[i].getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in Done list. Do you want to update this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    char decision;
                    cout<<"What do you want to update?"<<endl;
                    cout<<"Description (D), comments (C)."<<endl;
                    cin>>decision;
                    if(tolower(decision) == 'd') {
                        string description;
                        cout<<"Please write your new description here!"<<endl;
                        cin>>description;
                        done[i].setDescription(description);
                        break;
                    }
                    else if(tolower(decision) == 'c') {
                        string comments;
                        cout<<"Please write your comments here!"<<endl;
                        cin>>comments;
                        done[i].setComments(done[i].getComments() + " " + comments);
                        break;
                    }
                }
            }
        }        
    }
    //if member is the developers
    else if(member.isMemberOf(teamDevelopers)) {
        for(int i = 0; i < toDo.size(); i++) {
            if(toDo[i].getIssueID() == issueID && toDo[i].getAssignedTo().getUsername() == member.getUsername()) {
                char selection = 'y';
                cout<<"Issue is in toDo list. Do you want to update this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    char decision;
                    cout<<"What do you want to update?"<<endl;
                    cout<<"Comments (C), update status (S)."<<endl;
                    cin>>decision;
                    if(tolower(decision) == 's') {
                        string status;
                        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
                        cin>>status;
                        toDo[i].setStatus(status);
                        break;
                    }
                    else if(tolower(decision) == 'c') {
                        string comments;
                        cout<<"Please write your comments here!"<<endl;
                        cin>>comments;
                        toDo[i].setComments(toDo[i].getComments() + " " + comments);
                        break;
                    }
                }
            }
        }
        for(int j = 0; j < inProgress.size(); j++) {
            for(int z = 0; z < inProgress[j].getIssueSize(); z++) {
                if(issueID == inProgress[j].getIssueWithIndex(z).getIssueID() && member.getUsername() == inProgress[j].getIssueWithIndex(z).getAssignedTo().getUsername() ) {
                    char selection = 'y';
                    cout<<"Issue is in InProgress list: Sprint ID: " <<inProgress[j].getSprintID()<<" .Do you want to update this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        char decision;
                        cout<<"What do you want to update?"<<endl;
                        cout<<"Comments (C), update status(S)"<<endl;
                        cin>>decision;
                        if(tolower(decision) == 'c') {
                            string comments;
                            cout<<"Please write your comments here!"<<endl;
                            cin>>comments;
                            inProgress[j].getIssueWithIndex(z).setComments(inProgress[j].getIssueWithIndex(z).getComments() + " " + comments);
                            break;
                        }
                        else if(tolower(decision) == 's') {
                            string status;
                            cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
                            cin>>status;
                            inProgress[j].getIssueWithIndex(z).setStatus(status);
                            break;
                        }
                    }
                }
            }
        }
    }
}

// takes in username of user assigning the issue, the assignee and the issue
// reassigns an existing issue to someone else
void Project::assignIssue(TeamMember member, TeamMember assignee, int issueID) {
    if(member.getUsername() == projectOwner.getUsername() || member.isMemberOf(projectLeads)) {
    for(int i = 0; i < toDo.size(); i++) {
            if(issueID == toDo[i].getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in toDo list. Do you want to reassign this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    toDo[i].setAssignedTo(assignee);
                    cout<<"IssueID " << toDo[i].getIssueID() << " has been reassigned to: " << toDo[i].getAssignedTo().getUsername() <<endl;

                }
            }
        }
        for(int j = 0; j < inProgress.size(); j++) {
            for(int z = 0; z < inProgress[j].getIssueSize(); z++) {
                if(issueID == inProgress[j].getIssueWithIndex(z).getIssueID()) {
                    char selection = 'y';
                    cout<<"Issue is in InProgress list: Sprint ID: " <<inProgress[j].getSprintID()<<" .Do you want to reassign this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        inProgress[j].getIssueWithIndex(z).setAssignedTo(assignee);
                        cout<<"IssueID " << inProgress[j].getIssueWithIndex(z).getIssueID() << " has been reassigned to: " << inProgress[j].getIssueWithIndex(z).getAssignedTo().getUsername() <<endl;
                    }
                }
            }
        }
        for(int k = 0; k < done.size(); k++) {
            if(issueID == done[k].getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in Done list. Do you want to reassign this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    done[k].setAssignedTo(assignee);
                    cout<<"IssueID " << (done[k].getIssueID()) << " has been reassigned to: " << done[k].getAssignedTo().getUsername() <<endl;
                }
            }
        }        
    }
    else {
        cout<<"Assigning an issue is only allowed for project owner and project leads!"<<endl;
    }
}

// void moveIssue(int issueID, string moveTo) {
//     iss
    
// }

