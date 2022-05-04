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
    Sprint(int createdDate, int dueDate);
    ~Sprint();
    int getSprintID() {return sprintID;}
    void setSprintID(int given_ID) {sprintID = given_ID;}
    int getCreatedDate() {return createdDate;}
    void setcreatedDate(int given_createdDate) {createdDate = given_createdDate;}
    int getDueDate() {return dueDate;}
    void setDueDate(int given_time) {dueDate = given_time;}
    vector<Issue*> getIssues () {return issues;}
    void setIssues(vector<Issue*> givenIssues) {givenIssues=issues;}
    
    //get the issue size
    int getIssueSize();
    
    //get the issue at the given index
    Issue getIssueWithIndex(int index);

    //cout operator
    friend ostream& operator<<(ostream& out, const Sprint& Sprint);
    
    //return the issue from the given issueID
    bool findIssue(int issueID);
    
    //delete the issue in the sprint from the given issueID
    void deleteSprintIssue(int issueID);

    //ro as the given issue to the issue list
    void addIssue(Issue* i) {issues.push_back(i);}

    //to reassign the given issueID to the given assignee
    void reassignSprintIssue(int issueID, TeamMember* assignee);
    
    //to update the issue sprint with the givn issueID
    void updateIssueSprint(int issueID, string typeMember);

    //to get the issue from the given issueID
    Issue* getIssue(int issueID);
    
private:
    // Static variable for current sprint
    static int currentSprint;
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
