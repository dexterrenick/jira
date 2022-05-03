// Dexter, Grace, Khai
// main.cpp
// Run Jira Simulation
// Version 0.0.1

#include "project.hpp"
#include "teamMember.hpp"
#include "issue.hpp"
#include "sprint.hpp"
#include "jira.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main() {
    TeamMember* alex = new TeamMember("Alex123");
    TeamMember* ben = new TeamMember("Ben134");
    TeamMember* charles = new TeamMember("Charles422");
    TeamMember* emily = new TeamMember("Emily082");
    TeamMember* fenix = new TeamMember("Fenix294");
    TeamMember* harry = new TeamMember("Harry1083");

    vector<TeamMember*> allUsers;
    allUsers.push_back(alex);
    allUsers.push_back(ben);
    allUsers.push_back(charles);
    allUsers.push_back(emily);
    allUsers.push_back(fenix);
    allUsers.push_back(harry);
    
    vector<TeamMember*> docsLeads;
    docsLeads.push_back(ben);
    docsLeads.push_back(charles);

    vector<TeamMember*> docsDevelop;
    docsDevelop.push_back(emily);
    docsDevelop.push_back(fenix);
    docsDevelop.push_back(harry);
    
    Issue* docsIss1 = new Issue(emily);
    Issue* docsIss2 = new Issue(fenix);
    Issue* docsIss3 = new Issue(harry);
    Issue* docsIss4 = new Issue(charles);
    Issue* docsIss5 = new Issue(ben);
    Issue* docsIss6 = new Issue(alex);
    
    vector<Issue*> docsloITodo;
    docsloITodo.push_back(docsIss4);
    
    vector<Issue*> docsloISp1;
    docsloISp1.push_back(docsIss1);
    docsloISp1.push_back(docsIss2);
    docsloISp1.push_back(docsIss3);
    Sprint* docsSprint1 = new Sprint(10, 8, docsloISp1);
    
    vector<Issue*> docsloISp2;
    docsloISp2.push_back(docsIss5);
    docsloISp2.push_back(docsIss2);
    Sprint* docsSprint2 = new Sprint(15, 0, docsloISp2);
    
    vector<Sprint*> docsloSprint;
    docsloSprint.push_back(docsSprint1);
    docsloSprint.push_back(docsSprint2);
    
    vector<Issue*> docsloIDone;
    Project* p1 = new Project("Docs", 12, docsloITodo, docsloSprint, docsloIDone, *alex, docsLeads, docsDevelop);
    
    vector<Project*> allProjects;
    allProjects.push_back(p1);
    
    Jira* j = new Jira(0, "", allProjects, allUsers);
    
    j->displaySignInUp();
    //j->createAccount(allUsers, allProjects);
    
    for(int i = 0; i < allUsers.size(); i++) {
        cout<<allUsers[i]->getUsername()<<", ";
    }
    return 0;
}
