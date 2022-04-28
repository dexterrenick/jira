#include "teamMember.hpp"
#include "issue.hpp"
#include <stdio.h>
#include <iostream>

Issue::Issue(int givenID, string given_pr, string given_status, TeamMember given_member) {
    issueID = givenID;
    priority = given_pr;
    status = given_status;
    assignedTo = given_member;
}

