#include "teamMember.hpp"
#include "issue.hpp"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

Issue::Issue() {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = "";
    this->status = "";
    this->assignedTo = new TeamMember();
    this->type = "";
    this->createdDate = 0;
    this->dueDate = 0;
    this-> completionPercent=0;
    this->description = "";
    this->comments = "";
}

Issue::Issue(TeamMember* assignedToMember) {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = "";
    this->status = "";
    this->assignedTo = assignedToMember;
    this->type = "";
    this->createdDate = 0;
    this->dueDate = 0;
    this-> completionPercent=0;
    this->description = "";
    this->comments = "";
    
}
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
    this->completionPercent = (given_due-given_created)/given_created;
    this->description = given_description;
    this->comments = given_comments;
    this->assignedTo = given_member;
}

Issue& Issue::operator=(const Issue& given_issue) {
    this->issueID = given_issue.currentIssue;
    this->priority = given_issue.priority;
    this->status = given_issue.priority;
    this->assignedTo = given_issue.assignedTo;
    this->type = given_issue.type;
    this->createdDate = given_issue.createdDate;
    this->dueDate = given_issue.dueDate;
    this-> completionPercent= given_issue.completionPercent;
    this->description = given_issue.description;
    this->comments = given_issue.comments;

    return *this;
}

ostream& operator<<(ostream& out, const Issue& issue) {
    out<<"IssueID: "<<issue.issueID<<endl;
    out<<"Priority: "<<issue.priority<<endl;
    out<<"Status: "<<issue.priority<<endl;
    out<<"AssignedTo: "<<*issue.assignedTo<<endl;
    out<<"Type: "<<issue.type<<endl;
    out<<"CreatedDate: "<<issue.createdDate<<endl;
    out<<"DueDate: "<<issue.dueDate<<endl;
    out<<"CompletionPercent: "<<issue.completionPercent<<endl;
    out<<"Description: "<<issue.description<<endl;
    out<<"Comments: "<<issue.comments<<endl;
    return out;
}
