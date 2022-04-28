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
}
Issue::Issue(string given_pr, string given_status, TeamMember given_member) {
    this->issueID = currentIssue;
    currentIssue++;
    this->priority = given_pr;
    this->status = given_status;
    this->assignedTo = given_member;
}

