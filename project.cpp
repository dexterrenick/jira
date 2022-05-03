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

// saves current state of the project
void Project::saveProject(){
        string savedOutput = "";
        ofstream saved;
        cout << "Save Current State\n\n";
        saved.open("saved.txt");
        if(saved.is_open()) {
            saved << "Project ID: " << projectID << endl;
            saved << "Project Name: " << projectName << endl;
            saved << "Project Deadline: " << projectDeadline << endl;
          for (int i = 0; i < toDo.size(); i++) {
            saved << "Issues To Do: " << toDo[i]->getIssueID() << " " <<
              toDo[i]->getPriority() << " " <<
              toDo[i]->getStatus() << " " <<
              toDo[i]->getAssignedTo()->getUsername() <<endl;
          }
          for (int i = 0; i < inProgress.size(); i++) {
            saved << "Sprints In Progress: " << inProgress[i]->getSprintID() << " " <<
              inProgress[i]->getCreatedDate() << " " <<
              inProgress[i]->getDueDate() << 
              " ";

            for(int j = 0; j < inProgress[i]->getIssueSize(); j++) {
              saved << "Issues: " << inProgress[i]->getIssueWithIndex(j).getIssueID();
            }
              
          }
          for (int k = 0; k < done.size(); k++) {
            saved << "Issues Done: " << done[k]->getIssueID() << " " <<
              done[k]->getPriority() << " " <<
              done[k]->getStatus() << " " <<
              done[k]->getAssignedTo()->getUsername() <<endl;
          }
          saved << "Project Owner: " << projectOwner.getUsername() << endl;

          for (int i = 0; i < projectLeads.size(); i++) {
            saved << "Project Leads: " << projectLeads[i]->getUsername() << endl;
            
            }
          for (int i = 0; i < teamDevelopers.size(); i++) {
            saved << "Developers: " << teamDevelopers[i]->getUsername() << endl;
            
            }
 
     }
     saved.close();
}

// opens current state of the project based on text file
void Project::openProject(){
    int projectID;
    string projectName;
    int projectDeadline;
    vector<Issue*> toDo;
    int toDoIssueID;
    string toDoPriority;
    string toDoStatus;
    string toDoType;
    int toDoCreatedDate;
    int toDoDueDate;
    int toDoCurrentTime;
    string toDoDescription;
    string toDoComments;
    string toDoUsername;
    vector<Sprint*> inProgress;
    int sprintID;
    int sprintCreatedDate;
    int sprintIssueID;
    string sprintPriority;
    string sprintStatus;
    string sprintType;
    int sprintDueDate;
    string sprintDescription;
    string sprintComments;
    string sprintUsername;
    vector<Issue*> Sprintissues;
    vector<Issue*> done;
    int doneIssueID;
    string donePriority;
    string doneStatus;
    string doneType;
    int doneCreatedDate;
    int doneDueDate;
    int doneCurrentTime;
    string doneDescription;
    string doneComments;
    string doneUsername;
    TeamMember* projectOwner;
    string ownerName;
    vector<TeamMember*> projectLeads;
    string leadName;
    vector<TeamMember*> teamDevelopers;
    string devName;
    ifstream project;
    project.open("saved.txt");
    if (!project){
    cout << "Error in opening the file" << endl;
}
else if (project.is_open()) {
    project >> projectID;
    project >> projectName;
    project >> projectDeadline;
    project >> toDoIssueID;
    project >> toDoPriority;
    project >> toDoStatus;
    project >> toDoType;
    project >> toDoDueDate;
    project >> toDoCurrentTime;
    project >> toDoDescription;
    project >> toDoComments;
    project >> toDoUsername;
    TeamMember* toDoAssign = new TeamMember(toDoUsername);
    Issue* toDoIssue = new Issue(toDoIssueID, toDoPriority, toDoStatus, toDoType, toDoCreatedDate, toDoDueDate, toDoDescription, toDoComments, toDoAssign);
    toDo.push_back(toDoIssue);
    project >> sprintID;
    project >> sprintCreatedDate;
    project >> sprintDueDate;
    project >> sprintIssueID;
    project >> sprintPriority;
    project >> sprintStatus;
    project >> sprintType;
    project >> sprintCreatedDate;
    project >> sprintDueDate;
    project >> sprintDescription;
    project >> sprintComments;
    project >> sprintUsername;
    TeamMember* sprintAssign = new TeamMember(sprintUsername);
    Issue* sprintIssue = new Issue(sprintIssueID, sprintPriority, sprintStatus, sprintType, sprintCreatedDate, sprintDueDate, sprintDescription, sprintComments, sprintAssign);
    Sprintissues.push_back(sprintIssue);
    Sprint* sprints = new Sprint(sprintID, sprintCreatedDate, sprintDueDate, Sprintissues);
    inProgress.push_back(sprints);
    project >> doneIssueID;
    project >> donePriority;
    project >> doneStatus;
    project >> doneType;
    project >> doneCreatedDate;
    project >> doneDueDate;
    project >> doneDescription;
    project >> doneComments;
    project >> doneUsername;
    TeamMember* doneAssign = new TeamMember(doneUsername);
    Issue* doneIssue = new Issue(doneIssueID, donePriority, doneStatus, doneType, doneCreatedDate, doneDueDate, doneDescription, doneComments, doneAssign);
    done.push_back(doneIssue);
    project >> ownerName;
    TeamMember* projectOwner = new TeamMember(ownerName);
    project >> leadName;
    TeamMember* leads = new TeamMember(leadName);
    projectLeads.push_back(leads);
    project >> devName;
    TeamMember* devs = new TeamMember(devName);
    teamDevelopers.push_back(devs);

}

}

// saves current state of the project to a string
string Project::savedOutput(){
        string savedOutput = "";
            savedOutput += "Project ID: ";
            savedOutput += projectID;
            savedOutput += "; Project Name: ";
            savedOutput += projectName;
            savedOutput += "; Project Deadline: ";
            savedOutput += projectDeadline;
          for (int i = 0; i < toDo.size(); i++) {

              savedOutput += "; Issues To Do: ";
              savedOutput += toDo[i]->getIssueID();
              savedOutput += " ";
              savedOutput += toDo[i]->getPriority();
              savedOutput += " ";
              savedOutput += toDo[i]->getStatus();
              savedOutput += " ";
              savedOutput += toDo[i]->getAssignedTo()->getUsername();
              savedOutput += " ";
          }
          for (int i = 0; i < inProgress.size(); i++) {
              savedOutput += "; Sprints In Progress: ";
              savedOutput += inProgress[i]->getSprintID();
              savedOutput += " ";
              savedOutput += inProgress[i]->getCreatedDate();
              savedOutput += " ";
              savedOutput += inProgress[i]->getDueDate();
              savedOutput += " ";

            for(int j = 0; j < inProgress[i]->getIssueSize(); j++) {

              savedOutput += "; Issues: ";
              savedOutput += inProgress[i]->getIssueWithIndex(j).getIssueID();
              savedOutput += " ";
            }
              
          }
          for (int k = 0; k < done.size(); k++) {

              savedOutput += "; Issues Done: ";
              savedOutput += done[k]->getIssueID();
              savedOutput += " ";
              savedOutput += done[k]->getPriority();
              savedOutput += " ";
              savedOutput += done[k]->getStatus();
              savedOutput += " ";
              savedOutput += done[k]->getAssignedTo()->getUsername();
              savedOutput += " ";
          }
          savedOutput += "; Project Owner: ";
              savedOutput += projectOwner.getUsername();
              savedOutput += " ";

          for (int i = 0; i < projectLeads.size(); i++) {
              savedOutput += projectLeads[i]->getUsername();
              savedOutput += " ";
            }
          for (int i = 0; i < teamDevelopers.size(); i++) {
              savedOutput += teamDevelopers[i]->getUsername();
              savedOutput += " ";
            }
 
     
}

//create an issue
void Project::createIssue(string member, vector<TeamMember*> allUsers) {
    int createdDate, dueDate, completionPercent;
    string priority, status, type, description, comments;
    TeamMember* assignedTo = new TeamMember();
    
    if(member == projectOwner.getUsername() || isMemberOfProjectLeads(member)) {
        cout<<"Please enter a detailed description of this issue."<<endl;
        cin.ignore();
        getline(cin, description);
        
        cout<<"Please give the priority of the issue ('Red', 'Yellow', or 'Green')."<<endl;
        cin.ignore();
        getline(cin, priority);
        
        cout<<"Please give the date this issue is created."<<endl;
        cin>> createdDate;
        
        cout<<"Please give the date this issue is due."<<endl;
        cin>>dueDate;
        completionPercent = (dueDate-createdDate)/createdDate;
        
        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
        cin.ignore();
        getline(cin,status);
        cout<<"Please give the type of the issue (ex. user story, task, build, test, debug, documentation, etc)."<<endl;
        cin.ignore();
        getline(cin,type);
        cout<<"Please give the username of the team member assigned to this issue."<<endl;
        for(int i = 0; i < allUsers.size(); i++) {
            cout<<"All users: "<<allUsers[i]->getUsername()<<", ";
        }
        cout<<endl;
        
        string assignName;
        cin>>assignName;
        
        for(int i = 0; i < allUsers.size(); i++) {
            if(assignName == allUsers[i]->getUsername()) {
                assignedTo = allUsers[i];
            }
        }
        
        cout<<"Please enter any final comments for this issue."<<endl;
        cin.ignore();
        cin>>comments;

        Issue* issue1 = new Issue(priority, status, type, createdDate, dueDate, description, comments,
                                  assignedTo);
        this->toDo.push_back(issue1);
    }
    else {
        cout<<"You are neither project owner nor project leads."<<endl;
        cout<<"You can only assign yourself to this issue."<<endl;
        cout<<"Please enter a detailed description of this issue."<<endl;
        cin.ignore();
        getline(cin, description);
        
        cout<<"Please give the priority of the issue ('Red', 'Yellow', or 'Green')."<<endl;
        cin.ignore();
        getline(cin, priority);
        
        cout<<"Please give the date this issue was created."<<endl;
        cin>>createdDate;
        
        cout<<"Please give the date this issue is due."<<endl;
        cin>>dueDate;
        completionPercent = (dueDate-createdDate)/createdDate;
        
        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
        cin.ignore();
        getline(cin, status);
        cout<<"Please give the type of the issue (ex. user story, task, build, test, debug, documentation, etc)."<<endl;
        cin.ignore();
        getline(cin, type);
        
        for(int i = 0; i < allUsers.size(); i++) {
            if(member == allUsers[i]->getUsername()) {
                assignedTo = allUsers[i];
            }
        }

        cout<<"Please enter any final comments for this issue."<<endl;
        cin.ignore();
        getline(cin, comments);

        Issue* issue1 = new Issue(priority, status, type, createdDate, dueDate, description, comments, assignedTo);
        
        this->toDo.push_back(issue1);
    }
}



bool Project::isMemberOfProjectLeads(string member) {
    bool found = false;
    for(int i = 0; i < projectLeads.size(); i++) {
        if(member == projectLeads[i]->getUsername()) {
            found = true;
        }
    }
    return found;
}

bool Project::isMemberOfDevelopers(string member) {
    bool found = false;
    for(int i = 0; i < teamDevelopers.size(); i++) {
        if(member == teamDevelopers[i]->getUsername()) {
            found = true;
        }
    }
    return found;
}

//delete an issue with given member and given id
//only the project leads or the project owner can delete an issue
void Project::deleteIssue(string member, int issueID) {
    bool deleted = false;
    if(this->hasUser(member)) {
        
        if(member == projectOwner.getUsername() || this->isMemberOfProjectLeads(member)) {
            cout<<"Here! 1"<<endl;
            for(int i = 0; i < toDo.size(); i++) {
                if(issueID == toDo[i]->getIssueID()) {
                    cout<<"Here! 2"<<endl;
                    char selection = 'y';
                    cout<<"Issue is in toDo list. Do you want to delete this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        toDo.erase(toDo.begin() + i);
                        deleted = true;
                    }
                }
            }
            for(int j = 0; j < inProgress.size(); j++) {
                if(inProgress[j]->findIssue(issueID)) {
                    char selection = 'y';
                    cout<<"Issue is in InProgress list. Sprint ID: " <<inProgress[j]->getSprintID()<<" .Do you want to delete this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        inProgress[j]->deleteSprintIssue(issueID);
                        deleted = true;
                        break;
                    }
                }
            }
            for(int k = 0; k < done.size(); k++) {
                if(issueID == done[k]->getIssueID()) {
                    cout<<"Here! 4"<<endl;
                    char selection = 'y';
                    cout<<"Issue is in Work Done list. Do you want to delete this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        done.erase(done.begin() + k);
                        deleted = true;
                    }
                }
            }
        }
        else {
            cout<<"Deleting issue is only allowed for project owner and project leads!"<<endl;
        }
    }
    else {
        cout<<"You are not in this project!"<<endl;
    }
    
    if(deleted == true) {
        cout<<"Successfully deleted this issue."<<endl;
    }
    else {
        cout<<"Not successfully deleted this issue."<<endl;
    }
}


// takes in username of user assigning the issue, the assignee and the issue
// reassigns issue to a given user
void Project::assignIssue(string member, TeamMember* assignee, int issueID) {
    if(this->hasUser(member)) {
    if(member == projectOwner.getUsername() || this->isMemberOfProjectLeads(member)) {
    for(int i = 0; i < toDo.size(); i++) {
        if (toDo[i]->getAssignedTo()->getUsername() != assignee->getUsername()) {
        if(issueID == toDo[i]->getIssueID()) {
                char selection = 'y';
                cout<<"Issue is in toDo list. Do you want to reassign this issue? (y/n)"<<endl;
                cin>>selection;
                if(tolower(selection) == 'y') {
                    toDo[i]->setAssignedTo(assignee);
                    cout<<"IssueID " << toDo[i]->getIssueID() << " has been reassigned to: " << toDo[i]->getAssignedTo()->getUsername() <<endl;

                }
            } 
            }
            else {
                cout << "this issue is already assigned to the assignee!" << endl;
            }
            
        }
        for(int j = 0; j < inProgress.size(); j++) {
            for(int z = 0; z < inProgress[j]->getIssueSize(); z++) {
                if (inProgress[j]->getIssueWithIndex(z).getAssignedTo()->getUsername() != assignee->getUsername()) {
                if(inProgress[j]->getIssueWithIndex(z).getIssueID()) {
                    char selection = 'y';
                    cout<<"Issue is in InProgress list: Sprint ID: " <<inProgress[j]->getSprintID()<<" .Do you want to reassign this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        inProgress[j]->getIssueWithIndex(z).setAssignedTo(assignee);
                        cout<<"IssueID " << inProgress[j]->getIssueWithIndex(z).getIssueID() << " has been reassigned to: " << inProgress[j]->getIssueWithIndex(z).getAssignedTo() <<endl;
                    }
                }
            }
            else {
                cout << "this issue is already assigned to the assignee!" << endl;
            }
            }
            
        }
      for(int k = 0; k < done.size(); k++) {
          if (done[k]->getAssignedTo()->getUsername() != assignee->getUsername()) {
        if(issueID == done[k]->getIssueID()) {
            char selection = 'y';
            cout<<"Issue is in Done list. Do you want to reassign this issue? (y/n)"<<endl;
            cin>>selection;
            if(tolower(selection) == 'y') {
                done[k]->setAssignedTo(assignee);
                cout<<"IssueID " << done[k]->getIssueID() << " has been reassigned to: " << done[k]->getAssignedTo() <<endl;
            }
        }
        }
        else {
                cout << "this issue is already assigned to the assignee!" << endl;
            }
      }
    }
    else {
        cout<<"Re-assigning an issue is only allowed for project owner and project leads!"<<endl;
    }
    }
    else {
        cout<<"You are not in this project!"<<endl;
    }
    
}

void Project::updateIssue(string member, int issueID) {
    //if member is an owner or one of the project leads
    if(member == projectOwner.getUsername() || this->isMemberOfProjectLeads(member)) {
        for(int i = 0; i < toDo.size(); i++) {
            if(issueID == toDo[i]->getIssueID()) {
                string selection;
                cout<<"Issue is in toDo list. Do you want to update this issue? (y/n)"<<endl;
                cin>>selection;
                if(selection == "y" || selection == "Y") {
                    string decision;
                    cout<<"What do you want to update?"<<endl;
                    cout<<"Description (D), comments (C), update status (S)"<<endl;
                    cin>>decision;
                    if(decision == "d" || decision == "D") {
                      string description;
                        cout<<"Please write your new description here!"<<endl;
                        cin>>description;
                        toDo[i]->setDescription(description);
                        break;
                    }
                    else if(decision == "c" || decision == "C") {
                      string comments;
                        cout<<"Please write your comments here!"<<endl;
                        cin>>comments;
                        toDo[i]->setComments(toDo[i]->getComments() + " " + comments);
                        break;
                    }
                    else if(decision == "S" || decision == "s") {
                        string status;
                        cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
                        cin>>status;
                        toDo[i]->setStatus(status);
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        for(int j = 0; j < inProgress.size(); j++) {
            if(inProgress[j]->findIssue(issueID)) {
                string selection;
                cout<<"Issue is in InProgress list. Sprint ID: " <<inProgress[j]->getSprintID()<<" .Do you want to update this issue? (y/n)"<<endl;
                cin>>selection;
                if(selection == "y" || selection == "Y") {
                    inProgress[j]->updateIssueSprint(issueID, "projectLead/Owner");
                    break;
                }
                else {
                    break;
                }
            }
        }
      for(int k = 0; k < done.size(); k++) {
        if(issueID == done[k]->getIssueID()) {
            string selection;
            cout<<"Issue is in Done list. Do you want to update this issue? (y/n)"<<endl;
            cin>>selection;
            if(selection == "y" || selection == "Y") {
                string decision;
                cout<<"What do you want to update?"<<endl;
                cout<<"Description (D), comments (C)."<<endl;
                cin>>decision;
                if(decision == "d" || decision == "D") {
                  string description;
                    cout<<"Please write your new description here!"<<endl;
                    cin>>description;
                    done[k]->setDescription(description);
                    break;
                }
                else if(decision == "C" || decision == "c") {
                  string comments;
                    cout<<"Please write your comments here!"<<endl;
                    cin>>comments;
                    done[k]->setComments(done[k]->getComments() + " " + comments);
                    break;
                }
            }
            else {
                break;
            }
        }
    }
      }
    //if member is the developers
    else if(this->isMemberOfDevelopers(member)) {
        cout<<"You are a developer. You can only comment on the issue."<<endl;
        for(int i = 0; i < toDo.size(); i++) {
            if(toDo[i]->getIssueID() == issueID && toDo[i]->getAssignedTo()->getUsername() == member) {
                string selection;
                cout<<"Issue is in toDo list. Do you want to update this issue? (y/n)"<<endl;
                cin>>selection;
                if(selection == "y" || selection == "Y") {
                    string decision;
                    cout<<"Do you want to comment on this issue?"<<endl;
                    cin>>decision;
                    if(decision == "c" || decision == "C") {
                      string comments;
                        cout<<"Please write your comments here!"<<endl;
                        cin>>comments;
                        toDo[i]->setComments(toDo[i]->getComments() + " " + comments);
                        break;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }
        for(int j = 0; j < inProgress.size(); j++) {
            if(inProgress[j]->findIssue(issueID)) {
                string selection;
                cout<<"Issue is in InProgress list. Sprint ID: " <<inProgress[j]->getSprintID()<<" .Do you want to comment on this issue? (y/n)"<<endl;
                cin>>selection;
                if(selection == "y" || selection == "Y") {
                    inProgress[j]->updateIssueSprint(issueID, "developer");
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
}

void Project::moveIssue(string member, int issueID) {
    bool moved = false;
    if(this->hasUser(member)) {
        if(member == projectOwner.getUsername() || this->isMemberOfProjectLeads(member)) {
            for(int i = 0; i < toDo.size(); i++) {
                if(issueID == toDo[i]->getIssueID()) {
                    Issue* coppiedIssue = toDo[i];
                    string selection = "";
                    cout<<"Issue is in toDo list. Where do you want to move the issue?"<<endl;
                    cout << "1) In Progress" << endl;
                    cout << "2) Completed" << endl;
                    cout << "3) Cancel" << endl;
                    cin>>selection;
                    if (stoi(selection) == 1) {
                        vector<Sprint*> cSprints = this->getInProgress();
                        for (int i = 0; i < cSprints.size(); i++) {
                            cout << cSprints.at(i) << endl;
                        }
                        cout << "Which sprint would you like to add the project to, enter sprint ID: " << endl;

                        string deleteSprint;
                        cin >> deleteSprint;
                        bool validSprint = false;

                        for (int i = 0; i < cSprints.size(); i++) {
                            if (cSprints.at(i)->getSprintID() == stoi(deleteSprint)) {
                                validSprint = true;
                                cSprints[i]->addIssue(coppiedIssue);
                            }
                        }
                        if (validSprint) {
                            toDo.erase(toDo.begin() + i);
                            cout << "Issue moved successfully" << endl;
                            
                        } else {
                            cout << "Invalid sprint. Failed to move issue." << endl;
                        }
                    }
                    else if (stoi(selection) == 2) {
                        for(int j = 0; j < inProgress.size(); j++) {
                            if(inProgress[j]->findIssue(issueID)) {
                                done.push_back(coppiedIssue);
                                inProgress[j]->deleteSprintIssue(issueID);
                            }
                        }
                    } else {
                        return;
                    }
                }
            }
            for(int j = 0; j < inProgress.size(); j++) {
                if(inProgress[j]->findIssue(issueID)) {
                    Issue* coppiedIssue = inProgress[j]->getIssue(issueID);
                    string selection = "";
                    cout<<"Issue is in InProgress list. Sprint ID: " <<inProgress[j]->getSprintID()<<endl;
                    cout<<"Where do you want to move the issue?"<<endl;
                    cout << "1) Completed" << endl;
                    cout << "2) Cancel" << endl;
                    cin>>selection;
                    if (stoi(selection) == 1) {
                        for(int j = 0; j < inProgress.size(); j++) {
                            if(inProgress[j]->findIssue(issueID)) {
                                done.push_back(coppiedIssue);
                                inProgress[j]->deleteSprintIssue(issueID);
                            }
                        }
                    } else {
                        return;
                    }
                }
            }
            for(int k = 0; k < done.size(); k++) {
                if(issueID == done[k]->getIssueID()) {
                    char selection = 'y';
                    cout<<"Issue is in Work Done list. Do you want to delete this issue? (y/n)"<<endl;
                    cin>>selection;
                    if(tolower(selection) == 'y') {
                        done.erase(done.begin() + k);
                        moved = true;
                    }
                }
            }
        }
        else {
            cout<<"Moving issue is only allowed for project owner and project leads!"<<endl;
        }
    }
    else {
        cout<<"You are not in this project!"<<endl;
    }
}

// void Project::moveIssue(int issueID, string section) {
//     for (int i = 0; i < toDo.size() < i++) {
//         if (toDo.at(i)->getIssueID() == issueID) {
//             Issue* coppiedIssue = toDo[i];
//             if (section == "toDo") {
//                 toDo.push_back(toDo.at(i));
//                 toDo.erase(toDo.begin() + i);
//             }
//             if (section == "inProgress") {
//                 inProgress.push_back(toDo.at(i));
//                 toDo.erase(toDo.begin() + i);
//             }
//             if (section == "done") {
//                 done.push_back(toDo.at(i));
//                 toDo.erase(toDo.begin() + i);
//             }
//         }
//     }

//     for (int i = 0; i < inProgress.size() < i++) {
//         if (inProgress.at(i)->getIssueID() == issueID) {
//             Issue* coppiedIssue = inProgress[i];
//             if (section == "inProgress") {
//                 inProgress.push_back(inProgress.at(i));
//                 inProgress.erase(inProgress.begin() + i);

//             }
//         }
//     }

//     for (int i = 0; i < done.size() < i++) {
//         if (done.at(i)->getIssueID() == issueID) {
//             Issue* coppiedIssue = done[i];
//             if (section == "done") {
//                 done.push_back(done.at(i));
//                 done.erase(done.begin() + i);
//             }
//         }
//     }
// }  

void Project::dumpSprint(int sprintID) {
    for (int i = 0; i < inProgress.size(); i++) {
        if (inProgress.at(i)->getSprintID() == sprintID) {
            for (int j = 0; j < inProgress.at(i)->getIssues().size(); j++) {
                // Move to todo
                Issue* coppiedIssue = inProgress.at(i)->getIssues().at(j);
                coppiedIssue->setStatus("open");
                toDo.push_back(coppiedIssue);
                // Don't need to delete because we will delete the whole sprint, which is the only place this lives
            }
            inProgress.erase(inProgress.begin() + i);
        }
    }
}
void Project::addLeadProject(vector<TeamMember*> allUsers) {
    string newLead;
    cout<<"Please provide the name of the member you want to add as project lead?"<<endl;
    cin>>newLead;
    
    if(isMemberOfDevelopers(newLead)) {
        cout<<"This person is in your developer teams"<<endl;
        cout<<"Do you want to change this member's role to project lead? (y/n)"<<endl;
        string decision;
        cin>>decision;
        if(decision == "y" || decision == "Y") {
            for(int i = 0; i < teamDevelopers.size(); i++) {
                if(teamDevelopers[i]->getUsername() == newLead) {
                    vector<TeamMember*> newProjectLeads = this->getProjectLeads();
                    newProjectLeads.push_back(teamDevelopers[i]);
                    setProjectLeads(newProjectLeads);
                    cout<<"Successfully added "<<newLead <<" to project leads."<<endl;
                    teamDevelopers.erase(teamDevelopers.begin() + i);
                    cout<<"Successfully removed "<<newLead <<" in the developer team."<<endl;
                }
            }
        }
    }
    else if(isMemberOfProjectLeads(newLead)) {
        cout<<"This member is your project lead."<<endl;
    }
    else {
        for(int i = 0; i < allUsers.size(); i++) {
            if(newLead == allUsers[i]->getUsername()) {
                vector<TeamMember*> newProjectLeads = this->getProjectLeads();
                newProjectLeads.push_back(allUsers[i]);
                setProjectLeads(newProjectLeads);
            }
        }
    }
}

void Project::removeLeadProject() {
    cout<<"Here is the list of the project leads in this project"<<endl;
    for(int i = 0; i < projectLeads.size(); i++) {
        cout<<projectLeads[i]->getUsername()<<", ";
    }
    cout<<endl;
    string removeLead;
    cout<<"Please provide the name of the member you want to remove in the project leads?"<<endl;
    cin>>removeLead;
    
    if(isMemberOfProjectLeads(removeLead)) {
        for(int i = 0; i < projectLeads.size(); i++) {
            if(projectLeads[i]->getUsername() == removeLead) {
                projectLeads.erase(projectLeads.begin() + i);
                cout<<"Succesfully removed "<<removeLead<<" in the project leads"<<endl;
            }
        }
    }
    else {
        cout<<"This given user is not in your project leads"<<endl;
    }
}

void Project::addDeveloper(vector<TeamMember*> allUsers) {
    string newDevel;
    cout<<"Please provide the name of the member you want to add as developer?"<<endl;
    cin>>newDevel;
    
    if(isMemberOfProjectLeads(newDevel)) {
        cout<<"This person is in your project lead"<<endl;
        cout<<"Do you want to change this member's role to developer (y/n)"<<endl;
        string decision;
        cin>>decision;
        if(decision == "y" || decision == "Y") {
            for(int i = 0; i < projectLeads.size(); i++) {
                if(projectLeads[i]->getUsername() == newDevel) {
                    vector<TeamMember*> newDeveloper = this->getTeamDevelopers();
                    newDeveloper.push_back(projectLeads[i]);
                    setTeamDevelopers(newDeveloper);
                    cout<<"Successfully added "<<newDevel <<" to developer team."<<endl;
                    projectLeads.erase(projectLeads.begin() + i);
                    cout<<"Successfully removed "<<newDevel <<" in the project lead."<<endl;
                }
            }
        }
    }
    else if(isMemberOfDevelopers(newDevel)) {
        cout<<"This person is in your developer team"<<endl;
    }
    else {
        for(int i = 0; i < allUsers.size(); i++) {
            if(newDevel == allUsers[i]->getUsername()) {
                vector<TeamMember*> newDeveloper = this->getTeamDevelopers();
                newDeveloper.push_back(allUsers[i]);
                setTeamDevelopers(newDeveloper);
            }
        }
    }
}

void Project::removeDeveloper() {
    cout<<"Here is the list of the developer in this project"<<endl;
    for(int i = 0; i < teamDevelopers.size(); i++) {
        cout<<teamDevelopers[i]->getUsername()<<", ";
    }
    cout<<endl;
    string removeDev;
    cout<<"Please provide the name of the member you want to remove in the team developers?"<<endl;
    cin>>removeDev;
    
    if(isMemberOfDevelopers(removeDev)) {
        for(int i = 0; i < teamDevelopers.size(); i++) {
            if(teamDevelopers[i]->getUsername() == removeDev) {
                teamDevelopers.erase(teamDevelopers.begin() + i);
                cout<<"Succesfully removed "<<removeDev<<" in the team developer"<<endl;
            }
        }
    }
    else {
        cout<<"This given user is not in your team developer"<<endl;
    }
}