#ifndef issue_hpp
#define issue_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include "teamMember.hpp"

using namespace std;

class Issue {
    private:
        static int currentIssue;
        int issueID;
        string priority;
        string status;
        string type;
        int createdDate;
        int dueDate;
        int currentTime;
        string description;
        string comments;
        TeamMember* assignedTo;

    public:
        Issue();
        Issue(TeamMember* assignedToMember);
        Issue(string given_pr, string given_status, string given_type,
int given_created, int given_due, string given_description, string given_comments, TeamMember* given_member);
    
        Issue(int issueID, string given_pr, string given_status, string given_type,
int given_created, int given_due, string given_description, string given_comments, TeamMember* given_member);

        //destructor
        ~Issue() {delete assignedTo;}

        //get and set for members
        int getIssueID() {return issueID;}
        void setIssueID(int given_issueID) {issueID = given_issueID;}
        string getPriority() {return priority;}
        void setPriority(string given_pr) {priority = given_pr;}
        string getStatus() {return status;}
        void setStatus(string given_status) {status = given_status;}
        TeamMember* getAssignedTo() {return assignedTo;}
        void setAssignedTo(TeamMember* given_member) {assignedTo = given_member;}
        string getType() {return type;}
        void setType(string given_type) {type = given_type;}
        int getCreatedDate() {return createdDate;}
        void setCreatedDate(int given_created) {createdDate = given_created;}
        int getDueDate() {return dueDate;}
        void setDueDate(int given_due) {dueDate = given_due;}
        int getCurrentTime() {return currentTime;}
        void setCurrentTime(int t) {currentTime = t;}
        string getDescription() {return description;}
        void setDescription(string given_description) {description = given_description;}
        string getComments() {return comments;}
        void setComments(string given_comments) {comments = given_comments;}

    //assignement operator
    Issue& operator=(const Issue& given_issue);
    //cout operator
    friend ostream& operator<<(ostream& out, const Issue& issue);
};

#endif



