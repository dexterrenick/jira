#include "sprint.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

Sprint::Sprint(int timeAllowed, int TimeSpent, vector<Issue> problems) {
    sprintID = this->currentSprint;
    currentSprint++;
    timeFrame = timeAllowed;
    timeWorking = TimeSpent;
    issues=problems;   
}

int Sprint::getIssueSize() {
  return issues.size();
}

Issue Sprint::getIssueWithIndex(int index) {
  if(issues.size() < index) {
    cout<<"Over size!"<<endl;
  }
  else {
    for(int i = 0; i < issues.size(); i++) {
      if(i == index) {
        return issues[i];
      }
    }
  }
}

