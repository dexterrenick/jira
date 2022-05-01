#include "sprint.hpp"
#include "issue.hpp"
#include "teamMember.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

Sprint::Sprint(int timeAllowed, int TimeSpent, vector<Issue*> problems) {
    sprintID = this->currentSprint;
    currentSprint++;
    timeFrame = timeAllowed;
    timeWorking = TimeSpent;
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
    out<<"TimeFrame: "<<sprint.timeFrame<<endl;
    out<<"Time working: "<<sprint.timeWorking<<endl;
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