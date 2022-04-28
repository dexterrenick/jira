#ifndef issue_hpp
#define issue_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include "teamMember.hpp"

using namespace std;

class Issue {
public:
    Issue(int givenID, string given_pr, string given_status, TeamMember given_member);
    int getIssueID() {return issueID;}
    void setIssueID(int given_issueID) {issueID = given_issueID;}
    string getPriority() {return priority;}
    void setPriority(string given_pr) {priority = given_pr;}
    string getStatus() {return status;}
    void setSatus(string given_status) {status = given_status;}
    TeamMember getAssignedTo() {return assignedTo;}
    void setAssignedTo(TeamMember given_member) {assignedTo = given_member;}

private:
    int issueID;
    string priority;
    string status;
    TeamMember assignedTo;

};

#endif