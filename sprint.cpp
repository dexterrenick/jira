#include "sprint.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

Sprint::Sprint(int givenID, int timeAllowed, int TimeSpent, vector<Issue> problems) {
    sprintID = this->currentSprint;
    currentSprint++;
    timeFrame= timeAllowed;
    timeWorking=TimeSpent;
    issues=problems;
    
}

