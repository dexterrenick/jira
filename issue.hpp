#ifndef issue_hpp
#define issue_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include "teamMember.hpp"

using namespace std;

class Issue {
    private:
        inline static int currentIssue = 0;
        int issueID;
        string priority;
        string status;
        string type;
        int createdDate;
        int dueDate;
        int completionPercent;
        string description;
        string comments;
        TeamMember reporter;
        TeamMember assignedTo;

    public:
        Issue(TeamMember assignedToMember);
        Issue(string given_pr, string given_status, TeamMember given_member);
        Issue(string given_pr, string given_status, string given_type, int given_created, int given_due, string given_description, string given_comments, TeamMember given_reporter, TeamMember given_member);
        int getIssueID() {return issueID;}
        void setIssueID(int given_issueID) {issueID = given_issueID;}
        string getPriority() {return priority;}
        void setPriority(string given_pr) {priority = given_pr;}
        string getStatus() {return status;}
        void setStatus(string given_status) {status = given_status;}
        TeamMember getAssignedTo() {return assignedTo;}
        void setAssignedTo(TeamMember given_member) {assignedTo = given_member;}
        TeamMember getReporter() {return reporter;}
        void setReporter(TeamMember given_reporter) {reporter = given_reporter;}
        string getType() {return type;}
        void setType(string given_type) {type = given_type;}
        int getCreatedDate() {return createdDate;}
        void setCreatedDate(int given_created) {createdDate = given_created;}
        int getDueDate() {return dueDate;}
        void setDueDate(int given_due) {dueDate = given_due;}
        int getCompletionPercent() {return (dueDate-createdDate)/createdDate;}
        void setCompletionPercent(int given_due, int given_created) 
        {completionPercent = (given_due-given_created)/given_created;}
         string getDescription() {return description;}
        void setDescription(string given_description) {description = given_description;}
         string getComments() {return comments;}
        void setComments(string given_comments) {comments = given_comments;}
};

#endif