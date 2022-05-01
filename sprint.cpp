#include "sprint.hpp"
#include "issue.hpp"
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
