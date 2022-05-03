#include "teamMember.hpp"
#include "issue.hpp"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

//default constructor
Issue::Issue() {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = "";
    this->status = "";
    this->assignedTo = new TeamMember();
    this->type = "";
    this->createdDate = 0;
    this->dueDate = 0;
    this-> currentTime=0;
    this->description = "";
    this->comments = "";
}

//delegating constructor but only username
Issue::Issue(TeamMember* assignedToMember) {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = "";
    this->status = "";
    this->assignedTo = assignedToMember;
    this->type = "";
    this->createdDate = 0;
    this->dueDate = 0;
    this-> currentTime=0;
    this->description = "";
    this->comments = "";
    
}

//delegating consturctor
Issue::Issue(string given_pr, string given_status, string given_type,
int given_created, int given_due, string given_description, string given_comments,
TeamMember* given_member) {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = given_pr;
    this->status = given_status;
    this->type = given_type;
    this->createdDate = given_created;
    this->dueDate = given_due;
    this->currentTime = currentTime;
    this->description = given_description;
    this->comments = given_comments;
    this->assignedTo = given_member;
}

//delegating constructor
Issue::Issue(int given_issueID, string given_pr, string given_status, string given_type,
int given_created, int given_due, string given_description, string given_comments,
TeamMember* given_member) {
    this->issueID = given_issueID;
    this->priority = given_pr;
    this->status = given_status;
    this->type = given_type;
    this->createdDate = given_created;
    this->dueDate = given_due;
    this->currentTime = currentTime;
    this->description = given_description;
    this->comments = given_comments;
    this->assignedTo = given_member;
}

//assignment operator
Issue& Issue::operator=(const Issue& given_issue) {
    this->issueID = given_issue.currentIssue;
    this->priority = given_issue.priority;
    this->status = given_issue.priority;
    this->assignedTo = given_issue.assignedTo;
    this->type = given_issue.type;
    this->createdDate = given_issue.createdDate;
    this->dueDate = given_issue.dueDate;
    this-> currentTime = given_issue.currentTime;
    this->description = given_issue.description;
    this->comments = given_issue.comments;

    return *this;
}

//cout operator
ostream& operator<<(ostream& out, const Issue& issue) {
    if (issue.status != "done") {
        out<<"IssueID: "<<issue.issueID<<endl;
        out<<"Priority: "<<issue.priority<<endl;
        out<<"Status: "<<issue.priority<<endl;
        out<<"AssignedTo: "<<*issue.assignedTo<<endl;
        out<<"Type: "<<issue.type<<endl;
        out<<"CreatedDate: "<<issue.createdDate<<endl;
        out<<"DueDate: "<<issue.dueDate<<endl;
        out<<"CompletionPercent: "<< (1.0 * (issue.currentTime - issue.createdDate)) / (1.0 * (issue.dueDate - issue.currentTime))<<endl;
        out<<"Description: "<<issue.description<<endl;
        out<<"Comments: "<<issue.comments<<endl;
    } else { 
        out<<"IssueID: "<<issue.issueID<<endl;
        out<<"Priority: "<<issue.priority<<endl;
        out<<"Status: "<<issue.priority<<endl;
        out<<"AssignedTo: "<<*issue.assignedTo<<endl;
        out<<"Type: "<<issue.type<<endl;
        out<<"CreatedDate: "<<issue.createdDate<<endl;
        out<<"DueDate: "<<issue.dueDate<<endl;
        out<<"Description: "<<issue.description<<endl;
        out<<"Comments: "<<issue.comments<<endl;
    }
    return out;
}
