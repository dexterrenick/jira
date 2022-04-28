#ifndef sprint_hpp
#define sprint_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "issue.hpp"
using namespace std;

class Sprint {
public:
    Sprint(int, int, int, vector<Issue>);
    int getSprintID() {return sprintID;}
    void setSprintID(int given_ID) {sprintID = given_ID;}
    int getTimeFrame() {return timeFrame;}
    void setTimeFrame(int given_timeFrame) {timeFrame = given_timeFrame;}
    int getTimeWorking() {return timeWorking;}
    void setTimeWorking(int given_time) {timeWorking = given_time;}   
    vector<Issue> getIssues () {return issues;}
    void setIssues(vector<Issue> givenIssues) {givenIssues=issues;}


private:
    // Static variable for current sprint
    static int currentSprint = 0;
    // sprint ID
    int sprintID;
    // time frame available for the project
    int timeFrame;
    // time frame spent on the project
    int timeWorking;

    // list of issues in the sprint
    vector<Issue> issues;
};

#endif