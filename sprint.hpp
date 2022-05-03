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
    Sprint(int, int, vector<Issue*>);
    Sprint(int, int, int, vector<Issue*>);
    int getSprintID() {return sprintID;}
    void setSprintID(int given_ID) {sprintID = given_ID;}
    int getCreatedDate() {return createdDate;}
    void setcreatedDate(int given_createdDate) {createdDate = given_createdDate;}
    int getDueDate() {return dueDate;}
    void setDueDate(int given_time) {dueDate = given_time;}
    vector<Issue*> getIssues () {return issues;}
    
    void setIssues(vector<Issue*> givenIssues) {givenIssues=issues;}
    int getIssueSize();
    Issue getIssueWithIndex(int index);

    friend ostream& operator<<(ostream& out, const Sprint& Sprint);

    bool findIssue(int issueID);
    
    void deleteSprintIssue(int issueID);

    void addIssue(Issue* i) {issues.push_back(i);}

    void reassignSprintIssue(int issueID, TeamMember* assignee);
    void updateIssueSprint(int issueID, string typeMember);

    Issue* getIssue(int issueID);
    
private:
    // Static variable for current sprint
    inline static int currentSprint = 0;
    // sprint ID
    int sprintID;
    // time frame available for the project
    int createdDate;
    // time frame spent on the project
    int dueDate;

    // list of issues in the sprint
    vector<Issue*> issues;
};

#endif
