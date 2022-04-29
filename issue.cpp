// #include <stdio.h>
// #include <iostream>

// #include "teamMember.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include "issue.hpp"
#include "teamMember.hpp"


Issue::Issue(TeamMember assignedToMember) {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = "";
    this->status = "";
    this->assignedTo = assignedToMember;
    this->type = "";
    this->createdDate = 0;
    this->dueDate = 0;
    this-> completionPercent=0;
    this->reporter = assignedToMember;
    this->description = "";
    this->comments = "";
    
}
Issue::Issue(string given_pr, string given_status, string given_type, int given_created, int given_due, string given_description, string given_comments, TeamMember given_reporter, TeamMember given_member) {
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
    this->reporter = given_reporter;
}



