#include "sprint.hpp"
#include "issue.hpp"
#include "teamMember.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

Sprint::Sprint(int createdDate, int dueDate, vector<Issue*> problems) {
    sprintID = this->currentSprint;
    currentSprint++;
    this->createdDate = createdDate;
    this->dueDate = dueDate;
    issues = problems;
}

Sprint::Sprint(int given_sprintID, int createdDate, int dueDate, vector<Issue*> problems) {
    sprintID = given_sprintID;
    this->createdDate = createdDate;
    this->dueDate = dueDate;
    issues = problems;
}

int Sprint::getIssueSize() {
  return issues.size();
}

Issue Sprint::getIssueWithIndex(int index) {
    Issue found;
  if(issues.size() < index) {
    cout<<"Over size!"<<endl;
  }
  else {
    for(int i = 0; i < issues.size(); i++) {
      if(i == index) {
        found = *issues[i];
      }
    }
  }
    return found;
}

ostream& operator<<(ostream& out, const Sprint& sprint) {
    out<<"SprintID: "<<sprint.sprintID<<endl;
    out<<"Date Created: "<<sprint.createdDate<<endl;
    out<<"Date Due: "<<sprint.dueDate<<endl;
    for(int i = 0; i < sprint.issues.size(); i++) {
        out<<"Issue no."<<i+1<<endl;
        out<<*sprint.issues[i];
        out<<endl;
    }                                                                                                                                                                                                                 
    return out;
}

bool Sprint::findIssue(int issueID) {
    bool found = false;
    for(int i = 0; i < issues.size(); i++) {
        if(issueID == issues[i]->getIssueID()) {
            found = true;
        }
    }
    return found;
}

Issue* Sprint::getIssue(int issueID) {
    for(int i = 0; i < issues.size(); i++) {
        if(issueID == issues[i]->getIssueID()) {
            return issues[i];
        }
    }
}

void Sprint::deleteSprintIssue(int issueID) {
    bool erased = false;
    for(int i = 0; i < issues.size(); i++) {
        if(issues[i]->getIssueID() == issueID) {
            issues.erase(issues.begin() + i);
            erased = true;
        }
    }
    if(erased == true) {
        cout<<"Successfully deleted this issue."<<endl;
    }
    else {
        cout<<"Not successfully deleted this issue."<<endl;
    }
}

void Sprint::reassignSprintIssue(int issueID,TeamMember* assignee) {
    bool reassign = false;
    for(int i = 0; i < issues.size(); i++) {
        if(issues[i]->getIssueID() == issueID) {
            issues[i]->setAssignedTo(assignee);
            reassign = true;
        }
    }
    if(reassign == true) {
        cout<<"Successfully reassigned this issue."<<endl;
    }
    else {
        cout<<"Did not successfully reassigned this issue."<<endl;
    }
}
void Sprint::updateIssueSprint(int issueID, string typeMember) {
    for(int i = 0; i < issues.size(); i++) {
        if(issues[i]->getIssueID() == issueID) {
            if(typeMember != "developer") {
                string decision;
                cout<<"What do you want to update?"<<endl;
                cout<<"Description (D), comments (C), update status (S)"<<endl;
                cin>>decision;
                if(decision == "D" || decision == "d") {
                  string description;
                    cout<<"Please write your new description here!"<<endl;
                    cin>>description;
                    issues[i]->setDescription(description);
                    break;
                }
                else if(decision == "C" || decision == "c") {
                    string comments;
                    cout<<"Please write your comments here!"<<endl;
                    cin>>comments;
                    issues[i]->setComments(issues[i]->getComments() + ". New comments "+ comments);
                    break;
                }
                else if(decision == "S" || decision == "s") {
                    string status;
                    cout<<"Please give the status of the issue (open, in progress, done, overdue)."<<endl;
                    cin>>status;
                    issues[i]->setStatus(status);
                    break;
                }
            }
        }
        else {
            cout<<"You can only comment on this issue because you are developer."<<endl;
            string comments;
            cout<<"Please write your comments here!"<<endl;
            cin>>comments;
            issues[i]->setComments(issues[i]->getComments() + ". New comments "+ comments);
            break;
        }
    }
}
